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

#ifndef _IDENTIFIERGUI_H
#define _IDENTIFIERGUI_H

#include "DeviceHandler.h"
#include "FingerprintData.h"
#include "FingerprintDevice.h"
#include "FingerprintDiscoverer.h"
#include "Globals.h"
#include "ui_FingerprintIdentifier.h"
#include <QDesktopWidget>
#include <QEventLoop>
#include <QObject>
#include <QtGui>

class IdentifierGUI : public QMainWindow, public Ui::IdentifierWindow {
  Q_OBJECT

private:
  QMovie *movie;
  QTimer *timer;
  int repeatDelay;
  FingerprintDevice *device;
  FingerprintData *identifyData;
  QPixmap fpPix;

public:
  IdentifierGUI(bool decorated, FingerprintDevice *device,
                FingerprintData *identifyData, QWidget *parent = 0,
                Qt::WindowFlags f = 0);

public slots:
  void matchResult(int match, struct fp_pic_data *pic);
  void newVerifyResult(int result, struct fp_pic_data *pic);
  void timerTick();
  void keyPressEvent(QKeyEvent *e);
  void closeEvent(QCloseEvent *e);
};

#endif /* _IDENTIFIERGUI_H */
