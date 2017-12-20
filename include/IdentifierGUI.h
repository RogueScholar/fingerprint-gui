/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: IdentifierGUI.cpp, IdentifierGUI.h
 * Purpose: Main object for fingerprintIdentifier module for running in gui environments
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

#ifndef _IDENTIFIERGUI_H
#define	_IDENTIFIERGUI_H

#include <QtGui>
#include <QObject>
#include <QEventLoop>
#include "Globals.h"
#include "ui_FingerprintIdentifier.h"
#include "FingerprintDevice.h"
#include "FingerprintData.h"
#include "FingerprintDiscoverer.h"
#include "DeviceHandler.h"

class IdentifierGUI : public QMainWindow, public Ui::IdentifierWindow {
    Q_OBJECT

private:
    QMovie *movie;
    QTimer *timer;
    int repeatDelay;
    FingerprintDevice *device;
    FingerprintData *identifyData;
    QPixmap fpPix;

public:
    IdentifierGUI(bool decorated,FingerprintDevice *device,FingerprintData *identifyData,QWidget *parent=0,Qt::WFlags f=0);

public slots:
    void matchResult(int match,struct fp_pic_data *pic);
    void newVerifyResult(int result,struct fp_pic_data *pic);
    void timerTick();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);
};

#endif	/* _IDENTIFIERGUI_H */
