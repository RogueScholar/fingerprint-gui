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

#include "ExistDialogImpl.h"

ExistDialogImpl::ExistDialogImpl(string finger, QWidget *parent,
                                 Qt::WindowFlags f)
    : QDialog(parent, f) {
  setupUi(this);

  QString s =
      QString(tr("A fingerprint for %1 exists already.")).arg(finger.data());
  syslog(LOG_INFO, "A fingerprint for %s exists already.", finger.data());
  fingerLabel->setText(s);
  connect(acquireButton, SIGNAL(clicked()), this, SLOT(acquireChoice()));
  connect(verifyButton, SIGNAL(clicked()), this, SLOT(verifyChoice()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelChoice()));
  verifyButton->setDefault(true);
}

// Slots
void ExistDialogImpl::cancelChoice() {
  syslog(LOG_INFO, "Clicked \"Cancel\".");
  emit choice(EXIST_CANCEL);
  close();
}

void ExistDialogImpl::verifyChoice() {
  syslog(LOG_INFO, "Clicked \"Verify\".");
  emit choice(EXIST_VERIFY);
  close();
}

void ExistDialogImpl::acquireChoice() {
  syslog(LOG_INFO, "Clicked \"Acquire\".");
  emit choice(EXIST_ACQUIRE);
  close();
}

#include "moc_ExistDialogImpl.cpp"
