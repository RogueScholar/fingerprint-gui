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

#include "SavedDialogImpl.h"
#include "GlobalsImg.h"

SavedDialogImpl::SavedDialogImpl(int mode, QWidget * parent, struct fp_pic_data *pic, Qt::WFlags f)
    : QDialog(parent, f){
    setupUi(this);

    QString s="Fingerprint was ";
    QString t="Fingerprint ";
    switch(mode){
        case MODE_SAVED:
            s.append("saved to disk.");
            t.append("OK");
            yesButton->setDefault(true);
            break;
        case MODE_NOT_SAVED:
            s.append("not saved. Click \"No\" to retry.");
            t.append("fail!");
            noButton->setDefault(true);
            break;
        case MODE_VERIFIED:
            s.append("verified.");
            t.append("OK");
            yesButton->setDefault(true);
            break;
        case MODE_NOT_VERIFIED:
            s.append("NOT verified. Click \"No\" to retry.");
            t.append("fail!");
            noButton->setDefault(true);
            break;
    }

    if ( NULL != pic->data ) {
        int height = pic->height, width = pic->width;
        QSize max = fp_img->maximumSize();
        if ( height > max.height() ) {
            width /= height / max.height();
            height = max.height();
        }
        if ( width > max.width() ) {
            height /= width / max.width();
            width = max.width();
        }
        createQPixmapFromFpImg ( &fpPix, pic, width, height );
        fp_img->setPixmap ( fpPix );
    }
    else {
        fp_img->hide();
	adjustSize();
    }

    syslog(LOG_DEBUG,"%s",s.toStdString().data());
    setWindowTitle(t);
    modeLabel->setText(s);
    connect(yesButton,SIGNAL(clicked()),this,SLOT(yesChoice()));
    connect(noButton,SIGNAL(clicked()),this,SLOT(noChoice()));
}

// slots -----------------------------------------------------------------------
void SavedDialogImpl::yesChoice(){
    syslog(LOG_DEBUG,"YES.");
    emit choice(SAVED_YES);
    close();
}

void SavedDialogImpl::noChoice(){
    syslog(LOG_DEBUG,"NO.");
    emit choice(SAVED_NO);
    close();
}

