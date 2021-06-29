/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PluginDialog.cpp,PluginDialog.h
 * Purpose: GUI dialog requesting finger swipes
 * SPDX-License-Identifier: GPL-3.0-or-later
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
