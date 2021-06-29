/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: MessageDialogImpl.cpp, MessageDialogImpl.h
 * Purpose: Dialog for error messages
 *
 * @author Wolfgang Ullrich
 */

#ifndef _MESSAGEDIALOGIMPL_H
#define _MESSAGEDIALOGIMPL_H

#include "ui_Message.h"
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include <string>

#include "Globals.h"

using namespace std;

class MessageDialogImpl : public QDialog, public Ui::MessageDialog {
  Q_OBJECT

public:
  MessageDialogImpl(QWidget *parent = 0, Qt::WindowFlags f = 0);

private slots:
  void ok();
};

#endif /* _MESSAGEDIALOGIMPL_H */
