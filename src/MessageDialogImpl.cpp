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

#include <sys/param.h>

#include "MessageDialogImpl.h"

MessageDialogImpl::MessageDialogImpl(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f) {
  setupUi(this);
  okButton->setDefault(true);
  connect(okButton, SIGNAL(clicked()), this, SLOT(ok()));
}

// Slots
void MessageDialogImpl::ok() { accept(); }

#include "moc_MessageDialogImpl.cpp"
