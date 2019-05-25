/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: AboutImpl.cpp, AboutImpl.h
 * Purpose: About dialog
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

#ifndef _ABOUTIMPL_H
#define	_ABOUTIMPL_H

#include <iostream>
#include <string>
#include <QtGui>
#include <QObject>
#include <qstring.h>
#include <qwidget.h>
#include "ui_About.h"

#include "Globals.h"

using namespace std;

class AboutImpl : public QDialog, public Ui::AboutDialog {
Q_OBJECT

public:
    AboutImpl(QWidget *parent=0,Qt::WFlags f=0);

private slots:
    void bitcoin();
    void donate();
    void license();
    void homepage();
};


#endif	/* _ABOUTIMPL_H */

