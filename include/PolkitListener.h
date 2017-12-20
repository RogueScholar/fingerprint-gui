/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PolkitListener.cpp, PolkitListener.h
 * Purpose: Listens for polkit events
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

#ifndef POLKITLISTENER_H
#define	POLKITLISTENER_H

#include <polkit-qt-1/PolkitQt1/Agent/Listener>
#include "PolkitDialogImpl.h"

using namespace PolkitQt1::Agent;

class PolkitListener : public Listener {
    Q_OBJECT
public:
    PolkitListener(QObject *parent=0);
    virtual ~PolkitListener();

public slots:
    void initiateAuthentication(
        const QString &actionId,
        const QString &message,
        const QString &iconName,
        const PolkitQt1::Details &details,
        const QString &cookie,
        const PolkitQt1::Identity::List &identities,
        PolkitQt1::Agent::AsyncResult* result);
    bool initiateAuthenticationFinish();
    void cancelAuthentication();
    void tryAgain();
    void finishObtainPrivilege();
    void request(const QString &request,bool echo);
    void completed(bool gainedAuthorization);
    void showError(const QString &text);

private:
    PolkitDialogImpl *dialog;
    bool inProgress;
    bool gainedAuthorization;
    bool wasCancelled;
    int numTries;
    QWeakPointer<Session> session;
    PolkitQt1::Identity::List identities;
    PolkitQt1::Identity selectedUser;
    PolkitQt1::Agent::AsyncResult* result;
    QString cookie;
private slots:
    void dialogAccepted();
    void dialogCanceled();
    void userSelected(PolkitQt1::Identity identity);
};
#endif	/* POLKITLISTENER_H */
