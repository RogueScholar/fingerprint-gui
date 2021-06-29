/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: GlobalsImg.h
 *
 * @author Wolfgang Ullrich
 */

#ifndef _GLOBALSIMG_H
#define _GLOBALSIMG_H

#include "Globals.h"

void createQPixmapFromFpImg(QPixmap *pix, struct fp_pic_data *fp_pic,
                            unsigned int mw = 120, unsigned int mh = 240);
void freeQPixmapFromFpImg(QPixmap *pix);

#endif //_GLOBALSIMG_H
