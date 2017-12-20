/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: SavedDialogImpl.cpp, SavedDialogImpl.h
 * Purpose: Dialog after fingerprint verification or enrollment
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

#ifndef _SAVEDDIALOGIMPL_H
#define _SAVEDDIALOGIMPL_H

#include <string>
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include "ui_SavedDialog.h"

#include "Globals.h"

using namespace std;

typedef enum{
    SAVED_YES      = 0,    //One more finger  
    SAVED_NO       = 1,    //Go ahead
} savedDialogChoice;

typedef enum{
    MODE_SAVED,
    MODE_NOT_SAVED,
    MODE_VERIFIED,
    MODE_NOT_VERIFIED,
} saveDialogMode;

class SavedDialogImpl : public QDialog, public Ui::SavedDialog
{
Q_OBJECT

private:
    QPixmap fpPix;

public:
    SavedDialogImpl(int mode, QWidget * parent = 0, struct fp_pic_data *pic = NULL, Qt::WFlags f = 0 );

signals:
    void choice(savedDialogChoice);

private slots:
    void yesChoice();
    void noChoice();
};

#endif /* _SAVEDDIALOGIMPL_H */
