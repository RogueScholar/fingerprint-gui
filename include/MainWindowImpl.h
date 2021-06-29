/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: MainWindowImpl.cpp, MainWindowImpl.h
 * Purpose: The main application module
 *
 * @author Wolfgang Ullrich
 */

#ifndef _MAINWINDOWIMPL_H
#define _MAINWINDOWIMPL_H

#include "DeviceHandler.h"
#include "ExistDialogImpl.h"
#include "Fingerprint.h"
#include "MessageDialogImpl.h"
#include "SavedDialogImpl.h"
#include "ui_FingerprintGUI.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string>

#include "Globals.h"

using namespace std;

typedef enum {
  DEVICE_TAB   = 0, // Chose Device
  FINGER_TAB   = 1, // Chose Finger
  SCAN_TAB     = 2, // Scan Finger
  SETTINGS_TAB = 3, // Settings/Test
  PASSWORD_TAB = 4, // Password export
  NO_TAB       = 5, // no more tabs
} tabIndex;

typedef struct {
  string name;
  bool identify;
  QRadioButton *button;
  bool implemented;
} pamService;

class MainWindowImpl : public QMainWindow, public Ui::mainWindow {
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
  QLabel *textLabels[5];
  QLabel *iconLabels[5];
  pamService services[10];
  QString passwdPath;
  QString passwdPasswd;
  QString passwdUUID;
  bool passwdReady;
  QPixmap fpPixMap;
  QPixmap fpPix;

public:
  MainWindowImpl(QWidget *parent = 0, Qt::WindowFlags f = 0);

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
  void acquireFinished(int, struct fp_pic_data *);
  void verifyFinished(int, struct fp_pic_data *);
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
