/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamGUI.cpp, PamGUI.h
 * Purpose: Main object for pam_fingerprint module for running in GUI
 * environments SPDX-License-Identifier: GPL-3.0-or-later
 *
 * @author  Wolfgang Ullrich
 * Copyright (C) 2008-2016 Wolfgang Ullrich
 */

/*
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
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
  // used for authentication
  PamGUI(FingerprintDevice *device, const char *user = NULL,
         const char *finger = NULL);
  // used for identification
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
