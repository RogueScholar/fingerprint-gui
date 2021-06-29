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

#ifndef _PAMNONGUI_H
#define _PAMNONGUI_H

#include "DeviceHandler.h"
#include "FingerprintData.h"
#include "FingerprintDevice.h"
#include "FingerprintDiscoverer.h"
#include <QObject>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <termios.h>

#include "Globals.h"

// Non-GUI object
class PamNonGUI : public QObject {
  Q_OBJECT

public:
  volatile int result; // Result code:
                       // -2   -- still waiting for result
                       // -1   -- no match / not identified
                       // >=0  -- index of identified fingerprint
private:
  QTimer *timer;
  int repeatDelay;
  FingerprintDevice *device;
  const char *finger;
  bool prompt;
  void pamMessage(const char *target, const char *style, const char *msg);

public:
  // Used for authentication
  PamNonGUI(bool writeToPrompt, FingerprintDevice *device,
            const char *user = NULL, const char *finger = NULL,
            QObject *parent = 0);
  virtual ~PamNonGUI();

public slots:
  void timerTick();
  void matchResult(int match, struct fp_pic_data *pic);
  void newVerifyResult(int result, struct fp_pic_data *pic);
};

#endif /* _PAMNONGUI_H */
