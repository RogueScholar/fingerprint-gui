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

/*
 * This code is based on an analysis of the "polkit-kde-1" project, v0.95.1
 */

#include <polkit-qt5-1/PolkitQt1/Agent/Listener>
#include <polkit-qt5-1/PolkitQt1/Agent/Session>
#include <polkit-qt5-1/PolkitQt1/Details>
#include <polkit-qt5-1/PolkitQt1/Identity>
#include <polkit-qt5-1/PolkitQt1/Subject>
#include <qdialogbuttonbox.h>

#include "../include/Globals.h"
#include "../include/PolkitListener.h"

PolkitListener::PolkitListener(QObject *parent)
    : Listener(parent), inProgress(false), selectedUser(nullptr) {}

PolkitListener::~PolkitListener() {}

// initiateAuthentication message from polkit
void PolkitListener::initiateAuthentication(
    const QString &actionId, const QString &message, const QString &iconName,
    const PolkitQt1::Details &details, const QString &cookie,
    const PolkitQt1::Identity::List &identities,
    PolkitQt1::Agent::AsyncResult *result) {
  syslog(LOG_DEBUG, "Initiating authentication");
  if (inProgress) {
    syslog(LOG_ERR,
           "Another client is already authenticating, please try again later.");
    result->setError(
        "Another client is already authenticating, please try again later.");
    result->setCompleted();
    return;
  }
  this->identities = identities;
  this->cookie = cookie;
  this->result = result;
  session.clear();
  if (identities.length() == 1) {
    this->selectedUser = identities[0];
  } else {
    selectedUser = PolkitQt1::Identity();
  }

  inProgress = true;
  // Create the polkit dialog
  dialog =
      new PolkitDialogImpl(actionId, message, iconName, details, identities);
  connect(dialog->okButton, SIGNAL(clicked()), this, SLOT(dialogAccepted()));
  connect(dialog->passwordEdit, SIGNAL(returnPressed()), this,
          SLOT(dialogAccepted()));
  connect(dialog->cancelButton, SIGNAL(clicked()), this,
          SLOT(dialogCanceled()));
  connect(dialog, SIGNAL(rejected()), this, SLOT(dialogCanceled()));
  connect(dialog, SIGNAL(adminUserSelected(PolkitQt1::Identity)),
          SLOT(userSelected(PolkitQt1::Identity)));

  dialog->setOptions();
  dialog->show();
  dialog->raise();

  // dialog->setOptions();

  numTries = 0;
  wasCancelled = false;
  if (!dialog->preselectUser()) {
    tryAgain();
  }
}

void PolkitListener::finishObtainPrivilege() {
  // Number of tries increases only when some user is selected
  if (selectedUser.isValid()) {
    numTries++;
  }
  syslog(LOG_DEBUG, "Finishing obtaining privileges (G:%u, C:%u, D:%u).",
         gainedAuthorization, wasCancelled, (dialog != nullptr));
  if (!gainedAuthorization && !wasCancelled && (dialog != nullptr)) {
    dialog->authenticationFailure();
    if (numTries < 3) {
      session.data()->deleteLater();
      tryAgain();
      return;
    }
  }
  if (!session.isNull()) {
    session.data()->result()->setCompleted();
  } else {
    result->setCompleted();
  }
  session.data()->deleteLater();
  if (dialog) {
    delete (dialog);
    dialog = nullptr;
  }
  inProgress = false;
  syslog(LOG_DEBUG, "Finish obtain authorization: %u", gainedAuthorization);
}

void PolkitListener::tryAgain() {
  syslog(LOG_DEBUG, "Trying again.");
  // We will create a new session only when a user is selected
  if (selectedUser.isValid()) {
    session =
        QSharedPointer<Session>(new Session(selectedUser, cookie, result));
    connect(session.data(), SIGNAL(request(QString, bool)), this,
            SLOT(request(QString, bool)));
    connect(session.data(), SIGNAL(completed(bool)), this,
            SLOT(completed(bool)));
    connect(session.data(), SIGNAL(showError(QString)), this,
            SLOT(showError(QString)));
    session.data()->initiate();
  }
  if (dialog) {
    dialog->adjustSize();
  }
}

bool PolkitListener::initiateAuthenticationFinish() {
  syslog(LOG_DEBUG, "initiateAuthenticationFinish.");
  return true;
}

void PolkitListener::cancelAuthentication() {
  wasCancelled = true;
  syslog(LOG_DEBUG, "cancelAuthentication.");
  finishObtainPrivilege();
}

void PolkitListener::request(const QString &request, bool echo) {
  syslog(LOG_DEBUG, "Request \"%s\", echo: %u.", request.toStdString().data(),
         echo);
  if (dialog) {
    dialog->setRequest(request, echo);
    connect(dialog->pluginDialog->fifoReader, SIGNAL(userAuthenticated()),
            SLOT(dialogAccepted()));
    connect(dialog->pluginDialog->fifoReader, SIGNAL(stopPlugin()), dialog,
            SLOT(resize()));
  }
}

void PolkitListener::completed(bool gainedAuthorization) {
  syslog(LOG_DEBUG, "Completed: %u.", gainedAuthorization);
  this->gainedAuthorization = gainedAuthorization;
  finishObtainPrivilege();
}

void PolkitListener::showError(const QString &text) {
  syslog(LOG_DEBUG, "Error: \"%s\".", text.toStdString().data());
  if (dialog) {
    dialog->adjustSize();
  }
}

void PolkitListener::dialogAccepted() {
  syslog(LOG_DEBUG, "dialogAccepted.");
  if (!session.isNull()) {
    session.data()->setResponse(dialog->password());
  }
  //!!!!!!!!!!!!!!!! USE THIS LOG OUTPUT ONLY FOR DEVELOPMENT
  //!!!!!!!!!!!!!!!!!!!!!
  // syslog(LOG_DEBUG,"Got password
  // \"%s\".",dialog->password().toStdString().data());
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void PolkitListener::dialogCanceled() {
  syslog(LOG_DEBUG, "dialogCanceled.");
  wasCancelled = true;
  if (!session.isNull()) {
    session.data()->cancel();
  }
  finishObtainPrivilege();
}

void PolkitListener::userSelected(PolkitQt1::Identity identity) {
  syslog(LOG_DEBUG, "userSelected: %s.",
         identity.toString().remove("unix-user:").toStdString().data());
  selectedUser = identity;
  // If a user is selected, we must destroy the existing session
  if (!session.isNull()) {
    session.data()->deleteLater();
  }
  tryAgain();
}

#include "moc_PolkitListener.cpp"
