/*  This file is part of the KDE project
    Copyright (C) 2007-2008 Gökçen Eraslan <gokcen@pardus.org.tr>
    Copyright (C) 2008 Daniel Nicoletti <dantti85-pk@yahoo.com.br>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QtGui>
#include <QObject>
#include <qstring.h>
#include <qwidget.h>




#include "ui_AuthDialog.h"
#include "ui_authdetails.h"

class QStandardItemModel;

namespace PolkitQt1
{
class Details;
class Identity;
class ActionDescription;
}

class AuthDialog : public QDialog, private Ui::AuthDialog
{
    Q_OBJECT
public:
    AuthDialog(const QString &actionId,
               const QString &message,
               const QString &iconName,
               PolkitQt1::Details *details,
               QList<PolkitQt1::Identity *> identities);
    ~AuthDialog();

    void setRequest(const QString &request, bool requiresAdmin);
    void setOptions();
    QString password() const;
    void authenticationFailure();

    PolkitQt1::Identity *adminUserSelected();

    PolkitQt1::ActionDescription *m_actionDescription;

signals:
    void adminUserSelected(PolkitQt1::Identity *);

public slots:
    virtual void accept();

private slots:
    void on_userCB_currentIndexChanged(int index);

private:
    QStandardItemModel *m_userModelSIM;
    QString m_appname;

    void createUserCB(QList<PolkitQt1::Identity *> identities);
};

class AuthDetails : public QWidget, private Ui::AuthDetails
{
    Q_OBJECT
public:
    AuthDetails(PolkitQt1::Details *details,
                PolkitQt1::ActionDescription *actionDescription,
                const QString &appname,
                QWidget *parent);

private slots:
    void openUrl(const QString&);
    void openAction(const QString&);
};

#endif // AUTHDIALOG_H
