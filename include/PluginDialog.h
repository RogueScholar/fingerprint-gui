/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PluginDialog.cpp,PluginDialog.h
 * Purpose: GUI dialog requesting finger swipes
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

#ifndef PLUGINDIALOG_H
#define	PLUGINDIALOG_H

#define _MULTI_THREADED

#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <QtGui>
#include "ui_FingerprintPlugin.h"
#include "Globals.h"

class FifoReader : public QThread {
    Q_OBJECT
private:
    int fifo;
    QLabel *label;
    QLabel *statusBar;
protected:
    void run();
public:
    FifoReader(QLabel *label,QLabel *statusBar);
signals:
    void showPlugin();
    void stopPlugin();
    void okReceived();
    void userAuthenticated();
};

class PluginDialog : public QFrame, public Ui::MainFrame {
    Q_OBJECT
private:
    QDialog *parent;
    bool exitOnStop;
public:
    PluginDialog(QDialog *parent,bool exitOnStop);
    virtual ~PluginDialog();
    FifoReader *fifoReader;
signals:
    void userAuthenticated();
    void pluginStopped();
public slots:
    void stopPlugin();
    void showPlugin();
};
#endif	/* PLUGINDIALOG_H */
