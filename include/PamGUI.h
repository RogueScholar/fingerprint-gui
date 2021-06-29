/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamGUI.cpp, PamGUI.h
 * Purpose: Main object for pam_fingerprint module for running in GUI
 *          environments
 *
 * @author Wolfgang Ullrich
 */

#ifndef _PAMGUI_H
#define _PAMGUI_H

#include "DeviceHandler.h"
#include "FingerprintData.h"
#include "FingerprintDevice.h"
#include "FingerprintDiscoverer.h"
#include "Globals.h"
#include "ui_FingerprintPlugin.h"
#include <QEventLoop>
#include <QObject>
#include <QX11Info>
#include <QtWidgets>
#include <errno.h>
#include <fcntl.h>
#include <security/pam_modules.h>
#include <string>
#include <sys/stat.h>

class PamGUI : public QFrame, public Ui::MainFrame {
  Q_OBJECT

private:
  QTimer *timer;
  int repeatDelay;
  QMovie *movie;
  FingerprintDevice *device;
  FingerprintData *identifyData;
  QPixmap fpPix;

public:
  // Used for authentication
  PamGUI(FingerprintDevice *device, const char *user = NULL,
         const char *finger = NULL);
  // Used for identification
  PamGUI(FingerprintDevice *device, FingerprintData *identifyData);
  virtual ~PamGUI();

private:
  void startupGUI(FingerprintDevice *dev);
  void showMessage(const char *, const QString msg);
  void setFocusToUnityGreeter();
  void CinnamonFix(); // Fix cinnamon-screensaver

public slots:
  void timerTick();
  void matchResult(int match, struct fp_pic_data *pic);
  void newVerifyResult(int result, struct fp_pic_data *pic);
};

#endif /* _PAMGUI_H */
