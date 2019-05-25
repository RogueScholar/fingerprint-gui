/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: MessageDialogImpl.cpp, MessageDialogImpl.h
 * Purpose: Dialog for error messages
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

#include <sys/param.h>

#include "MessageDialogImpl.h"

MessageDialogImpl::MessageDialogImpl(QWidget * parent, Qt::WindowFlags f)
    : QDialog(parent, f){
    setupUi(this);
    okButton->setDefault(true);
    connect(okButton,SIGNAL(clicked()),this,SLOT(ok()));
}

// slots -----------------------------------------------------------------------
void MessageDialogImpl::ok(){
    accept();
}
