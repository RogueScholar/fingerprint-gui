/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PolkitDialog.cpp, PolkitDialog.h
 * Purpose: GUI dialog for polkit agent for fingerprint authentication
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

/*
 * This code is based on the analysis of the "polkit-kde-1-0.95.1" project
 */

#include <polkit-qt-1/PolkitQt1/Authority>
#include <polkit-qt-1/PolkitQt1/Details>
#include <pwd.h>
#include <sys/wait.h>

#include "../include/PolkitDialogImpl.h"
#include "../include/PluginDialog.h"

Q_DECLARE_METATYPE(PolkitQt1::Identity *);

PolkitDialogImpl::PolkitDialogImpl(
        const QString &actionId,
        const QString &message,
        const QString &/*iconName*/,
        const PolkitQt1::Details &details,
        const PolkitQt1::Identity::List &identities,
        QWidget * parent,Qt::WindowFlags f)
    : QDialog(parent,f){

    qRegisterMetaType<PolkitQt1::Identity*>("PolkitQt1::Identity *");
    setupUi(this);
    errorLabel->hide();
    setModal(true);
    pluginDialog=NULL;

    if(message.isEmpty()){
        syslog(LOG_WARNING,"Could not get action message for action.");
        headerLabel->hide();
    } else {
        syslog(LOG_DEBUG,"Message of action: %s.",message.toStdString().data());
        headerLabel->setText("<h3>"+message+"</h3>");
    }
    // find action description for actionId
    foreach(PolkitQt1::ActionDescription desc,PolkitQt1::Authority::instance()->enumerateActionsSync()){
        if(actionId==desc.actionId()){
            actionDescription=new PolkitQt1::ActionDescription(desc);
            syslog(LOG_DEBUG,"Found action description: %s.",actionDescription->description().toStdString().data());
            break;
        }
    }
    detailsDialog=new PolkitDetailsImpl(details,actionDescription,appname,this);
    horizontalLayoutDetails->addWidget(detailsDialog);
    detailsDialog->hide();
    connect(detailsButton,SIGNAL(pressed()),SLOT(showDetails()));
    connect(detailsButton,SIGNAL(released()),SLOT(resize()));
    userCombobox->hide();
    // If there is more than 1 identity we will show the combobox for user selection
    if(identities.size()>1){
        connect(userCombobox,SIGNAL(currentIndexChanged(int)),SLOT(userComboboxIndexChanged(int)));
        createUserCombobox(identities);
    }
    else{
        userCombobox->addItem("", QVariant(identities[0].toString()));
        userCombobox->setCurrentIndex(0);
    }
    passwordEdit->setFocus();
}

PolkitDialogImpl::~PolkitDialogImpl(){
    syslog(LOG_DEBUG,"Deleting PolkitDialog.");
    // If a helper process is running kill him
    int rc;
    FILE *pidfile=fopen(HELPER_PID,"r");
    if(pidfile){
        char pidstr[100];
        int i=fread(pidstr,1,100,pidfile);
        if(i>0)
            pidstr[i]='\0';
        sscanf(pidstr,"%d",&i);
        if(i!=getpid()){
            syslog(LOG_WARNING,"Killing fingerprint-helper (%d).",i);
            kill(i,SIGTERM);
            waitpid(i,&rc,0);
        }
        fclose(pidfile);
    }
}

// Preselect the current user if he is in admin group
bool PolkitDialogImpl::preselectUser(){
    struct passwd *bPwd=getpwuid(getuid());
    if(!bPwd){
        return false;
    }
    int i=userCombobox->findText(QString(bPwd->pw_name));
    if(i>0){
        syslog(LOG_DEBUG,"User %s selected.",bPwd->pw_name);
        userCombobox->setCurrentIndex(i);
        return true;
    }
    return false;
}

void PolkitDialogImpl::resize(){
    adjustSize();
    passwordEdit->setFocus();
    passwordEdit->grabKeyboard();
}

void PolkitDialogImpl::accept(){
    syslog(LOG_DEBUG,"Accept.");
    // Do nothing, do not close the dialog. This is needed so that the dialog stays
    return;
}

void PolkitDialogImpl::setRequest(const QString &request,bool requiresAdmin){
    syslog(LOG_DEBUG,"Request: %s requires %s admin.",request.toStdString().data(),requiresAdmin?"":"no");
    if(pluginDialog){
        horizontalLayoutFingerprint->removeWidget(pluginDialog);
        delete(pluginDialog);
        pluginDialog=NULL;
        unlink(PLUGIN_FIFO);
        resize();
    }
    usleep(400000);
    // Create a named pipe to receive messages from fingerprintHelper
    mkfifo(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
    chmod(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
    pluginDialog=new PluginDialog(this,false);
    pluginDialog->setFixedSize(341,115);
    pluginDialog->hide();
    horizontalLayoutFingerprint->addWidget(pluginDialog);
    syslog(LOG_DEBUG,"Plugin dialog created (hidden).");

    PolkitQt1::Identity identity=userSelected();
    if(request.startsWith(QLatin1String("password:"),Qt::CaseInsensitive)){
        if(requiresAdmin){
            if(!identity.isValid()){
                passwordLabel->setText("Password for root:");
            }
            else{
                passwordLabel->setText("Password for "+identity.toString().remove("unix-user:"));
            }
        }
        else{
            passwordLabel->setText("Password:");
        }
    }
    else{
        passwordLabel->setText(request);
    }
    passwordEdit->setFocus();
}

void PolkitDialogImpl::createUserCombobox(const PolkitQt1::Identity::List &identities){
    if(identities.count()&&(userCombobox->count()-1)!=identities.count()){
        userCombobox->clear();
        // Adds a Dummy user
        userCombobox->addItem("Select User", qVariantFromValue<QString> (QString()));
        qobject_cast<QStandardItemModel *>(userCombobox->model())->item(userCombobox->count()-1)->setEnabled(false);

        // For each user
        foreach(PolkitQt1::Identity identity,identities) {
            QString user(identity.toString().remove("unix-user:"));
            syslog(LOG_DEBUG,"Add user: %s.",user.toStdString().data());
            userCombobox->addItem(user,qVariantFromValue<QString> (identity.toString()));
        }

        // Show the widget and set focus
        userCombobox->show();
        userCombobox->setFocus();
        passwordEdit->setEnabled(false);
        passwordLabel->setEnabled(false);
        okButton->setEnabled(false);
    }
}

PolkitQt1::Identity PolkitDialogImpl::userSelected(){
    if (userCombobox->currentIndex()==-1)
        return PolkitQt1::Identity();

    QString id=userCombobox->itemData(userCombobox->currentIndex()).toString();
    if (id.isEmpty())
        return PolkitQt1::Identity();
    return PolkitQt1::Identity::fromString(id);
}

void PolkitDialogImpl::userComboboxIndexChanged(int /*index*/){
    PolkitQt1::Identity identity=userSelected();
    if(pluginDialog){
        horizontalLayoutFingerprint->removeWidget(pluginDialog);
        delete(pluginDialog);
        pluginDialog=NULL;
        unlink(PLUGIN_FIFO);
        resize();
    }
    // itemData is Null when "Select user" is selected
    if(!identity.isValid()){
        passwordEdit->setEnabled(false);
        passwordLabel->setEnabled(false);
        okButton->setEnabled(false);
    }
    else{
        passwordEdit->setEnabled(true);
        passwordLabel->setEnabled(true);
        okButton->setEnabled(true);
        // We need this to restart the auth with the new user
        emit adminUserSelected(identity);
        passwordEdit->setFocus();
    }
}

QString PolkitDialogImpl::password() const{
    return passwordEdit->text();
}

void PolkitDialogImpl::authenticationFailure(){
    errorLabel->setText("Authentication failure, please try again.");
    errorLabel->show();
    passwordEdit->clear();
    passwordEdit->setFocus();
}

void PolkitDialogImpl::setOptions(){
    contentLabel->setText(
    "An application is attempting to perform an action that requires privileges. \
    Authentication is required to perform this action.");
    SET_TEXT_COLOR;
}

void PolkitDialogImpl::showDetails(){
    if(detailsDialog->isHidden()){
        detailsButton->setText("&Details <<");
        detailsDialog->show();
    }
    else{
        detailsDialog->hide();
        detailsButton->setText("&Details >>");
    }
}

//------------------------------------------------------------------------------
PolkitDetailsImpl::PolkitDetailsImpl(const PolkitQt1::Details &details,
                         PolkitQt1::ActionDescription *actionDescription,
                         const QString &appname,
                         QWidget *parent) : QWidget(parent){
    setupUi(this);

    if(!appname.isEmpty()){
        appTextLabel->setText(appname);
    }
    else{
        appLabel->hide();
        appTextLabel->hide();
    }
    foreach(const QString &key,details.keys()){
        int row=gridLayout->rowCount()+1;
        QLabel *keyLabel=new QLabel(this);
        keyLabel->setText(key+"is the name of a detail about the current action provided by polkit.");
        gridLayout->addWidget(keyLabel,row,0);
        QLabel *valueLabel=new QLabel(this);
        valueLabel->setText(details.lookup(key));
        gridLayout->addWidget(valueLabel,row,1);
    }
    if(actionDescription){
        if(!actionDescription->description().isEmpty()){
            actionTextLabel->setText(actionDescription->description());
        }
        else{
            actionLabel->hide();
            actionTextLabel->hide();
        }

        QString vendor=actionDescription->vendorName();
        QString vendorUrl = "<a href=\""+actionDescription->vendorUrl()+"\">"+vendor+"</a>";
        if(!vendor.isEmpty()){
            vendorUrlLabel->setToolTip("Click to open "+actionDescription->vendorUrl());
            vendorUrlLabel->setText(vendorUrl);
        } 
        else{
            if(!actionDescription->vendorUrl().isEmpty()){
                vendorUrlLabel->setToolTip("Click to open "+actionDescription->vendorUrl());
                vendorUrlLabel->setText(vendorUrl);
            }
            else{
                vendorLabel->hide();
                vendorUrlLabel->hide();
            }
        }
    }
}
