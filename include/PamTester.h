/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamTester.cpp, PamTester.h
 * Purpose: Testing of PAM settings with "libpam_fingerprint.so"
 *
 * @author Wolfgang Ullrich
 */

#ifndef _PAMTESTER_H
#define _PAMTESTER_H

#include "DeviceHandler.h"
#include "Globals.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QtWidgets>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <string>
#include <sys/stat.h>

using namespace std;

extern volatile bool stopTester;
extern bool debugTest;
extern string syslogIdent;

class TestFifoReader : public QThread {
  Q_OBJECT
private:
  int fifo;
  QLabel *label;
  QLabel *statusBar;

protected:
  void run();

public:
  TestFifoReader(QLabel *label, QLabel *statusBar);
};

class PamTester : public QObject {
  Q_OBJECT
private:
  const char *service;
  const char *user;
  struct pam_conv pamconv;
  pam_handle_t *pamh;
  QLineEdit *line;
  QLabel *testLabel1;
  QLabel *testLabel2;
  TestFifoReader *fifoReader;

public:
  PamTester(QLabel *label1, QLabel *label2, const char *service, bool identify);
  void testPam(DeviceHandler *deviceHandler, QLineEdit *result);

private slots:
  void haveResult();
};

#endif /* _PAMTESTER_H */
