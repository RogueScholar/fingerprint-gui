/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "fingerprintGUI": Services for fingerprint authentication on Linux
 * Module: UserSettings.cpp, UserSettings.h
 * Purpose: User-specific persistent settings for password encryption/decryption
 *
 * @author Wolfgang Ullrich
 */

#ifndef _USERSETTINGS_H
#define _USERSETTINGS_H

#include <QString>
#include <QtCrypto>

class UserSettings {
public:
  bool providePassword;
  QString uuid;
  QString pathToPassword;
  QString xIv;
  QString xKey;
  QString xPass;

  UserSettings(char *userName, bool debug);
  UserSettings(char *extDir, char *uuid, char *userName, char *machineName);
  virtual ~UserSettings();
  bool writeConfig(char *, bool debug);
  bool getPassword(char **password);
  const char *getPathToMedia();

private:
  QString pathToConfig;
  QString password;
  bool umountRequired;
  QString passwordDir;
  QString user;

  // Mount device by UUID, return mount point or NULL
  QString mountUuid(QString uuid);
};

#endif /* _USERSETTINGS_H */
