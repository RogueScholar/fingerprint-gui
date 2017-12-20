/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: MainWindowImpl.cpp, MainWindowImpl.h
 * Purpose: The main application module
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

#ifndef _MAINWINDOWIMPL_H
#define _MAINWINDOWIMPL_H

#include <string>
#include "ui_FingerprintGUI.h"
#include "DeviceHandler.h"
#include "Fingerprint.h"
#include "ExistDialogImpl.h"
#include "SavedDialogImpl.h"
#include "MessageDialogImpl.h"

#include "Globals.h"

using namespace std;

typedef enum {
        DEVICE_TAB      = 0,    //Chose Device  
        FINGER_TAB      = 1,    //Chose Finger
        SCAN_TAB        = 2,    //Scan Finger
        SETTINGS_TAB    = 3,    //Settings/Test
        PASSWORD_TAB    = 4,    //Password export
        NO_TAB          = 5,    //no more tabs
} tabIndex;

typedef struct {
    string name;
    bool identify;
    QRadioButton *button;
    bool implemented;
} pamService;

class MainWindowImpl : public QMainWindow, public Ui::mainWindow
{
Q_OBJECT
public:
    DeviceHandler *deviceHandler;
private:
    int currentTab;
    int currentFinger;
    QMovie *movie;
    Fingerprint *currentFingerprint;
    ExistDialogImpl *eDialog;
    SavedDialogImpl *sDialog;
    QLabel* textLabels[5];
    QLabel* iconLabels[5];
    pamService services[10];
    QString passwdPath;
    QString passwdPasswd;
    QString passwdUUID;
    bool passwdReady;
    QPixmap fpPixMap;
    QPixmap fpPix;

public:
    MainWindowImpl(QWidget * parent = 0, Qt::WindowFlags f = 0 );

private:
    void tabChanged(int newTab);
    void deviceTabToBack();
    void fingerTabToBack();
    void scanTabToBack();
    void settingsTabToBack();
    void passwordTabToBack();
    void deviceTabToFront();
    void fingerTabToFront();
    void scanTabToFront();
    void settingsTabToFront();
    void passwordTabToFront();
    void setLabel(int finger);
    void swipeFinger();
    void markFinger(int finger);
    bool haveFingerprints();
    bool getUuid(QString dir);

private slots:
    void closeApp();
    void nextTab();
    void tabChanged();
    void newDevice(string);
    void showAttachedUSBDevices();
    void lsChanged();
    void lrChanged();
    void lmChanged();
    void lpChanged();
    void ltChanged();
    void rsChanged();
    void rrChanged();
    void rmChanged();
    void rpChanged();
    void rtChanged();
    void setScanTabNeededStages(int);
    void acquireFinished(int,struct fp_pic_data*);
    void verifyFinished(int,struct fp_pic_data*);
    void existDialogChosen(existDialogChoice);
    void savedDialogChosen(savedDialogChoice);
    int saveToFile();
    void displayModeVendor();
    void displayModeDriver();
    void noDeviceOpen();
    void testPam();
    void showAbout();
    void showHelp();
    void showHomepage();
    void showForum();
    void findPamServices();
    void setPwdPath(QString);
    void setPwdPath1();
    void setPwdPath2();
    void enableSaveButton();
    void savePasswd();
};

#endif /* _MAINWINDOWIMPL_H */

