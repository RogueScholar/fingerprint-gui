/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: Fingerprint.cpp, Fingerprint.h
 * Purpose: Represents a single fingerprint, its data, and the assigned device;
 *          also handles some GUI interaction.
 *
 * @author Wolfgang Ullrich
 */

#include "Fingerprint.h"
#include "DeviceHandler.h"
#include "FingerprintDevice.h"
#include "UsbDevice.h"
#include <errno.h>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

Fingerprint::Fingerprint(int finger, FingerprintDevice *d,
                         QLabel *textLabels[5], QLabel *iconLabels[5]) {
  valid = false;
  busy = false;
  data = nullptr;
  fpPic = nullptr;
  this->finger = finger;
  this->textLabels[0] = textLabels[0];
  this->textLabels[1] = textLabels[1];
  this->textLabels[2] = textLabels[2];
  this->textLabels[3] = textLabels[3];
  this->textLabels[4] = textLabels[4];
  this->iconLabels[0] = iconLabels[0];
  this->iconLabels[1] = iconLabels[1];
  this->iconLabels[2] = iconLabels[2];
  this->iconLabels[3] = iconLabels[3];
  this->iconLabels[4] = iconLabels[4];
  setAcquireStage(-1);
  device = d;
  device->setMode(MODE_ACQUIRE);
  if (loadData()) { // Existing fingerprint found
    valid = true;
  }
}

// Public getters and setters
FingerprintDevice *Fingerprint::getDevice() { return device; }

bool Fingerprint::isValid() { return valid; }

void Fingerprint::modeVerify() { device->setMode(MODE_VERIFY); }

bool Fingerprint::swipe() {
  if (device == nullptr || busy)
    return false;
  busy = true;
  syslog(LOG_DEBUG, "Swipe finger at %s.",
         device->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  device->start();
  syslog(LOG_DEBUG, "Thread started.");
  return true;
}

// Slots
void Fingerprint::newAcquireResult(int result) {
  int rc = result;

  setAcquireStage(result);
  switch (result) {
  case RESULT_ENROLL_COMPLETE:
    syslog(LOG_DEBUG, "Acquire complete.");
    valid = false;
    dataSize = device->getData(&data, &fpPic);
    if (dataSize == 0) {
      rc = RESULT_ENROLL_FAIL;
      break;
    }
    if (saveData()) {
      valid = true;
    } else {
      rc = RESULT_ENROLL_FAIL;
    }
    break;
  case RESULT_ENROLL_FAIL:
    syslog(LOG_DEBUG, "Acquire failed.");
    valid = false;
    break;
  default:
    return;
  }
  emit acquireFinished(rc, fpPic);
}

void Fingerprint::newVerifyResult(int result, struct fp_pic_data *pic) {
  setVerifyStage(result);
  switch (result) {
  case RESULT_VERIFY_NO_MATCH:
    syslog(LOG_DEBUG, "Verify failed.");
    valid = false;
    break;
  case RESULT_VERIFY_MATCH:
    syslog(LOG_DEBUG, "Verify complete.");
    valid = true;
    break;
  default:
    return;
  }
  emit verifyFinished(result, pic);
}

// Private helpers

bool Fingerprint::loadData() { // Loads fingerprint data for this finger and
                               // device and puts it into the device
  struct stat bStat;
  pid_t child;
  int rc;
  struct passwd *pws = getpwuid(geteuid());
  string tempfilename = string("/tmp/read-");
  string sourcefilename = string(DATA_DIR);
  string user(pws->pw_name);
  string filename = ("");
  std::ostringstream o;
  o << finger;
  filename.append(o.str());
  filename.append(DATA_EXT);
  tempfilename.append(o.str());
  tempfilename.append(DATA_EXT);
  sourcefilename.append(user.data());
  sourcefilename.append("/");
  sourcefilename.append(device->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  sourcefilename.append("/");
  sourcefilename.append(o.str());
  sourcefilename.append(DATA_EXT);

  if (sourcefilename.empty())
    return false;

  if (stat(sourcefilename.data(), &bStat) != 0) // File doesn't exist
    return false;

  syslog(LOG_DEBUG, "Parent PID: %d.", getpid());
  child = fork(); // Here we start a child process that copies fingerprint data
                  // to a temporary file
  switch (child) {
  case 0: // This is the child
    rc = execl("/usr/bin/pkexec", "pkexec", READ_COMMAND, ARG_USER,
               pws->pw_name, ARG_DRIVER,
               device->getDisplayName(DISPLAY_DRIVER_NAME)->data(), ARG_FILE,
               filename.data(), debugTest ? ARG_DEBUG1 : nullptr, nullptr);
    syslog(LOG_ERR, "ERROR: Could not execute %s %d (%s).", READ_COMMAND, rc,
           strerror(errno));
    _exit(EXIT_FAILURE);
  case -1: // Fork error
    syslog(LOG_ERR, "ERROR FORKING CHILD PROCESS.");
    return false;
  default: // This is the parent
    syslog(LOG_DEBUG, "Child PID: %d.", child);
    waitpid(child, &rc, 0);
    if (rc != EXIT_SUCCESS) {
      syslog(LOG_ERR, "ERROR: %s returned %d.", READ_COMMAND_NAME, rc);
      return false;
    }
  }

  ifstream birFile(tempfilename.data(), ios_base::binary);
  if (birFile.is_open()) {
    birFile.seekg(0, ios::end);
    dataSize = birFile.tellg();
    if (dataSize == 0) {
      birFile.close();
      return false;
    }
    birFile.seekg(0, ios::beg);
    data = new char[dataSize];
    birFile.read((char *)data, dataSize);
    birFile.close();
    syslog(LOG_DEBUG, "Load data from %s (%d bytes).", tempfilename.data(),
           dataSize);
    if (unlink(tempfilename.data())) {
      syslog(LOG_ERR, "Could not delete file %s. Aborting!",
             tempfilename.data());
      return false;
    }
  } else {
    return false;
  }
  device->setData(data, dataSize);
  return true;
}

bool Fingerprint::saveData() { // Saves fingerprint data for this finger and
                               // device to the disk
  pid_t child;
  int rc;
  struct passwd *pws = getpwuid(geteuid());
  string devname(device->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  // bir filename
  string fname = string("/tmp/");
  string filename = string("");
  std::ostringstream o;
  o << finger;
  filename.append(o.str());
  filename.append(DATA_EXT);
  fname.append(filename);
  ofstream birFile(fname.data(), ios_base::binary | ios_base::out);
  if (birFile.is_open()) {
    birFile.write((const char *)data, dataSize);
    birFile.close();
  } else {
    syslog(LOG_ERR, "Could not temporary save %s.", fname.data());
    return false;
  }
  std::ostringstream fin;
  fin << finger;

  syslog(LOG_DEBUG, "Parent PID: %d.", getpid());
  child = fork(); // Here we start a child process that saves fingerprint data
  switch (child) {
  case 0: // This is the child
    rc = execl("/usr/bin/pkexec", "pkexec", WRITE_COMMAND, ARG_USER,
               pws->pw_name, ARG_DRIVER, devname.data(), ARG_FILE,
               filename.data(), debugTest ? ARG_DEBUG1 : nullptr, nullptr);
    syslog(LOG_ERR, "ERROR: Could not execute %s %d (%s).", WRITE_COMMAND, rc,
           strerror(errno));
    _exit(EXIT_FAILURE);
  case -1: // Fork error
    syslog(LOG_ERR, "ERROR FORKING CHILD PROCESS.");
    return false;
  default: // This is the parent
    syslog(LOG_DEBUG, "Child PID: %d.", child);
    waitpid(child, &rc, 0);
    if (rc != EXIT_SUCCESS) {
      syslog(LOG_ERR, "ERROR: %s returned %d.", WRITE_COMMAND_NAME, rc);
      return false;
    }
  }
  return true;
}

void Fingerprint::initLabels() {
  textLabels[0]->setText(tr("Waiting..."));
  textLabels[1]->setText("");
  textLabels[2]->setText("");
  textLabels[3]->setText("");
  textLabels[4]->setText("");
  iconLabels[0]->setPixmap(
      QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-wait.png")));
  iconLabels[1]->setPixmap(QPixmap());
  iconLabels[2]->setPixmap(QPixmap());
  iconLabels[3]->setPixmap(QPixmap());
  iconLabels[4]->setPixmap(QPixmap());
}

void Fingerprint::setAcquireStage(int result) {
  if (result == -1) { // Initial
    stage = 0;
    initLabels();
    return;
  }
  switch (result) {
  case RESULT_ENROLL_COMPLETE:
    syslog(LOG_DEBUG, "Acquire stage %d OK.", stage);
    textLabels[stage % 5]->setText(tr("OK"));
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-ok.png")));
    return;
  case RESULT_ENROLL_RETRY_TOO_SHORT:
    syslog(LOG_DEBUG, "Acquire stage %d swipe too short...", stage);
    textLabels[stage % 5]->setText(tr("Swipe too short..."));
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_ENROLL_RETRY_CENTER:
    syslog(LOG_DEBUG, "Acquire stage %d please center...", stage);
    textLabels[stage % 5]->setText(tr("Please center..."));
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_ENROLL_RETRY:
  case RESULT_ENROLL_RETRY_REMOVE:
    syslog(LOG_DEBUG, "Acquire stage %d try again...", stage);
    textLabels[stage % 5]->setText(tr("Try again..."));
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_ENROLL_PASS:
    syslog(LOG_DEBUG, "Acquire stage %d OK.", stage);
    textLabels[stage % 5]->setText(tr("OK"));
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-ok.png")));
    stage++;
    if (stage % 5 == 0)
      initLabels();
    emit neededStages(stage % 5 +
                      1); // libbsapi has a dynamic number of needed stages
    break;
  case RESULT_SWIPE:
    syslog(LOG_DEBUG, "Acquire stage %d waiting...", stage);
    iconLabels[stage % 5]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-wait.png")));
    break;
  default:
    syslog(LOG_ERR, "Acquire invalid result code!");
    setAcquireStage(-1);
    return;
  }
}

void Fingerprint::setVerifyStage(int result) {
  switch (result) {
  case RESULT_VERIFY_NO_MATCH:
    syslog(LOG_DEBUG, "Verify no match");
    textLabels[0]->setText(tr("No match!"));
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_VERIFY_MATCH:
    syslog(LOG_DEBUG, "Verify OK");
    textLabels[0]->setText(tr("OK"));
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-ok.png")));
    break;
  case RESULT_VERIFY_RETRY_TOO_SHORT:
    syslog(LOG_DEBUG, "Verify swipe too short...");
    textLabels[0]->setText(tr("Swipe too short..."));
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_VERIFY_RETRY_CENTER:
    syslog(LOG_DEBUG, "Verify please center...");
    textLabels[0]->setText(tr("Please center..."));
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_VERIFY_RETRY:
  case RESULT_VERIFY_RETRY_REMOVE:
    syslog(LOG_DEBUG, "Verify try again...");
    textLabels[0]->setText(tr("Try again..."));
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
    break;
  case RESULT_SWIPE:
    syslog(LOG_DEBUG, "Verify waiting...");
    iconLabels[0]->setPixmap(
        QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-wait.png")));
    break;
  default:
    syslog(LOG_ERR, "Verify invalid result code!");
    return;
  }
}

#include "moc_Fingerprint.cpp"
