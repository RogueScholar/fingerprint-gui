/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: SavedDialogImpl.cpp, SavedDialogImpl.h
 * Purpose: Dialog after fingerprint verification or enrollment
 *
 * @author Wolfgang Ullrich
 */

#ifndef _SAVEDDIALOGIMPL_H
#define _SAVEDDIALOGIMPL_H

#include "ui_SavedDialog.h"
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include <string>

#include "Globals.h"

using namespace std;

typedef enum {
  SAVED_YES = 0, // One more finger
  SAVED_NO  = 1, // Go ahead
} savedDialogChoice;

typedef enum {
  MODE_SAVED,
  MODE_NOT_SAVED,
  MODE_VERIFIED,
  MODE_NOT_VERIFIED,
} saveDialogMode;

class SavedDialogImpl : public QDialog, public Ui::SavedDialog {
  Q_OBJECT

private:
  QPixmap fpPix;

public:
  SavedDialogImpl(int mode, QWidget *parent = 0, struct fp_pic_data *pic = NULL,
                  Qt::WindowFlags f = 0);

signals:
  void choice(savedDialogChoice);

private slots:
  void yesChoice();
  void noChoice();
};

#endif /* _SAVEDDIALOGIMPL_H */
