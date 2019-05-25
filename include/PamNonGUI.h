/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamNonGUI.cpp, PamNonGUI.h
 * Purpose: Main object for libpam_fingerprint module for running in non-gui environments
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

#ifndef _PAMNONGUI_H
#define	_PAMNONGUI_H

#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <QObject>
#include <iostream>
#include <string>
#include <termios.h>
#include "FingerprintDevice.h"
#include "FingerprintData.h"
#include "FingerprintDiscoverer.h"
#include "DeviceHandler.h"

#include "Globals.h"

//NonGUI object ----------------------------------------------------------------
class PamNonGUI : public QObject {
    Q_OBJECT

public:
    volatile int result;    // Result code:
                            // -2   -- still waiting for result
                            // -1   -- no match / not idetified
                            // >=0  -- index of identified fingerprint
private:
    QTimer *timer;
    int repeatDelay;
    FingerprintDevice *device;
    const char *finger;
    bool prompt;
    void pamMessage(const char* target,const char *style,const char *msg);
public:
    //used for authentication
    PamNonGUI(bool writeToPrompt,FingerprintDevice *device,const char *user=NULL,const char *finger=NULL,QObject* parent=0);
    virtual ~PamNonGUI();

public slots:
    void timerTick();
    void matchResult(int match,struct fp_pic_data *pic);
    void newVerifyResult(int result,struct fp_pic_data *pic);
};

#endif	/* _PAMNONGUI_H */

