/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PolkitDialog.cpp, PolkitDialog.h
 * Purpose: GUI dialog for polkit agent fingerprint authentication
 *
 * @author Wolfgang Ullrich
 */

#ifndef POLKITDIALOGIMPL_H
#define POLKITDIALOGIMPL_H

#include "Globals.h"
#include "PluginDialog.h"
#include "ui_FingerprintPlugin.h"
#include "ui_PolkitDetails.h"
#include "ui_PolkitDialog.h"
#include <QDialog>
#include <QSharedPointer>
#include <QWidget>
#include <QtGui>
#include <polkit-qt5-1/PolkitQt1/Authority>
#include <polkit-qt5-1/PolkitQt1/Details>

class QStandardItemModel;

namespace PolkitQt1 {
class Details;
class Identity;
class ActionDescription;
} // namespace PolkitQt1

using namespace std;

class PolkitDetailsImpl : public QWidget, private Ui::PolkitDetails {
  Q_OBJECT
public:
  PolkitDetailsImpl(const PolkitQt1::Details &details,
                    PolkitQt1::ActionDescription *actionDescription,
                    const QString &appname, QWidget *parent);
};

class PolkitDialogImpl : public QDialog, public Ui::PolkitDialog {
  Q_OBJECT
public:
  PolkitDialogImpl(const QString &actionId, const QString &message,
                   const QString &iconName, const PolkitQt1::Details &details,
                   const PolkitQt1::Identity::List &identities,
                   QWidget *parent = nullptr, Qt::WindowFlags f = nullptr);
  virtual ~PolkitDialogImpl();
  QString password() const;
  void authenticationFailure();
  void setOptions();
  void setRequest(const QString &request, bool requiresAdmin);
  PluginDialog *pluginDialog;
  PolkitQt1::Identity userSelected();
  PolkitQt1::ActionDescription *actionDescription;
  bool preselectUser();

signals:
  void adminUserSelected(PolkitQt1::Identity);
private slots:
  void userComboboxIndexChanged(int index);
  void showDetails();
public slots:
  virtual void accept();
  void resize();

private:
  PolkitDetailsImpl *detailsDialog;
  QString appname;
  void createUserCombobox(const PolkitQt1::Identity::List &identities);
};
#endif /* POLKITDIALOGIMPL_H */
