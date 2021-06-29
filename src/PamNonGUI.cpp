/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamNonGUI.cpp, PamNonGUI.h
 * Purpose: Main object for libpam_fingerprint module for running in non-GUI
 *          environments
 *
 * @author Wolfgang Ullrich
 */

#include "PamNonGUI.h"
#include "FingerprintHelper.h"
#include <unistd.h>

#define NORMAL "[0;39m"
#define RED "[1;31m"
#define GREEN "[1;32m"
#define YELLOW "[1;33m"
#define BLUE "[1;34m"
#define MAGENTA "[1;35m"
#define CYAN "[1;36m"
#define WHITE "[1;37m"

// Helper for sending messages to the PAM prompt
void PamNonGUI::pamMessage(const char *target, const char *style,
                           const char *msg) {
  if (prompt)
    printf("%s%s%s\n", style, msg, NORMAL);
  if (target == nullptr)
    return;
  string fifoMsg(""); // Compose a message for fingerprint-plugin
  fifoMsg.append(target);
  fifoMsg.append(msg);
  fifoMsg.append("\0");
  pluginMessage(fifoMsg.data());
}

// Non-GUI object
PamNonGUI::PamNonGUI(bool writeToPrompt, FingerprintDevice *dev,
                     const char *user, const char *fing, QObject *parent)
    : QObject(parent) {
  result = -2;
  repeatDelay = 0;
  device = dev;
  finger = fing;
  prompt = writeToPrompt;

  connect(device, SIGNAL(matchResult(int, struct fp_pic_data *)), this,
          SLOT(matchResult(int, struct fp_pic_data *)));
  connect(device, SIGNAL(verifyResult(int, struct fp_pic_data *)), this,
          SLOT(newVerifyResult(int, struct fp_pic_data *)));
  device->start();
  usleep(100000);           // Give it a chance to stop with some error
  if (!device->isRunning()) // Exit quietly (device not running for some reason)
    return;

  string title = string("\nFingerprint Login ");
  title.append(VERSION);
  pamMessage(nullptr, MAGENTA, title.data());
  string s = string("Authenticating ");
  s.append(user);
  pamMessage(MSG_NORMAL, MAGENTA, s.data());
  s = string("Swipe your ");
  if (finger == nullptr)
    s.append("finger");
  else
    s.append(finger);
  s.append(" or type your password:");
  pamMessage(nullptr, MAGENTA, s.data());
  START_TIMER
}

PamNonGUI::~PamNonGUI() { device->stop(); }

// Slots
void PamNonGUI::matchResult(int match,
                            struct fp_pic_data __attribute__((unused)) * pic) {
  device->stop();
  if (match >= 0) {
    syslog(LOG_DEBUG, "showMessage: OK");
    pamMessage(MSG_BOLD, GREEN, "OK");
    timer->stop();
    // Exit with index (match) as exit code
    qApp->processEvents();
    device->wait(5000);
    result = match;
    qApp->exit(match);
    return;
  }
  syslog(LOG_DEBUG, "showMessage: Not identified!");
  pamMessage(MSG_BOLD, RED, "Not identified!");
  repeatDelay = 3; // Let 'em see the result before exiting
}

void PamNonGUI::newVerifyResult(int result, struct fp_pic_data
                                                __attribute__((unused)) *
                                                pic) {
  switch (result) {
  case RESULT_VERIFY_NO_MATCH:
    syslog(LOG_DEBUG, "showMessage: No match!");
    pamMessage(MSG_NORMAL, RED, "No match!");
    break;
  case RESULT_VERIFY_RETRY_TOO_SHORT:
    syslog(LOG_DEBUG, "showMessage: Swipe too short...");
    pamMessage(MSG_NORMAL, RED, "Swipe too short...");
    break;
  case RESULT_VERIFY_RETRY_CENTER:
    syslog(LOG_DEBUG, "showMessage: Please center...");
    pamMessage(MSG_NORMAL, RED, "Please center...");
    break;
  case RESULT_VERIFY_RETRY:
  case RESULT_VERIFY_RETRY_REMOVE:
    syslog(LOG_DEBUG, "showMessage: Try again...");
    pamMessage(MSG_NORMAL, RED, "Try again...");
    break;
  }
}

// Helper thread for restart
void PamNonGUI::timerTick() {
  string s;
  pluginMessage(MSG_ALIVE);
  switch (repeatDelay) {
  case 0:
    if (!device->isRunning()) {
      syslog(LOG_ERR, "ERROR: Fingerprint device not running.");
      qApp->exit(-1);
      return;
    }
    // Do nothing
    break;
  case 1:
    syslog(LOG_INFO, "Waiting for device to stop...");
    device->wait(5000);
    syslog(LOG_INFO, "Stopped, restarting");
    // Restart fingerprint scanner
    s = string("Swipe your ");
    if (finger == nullptr)
      s.append("finger");
    else
      s.append(finger);
    s.append(" or type your password:");
    pamMessage(nullptr, MAGENTA, s.data());
    device->start();
    repeatDelay--;
    break;
  default:
    repeatDelay--; // Still waiting...
  }
}

#include "moc_PamNonGUI.cpp"
