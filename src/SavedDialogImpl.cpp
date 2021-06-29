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

#include "SavedDialogImpl.h"
#include "GlobalsImg.h"

SavedDialogImpl::SavedDialogImpl(int mode, QWidget *parent,
                                 struct fp_pic_data *pic, Qt::WindowFlags f)
    : QDialog(parent, f) {
  setupUi(this);

  QString s; // ="Fingerprint was ";
  QString t;
  switch (mode) {
  case MODE_SAVED:
    s = tr("Fingerprint saved to disk.");
    t = tr("Fingerprint OK");
    yesButton->setDefault(true);
    break;
  case MODE_NOT_SAVED:
    s = tr("Fingerprint not saved. Click \"No\" to retry.");
    t = tr("Fingerprint fail!");
    noButton->setDefault(true);
    break;
  case MODE_VERIFIED:
    s = tr("Fingerprint verified.");
    t = tr("Fingerprint OK");
    yesButton->setDefault(true);
    break;
  case MODE_NOT_VERIFIED:
    s = tr("Fingerprint NOT verified. Click \"No\" to retry.");
    t = tr("Fingerprint fail!");
    noButton->setDefault(true);
    break;
  }

  if (nullptr != pic->data) {
    int height = pic->height, width = pic->width;
    QSize max = fp_img->maximumSize();
    if (height > max.height()) {
      width /= height / max.height();
      height = max.height();
    }
    if (width > max.width()) {
      height /= width / max.width();
      width = max.width();
    }
    createQPixmapFromFpImg(&fpPix, pic, width, height);
    fp_img->setPixmap(fpPix);
  } else {
    fp_img->hide();
    adjustSize();
  }

  syslog(LOG_DEBUG, "%s", s.toStdString().data());
  setWindowTitle(t);
  modeLabel->setText(s);
  connect(yesButton, SIGNAL(clicked()), this, SLOT(yesChoice()));
  connect(noButton, SIGNAL(clicked()), this, SLOT(noChoice()));
}

// Slots
void SavedDialogImpl::yesChoice() {
  syslog(LOG_DEBUG, "YES.");
  emit choice(SAVED_YES);
  close();
}

void SavedDialogImpl::noChoice() {
  syslog(LOG_DEBUG, "NO.");
  emit choice(SAVED_NO);
  close();
}

#include "moc_SavedDialogImpl.cpp"
