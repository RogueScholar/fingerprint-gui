/*
 * Project "fingerprintGUI": Services for fingerprint authentication on Linux
 * Module: UserSettings.cpp, UserSettings.h
 * Purpose: User specific persistent settings; Password encryption/decryption
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

#ifndef _USERSETTINGS_H
#define	_USERSETTINGS_H

#include <QString>
#include <QtCrypto/QtCrypto>

class UserSettings {
public:
    bool providePassword;
    QString uuid;
    QString pathToPassword;
    QString xIv;
    QString xKey;
    QString xPass;

    UserSettings(char *userName,bool debug);
    UserSettings(char *extDir,char *uuid,char *userName,char *machineName);
    virtual ~UserSettings();
    bool writeConfig(char*,bool debug);
    bool getPassword(char **password);
    const char* getPathToMedia();
private:
    QString pathToConfig;
    QString password;
    bool umountRequired;
    QString passwordDir;
    QString user;

    // mount device by uuid, return mountpoint or NULL
    QString mountUuid(QString uuid);
};

#endif	/* _USERSETTINGS_H */

