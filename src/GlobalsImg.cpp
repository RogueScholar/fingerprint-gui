/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: GlobalsImg.cpp
 *
 * @author Wolfgang Ullrich
 */

#include <QtGui>

#include "GlobalsImg.h"

void createQPixmapFromFpImg(QPixmap *pix, struct fp_pic_data *fp_pic,
                            unsigned int mw, unsigned int mh) {
  if (fp_pic == nullptr || (*fp_pic).data == nullptr) {
    *pix = QPixmap();
    return;
  }
  unsigned int width = (*fp_pic).width;
  unsigned int height = (*fp_pic).height;
  float aspect;
  QImage qImg = QImage((unsigned char *)(*fp_pic).data, width, height,
                       QImage::Format_RGB888);
  if (width > mw) {
    aspect = (float)mw / (float)width;
    width = mw;
    height = (int)(aspect * (float)height);
  }
  if (height > mh) {
    aspect = (float)mh / (float)height;
    height = mh;
    width = (int)(aspect * (float)width);
  }
  *pix = QPixmap::fromImage(qImg.scaled(width, height));
}

void freeQPixmapFromFpImg(QPixmap *pix) { *pix = QPixmap(); }
