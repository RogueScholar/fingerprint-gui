/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: ExistDialogImpl.cpp, ExistDialogImpl.h
 * Purpose: A dialog when a fingerprint for this finger/device already exists
 *
 * @author  Wolfgang Ullrich
 * Copyright (C) 2008-2016 Wolfgang Ullrich
 */

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _EXISTDIALOGIMPL_H
#define	_EXISTDIALOGIMPL_H

#include <string>
#include <QtGui>
#include <QObject>
#include <qstring.h>
#include <qwidget.h>
#include "ui_ExistDialog.h"

#include "Globals.h"

using namespace std;

typedef enum {
        EXIST_VERIFY      = 0,    //Verify finger  
        EXIST_ACQUIRE     = 1,    //Acquire fingerprint new
        EXIST_CANCEL      = 2,    //Cancel
} existDialogChoice;

class ExistDialogImpl : public QDialog, public Ui::ExistDialog {
Q_OBJECT

public:
    ExistDialogImpl(string finger,QWidget * parent=0,Qt::WFlags f=0);

signals:
    void choice(existDialogChoice);

private slots:
    void cancelChoice();
    void verifyChoice();
    void acquireChoice();
};
#endif	/* _EXISTDIALOGIMPL_H */

