/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: IdentifierGUI.cpp, IdentifierGUI.h
 * Purpose: Main object for fingerprintIdentifier module for running in GUI
 *          environments
 *
 * @author Wolfgang Ullrich
 */

#include "IdentifierGUI.h"
#include "GlobalsImg.h"
#include <iostream>
#include <string>
#include <unistd.h>

#define KEEP_ON_TOP                                                            \
  raise();                                                                     \
  activateWindow();

IdentifierGUI::IdentifierGUI(bool decorated, FingerprintDevice *dev,
                             FingerprintData *iData, QWidget *parent,
                             Qt::WindowFlags f)
    : QMainWindow(parent, f) {
  setupUi(this);

  if (!decorated) {
    UNDECORATED_MODAL_WINDOW_CENTERED
  } else {
    setWindowFlags(Qt::Dialog);
    // Title of the dialog (also the name of this module)
    string title = string(QT_TR_NOOP("Fingerprint Identifier "));
    title.append(VERSION);
    setWindowTitle(
        QApplication::translate("MainWindow", title.data(), nullptr));
    SET_TEXT_COLOR
  }

  ANIMATION_MOVIE

  device = dev;
  device->setTimeout(false);
  identifyData = iData;
  repeatDelay = 0;

  syslog(LOG_DEBUG, "Please swipe your finger");

  connect(device, SIGNAL(matchResult(int, struct fp_pic_data *)), this,
          SLOT(matchResult(int, struct fp_pic_data *)));
  connect(device, SIGNAL(verifyResult(int, struct fp_pic_data *)), this,
          SLOT(newVerifyResult(int, struct fp_pic_data *)));
  device->start();
  show();
  KEEP_ON_TOP
  START_TIMER

  fpPix = QPixmap();

  /*
      QFont font;
      font.setPointSize(9);
      font.setBold(false);
      statusBar()->setFont(font);
  */
  statusBar()->showMessage(tr("Ready..."));
  syslog(LOG_INFO, "Ready...");
}

// Slots
void IdentifierGUI::matchResult(int match, struct fp_pic_data *pic) {
  syslog(LOG_DEBUG, "MatchResult %d.", match);
  device->stop();
  statusBar()->clearMessage();
  if (!fpPix.isNull()) {
    freeQPixmapFromFpImg(&fpPix);
  }
  createQPixmapFromFpImg(&fpPix, pic, animationLabel->width(),
                         animationLabel->height());
  if (!fpPix.isNull()) {
    animationLabel->setMovie(nullptr);
    animationLabel->setPixmap(fpPix);
  }
  /*
      QFont font;
      font.setPointSize(12);
      font.setBold(true);
      statusBar()->setFont(font);
  */
  if (match >= 0) {
    timer->stop();
    movie->setPaused(true);
    releaseKeyboard();

    FingerprintData *fingerprintData = identifyData;
    for (int i = 0; i < match; i++)
      fingerprintData = fingerprintData->next;
    syslog(LOG_DEBUG, "Identified: %s (%s).",
           fingerprintData->getUserName()->data(),
           fingerprintData->getFingerName());
    // %1 = user name %2 = finger name
    QString message = tr("Identified: %1 (%2)")
                          .arg(fingerprintData->getUserName()->data())
                          .arg(fingerprintData->getFingerName());
    statusBar()->showMessage(message);
    // for(int i=SHOW_DELAY/1000;i>0;i--){ //let 'em see the result before exit
    qApp->processEvents();
    usleep(SHOW_DELAY);
    //            usleep(1000);
    //        }

    // Exit with index (match) as exit code
    qApp->exit(match);
    return;
  }
  syslog(LOG_DEBUG, "showMessage: Not identified!");
  statusBar()->showMessage(tr("Not identified!"));
  repeatDelay = 2; // Let 'em see the result before exiting
}

void IdentifierGUI::newVerifyResult(int result, struct fp_pic_data *pic) {
  movie->setPaused(true);
  if (!fpPix.isNull()) {
    freeQPixmapFromFpImg(&fpPix);
  }
  createQPixmapFromFpImg(&fpPix, pic, animationLabel->width(),
                         animationLabel->height());
  if (!fpPix.isNull()) {
    animationLabel->setMovie(nullptr);
    animationLabel->setPixmap(fpPix);
  }
  switch (result) {
  case RESULT_VERIFY_NO_MATCH:
    syslog(LOG_DEBUG, "showMessage: No match!");
    statusBar()->showMessage(tr("No match!"));
    break;
  case RESULT_VERIFY_RETRY_TOO_SHORT:
    syslog(LOG_DEBUG, "showMessage: Swipe too short...");
    statusBar()->showMessage(tr("Swipe too short..."));
    break;
  case RESULT_VERIFY_RETRY_CENTER:
    syslog(LOG_DEBUG, "showMessage: Please center...");
    statusBar()->showMessage(tr("Please center..."));
    break;
  case RESULT_VERIFY_RETRY:
  case RESULT_VERIFY_RETRY_REMOVE:
    syslog(LOG_DEBUG, "showMessage: Try again...");
    statusBar()->showMessage(tr("Try again..."));
    break;
  }
  repeatDelay = 2; // Let 'em see the result before continuing
}

// We don't want to lose the keyboard, so we grab it with every timerTick
void IdentifierGUI::timerTick() {
  //    QFont font;

  KEEP_ON_TOP
  switch (repeatDelay) {
  case 0:
    statusBar()->showMessage(tr("Ready..."));
    break;
  case 1:
    // Restart the fingerprint scanner
    //            font.setPointSize(9);
    //            font.setBold(false);
    //            statusBar()->setFont(font);
    statusBar()->clearMessage();
    device->start();
    animationLabel->setMovie(movie);
    movie->start();
    statusBar()->showMessage(tr("Ready..."));
    syslog(LOG_INFO, "Ready...");
    repeatDelay--;
    break;
  default:
    repeatDelay--; // Still waiting
  }
}

void IdentifierGUI::keyPressEvent(QKeyEvent *e) {
  //    QFont font;
  switch (e->key()) {
  case Qt::Key_Enter:
  case Qt::Key_Return:
    device->stop();
    //            font.setPointSize(10);
    //            font.setBold(true);
    //            statusBar()->setFont(font);
    // Shown on the status bar when ENTER key gets pressed
    statusBar()->showMessage(tr("ENTER pressed."));
    qApp->processEvents();
    syslog(LOG_DEBUG, "showMessage: ENTER pressed.");
    usleep(SHOW_DELAY);
    break;
  default:
    return;
  }
  syslog(LOG_DEBUG, "Got ENTER. Aborting.");
  qApp->exit(-1);
}

void IdentifierGUI::closeEvent(QCloseEvent * /*e*/) {
  syslog(LOG_DEBUG, "Got closeEvent. Aborting.");
  device->stop();
  qApp->exit(-1);
}

#include "moc_IdentifierGUI.cpp"
