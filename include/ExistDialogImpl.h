/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: ExistDialogImpl.cpp, ExistDialogImpl.h
 * Purpose: A dialog when a fingerprint for this finger/device already exists
 *
 * @author Wolfgang Ullrich
 */

#ifndef _EXISTDIALOGIMPL_H
#define _EXISTDIALOGIMPL_H

#include "ui_ExistDialog.h"
#include <QObject>
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include <string>

#include "Globals.h"

using namespace std;

typedef enum {
  EXIST_VERIFY  = 0,  // Verify finger
  EXIST_ACQUIRE = 1,  // Acquire fingerprint new
  EXIST_CANCEL  = 2,  // Cancel
} existDialogChoice;

class ExistDialogImpl : public QDialog, public Ui::ExistDialog {
  Q_OBJECT

public:
  ExistDialogImpl(string finger, QWidget *parent = 0, Qt::WindowFlags f = 0);

signals:
  void choice(existDialogChoice);

private slots:
  void cancelChoice();
  void verifyChoice();
  void acquireChoice();
};
#endif /* _EXISTDIALOGIMPL_H */
