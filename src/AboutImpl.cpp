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


#include "../include/AboutImpl.h"

AboutImpl::AboutImpl(QWidget *parent,Qt::WFlags f)
    : QDialog(parent,f){
    setupUi(this);

    string s="Version: ";
    s.append(VERSION);
    versionLabel->setText(QApplication::translate("AboutDialog", s.data(),0,QApplication::UnicodeUTF8));
    copyrightLabel->setText(QApplication::translate("AboutDialog", COPYRIGHT,0,QApplication::UnicodeUTF8));
    homeButton->setText(QApplication::translate("AboutDialog",HOMEPAGE,0,QApplication::UnicodeUTF8));
    bitcoinButton->setText(QApplication::translate("AboutDialog",BITCOINADDRESS,0,QApplication::UnicodeUTF8));
    connect(donateButton,SIGNAL(clicked()),this,SLOT(donate()));
    connect(licenseButton,SIGNAL(clicked()),this,SLOT(license()));
    connect(homeButton,SIGNAL(clicked()),this,SLOT(homepage()));
    connect(bitcoinButton,SIGNAL(clicked()),this,SLOT(bitcoin()));
}

// slots
void AboutImpl::bitcoin(){
    QClipboard *cb = QApplication::clipboard();
// set a text to the Clipboard
    cb->setText(BITCOINADDRESS);
}

void AboutImpl::donate(){
    QString s;
    s.append(HOMEPAGE);
    s.append(DONATE);
    QDesktopServices srv;
    srv.openUrl(QUrl(s));
}

void AboutImpl::license(){
    QDesktopServices srv;
    srv.openUrl(QUrl(LICENSE));
}

void AboutImpl::homepage(){
    QDesktopServices srv;
    srv.openUrl(QUrl(HOMEPAGE));
}
