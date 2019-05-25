/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamTester.cpp, PamTester.h
 * Purpose: Testing of PAM settings with "libpam_fingerprint.so"
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

#ifndef _PAMTESTER_H
#define	_PAMTESTER_H

#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <QtWidgets>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include "Globals.h"
#include "DeviceHandler.h"

using namespace std;

extern volatile bool stopTester;
extern bool debugTest;
extern string syslogIdent;

class TestFifoReader : public QThread {
    Q_OBJECT
private:
    int fifo;
    QLabel *label;
    QLabel *statusBar;
protected:
    void run();
public:
    TestFifoReader(QLabel *label,QLabel *statusBar);
};

//------------------------------------------------------------------------------

class PamTester : public QObject {
    Q_OBJECT
private:
    const char *service;
    const char *user;
    struct pam_conv pamconv;
    pam_handle_t *pamh;
    QLineEdit *line;
    QLabel *testLabel1;
    QLabel *testLabel2;
    TestFifoReader *fifoReader;

public:
    PamTester(QLabel *label1,QLabel *label2,const char *service,bool identify);
    void testPam(DeviceHandler *deviceHandler,QLineEdit *result);

private slots:
    void haveResult();
};


#endif	/* _PAMTESTER_H */

