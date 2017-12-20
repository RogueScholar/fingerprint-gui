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

#include "ExistDialogImpl.h"

ExistDialogImpl::ExistDialogImpl(string finger, QWidget * parent, Qt::WFlags f)
    : QDialog(parent, f){
    setupUi(this);

    QString s("A fingerprint for ");
    s.append(finger.data());
    s.append(" exists already.");
    syslog(LOG_INFO,"A fingerprint for %s exists already.",finger.data());
    fingerLabel->setText(s);
    connect(acquireButton,SIGNAL(clicked()),this,SLOT(acquireChoice()));
    connect(verifyButton,SIGNAL(clicked()),this,SLOT(verifyChoice()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelChoice()));
    verifyButton->setDefault(true);
}

// slots -----------------------------------------------------------------------
void ExistDialogImpl::cancelChoice(){
    syslog(LOG_INFO,"Clicked \"Cancel\".");
    emit choice(EXIST_CANCEL);
    close();
}

void ExistDialogImpl::verifyChoice(){
    syslog(LOG_INFO,"Clicked \"Verify\".");
    emit choice(EXIST_VERIFY);
    close();
}

void ExistDialogImpl::acquireChoice(){
    syslog(LOG_INFO,"Clicked \"Acquire\".");
    emit choice(EXIST_ACQUIRE);
    close();
}
