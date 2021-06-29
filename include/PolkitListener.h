/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PolkitListener.cpp, PolkitListener.h
 * Purpose: Listens for polkit events
 *
 * @author Wolfgang Ullrich
 */

#ifndef POLKITLISTENER_H
#define POLKITLISTENER_H

#include "PolkitDialogImpl.h"
#include <polkit-qt5-1/PolkitQt1/Agent/Listener>

using namespace PolkitQt1::Agent;

class PolkitListener : public Listener {
  Q_OBJECT
public:
  PolkitListener(QObject *parent = 0);
  virtual ~PolkitListener();

public slots:
  void initiateAuthentication(const QString &actionId, const QString &message,
                              const QString &iconName,
                              const PolkitQt1::Details &details,
                              const QString &cookie,
                              const PolkitQt1::Identity::List &identities,
                              PolkitQt1::Agent::AsyncResult *result);
  bool initiateAuthenticationFinish();
  void cancelAuthentication();
  void tryAgain();
  void finishObtainPrivilege();
  void request(const QString &request, bool echo);
  void completed(bool gainedAuthorization);
  void showError(const QString &text);

private:
  PolkitDialogImpl *dialog;
  bool inProgress;
  bool gainedAuthorization;
  bool wasCancelled;
  int numTries;
  QSharedPointer<Session> session;
  PolkitQt1::Identity::List identities;
  PolkitQt1::Identity selectedUser;
  PolkitQt1::Agent::AsyncResult *result;
  QString cookie;
private slots:
  void dialogAccepted();
  void dialogCanceled();
  void userSelected(PolkitQt1::Identity identity);
};
#endif /* POLKITLISTENER_H */
