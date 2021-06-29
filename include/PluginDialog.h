/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PluginDialog.cpp,PluginDialog.h
 * Purpose: GUI dialog requesting finger swipes
 *
 * @author Wolfgang Ullrich
 */

#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#define _MULTI_THREADED

#include "Globals.h"
#include "ui_FingerprintPlugin.h"
#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QtWidgets>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

class FifoReader : public QThread {
  Q_OBJECT
private:
  int fifo;
  QLabel *label;
  QLabel *statusBar;

protected:
  void run();

public:
  FifoReader(QLabel *label, QLabel *statusBar);
signals:
  void showPlugin();
  void stopPlugin();
  void okReceived();
  void userAuthenticated();
};

class PluginDialog : public QFrame, public Ui::MainFrame {
  Q_OBJECT
private:
  QDialog *parent;
  bool exitOnStop;

public:
  PluginDialog(QDialog *parent, bool exitOnStop);
  virtual ~PluginDialog();
  FifoReader *fifoReader;
signals:
  void userAuthenticated();
  void pluginStopped();
public slots:
  void stopPlugin();
  void showPlugin();
};
#endif /* PLUGINDIALOG_H */
