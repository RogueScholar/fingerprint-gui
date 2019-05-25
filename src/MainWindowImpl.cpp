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

//#include <qt4/QtCore/qlocale.h>
#include <qlocale.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include "ui_FingerprintGUI.h"
#include "../include/DeviceHandler.h"
#include "../include/MainWindowImpl.h"
#include "../include/ExistDialogImpl.h"
#include "../include/SavedDialogImpl.h"
#include "../include/Fingercodes.h"
#include "../include/PamTester.h"
#include "../include/AboutImpl.h"
#include "../include/UserSettings.h"
#include "../include/GlobalsImg.h"

FINGERS
        
MainWindowImpl::MainWindowImpl(QWidget * parent, Qt::WFlags f)
    : QMainWindow(parent, f){
    setupUi(this);

    string title=string("Fingerprint GUI ");
    title.append(VERSION);
    setWindowTitle(QApplication::translate("MainWindow",title.data(), 0, QApplication::UnicodeUTF8));
    deviceHandler=new DeviceHandler(DISPLAY_VENDOR_NAME);
    connect(deviceHandler, SIGNAL(deviceAdded(string)), this, SLOT(newDevice(string)));
    connect(rescanButton, SIGNAL(clicked()),deviceHandler, SLOT(rescan()));
    connect(deviceHandler, SIGNAL(rescanFinished()), this, SLOT(showAttachedUSBDevices()));
    connect(lsButton,SIGNAL(clicked()),this,SLOT(lsChanged()));
    connect(lrButton,SIGNAL(clicked()),this,SLOT(lrChanged()));
    connect(lmButton,SIGNAL(clicked()),this,SLOT(lmChanged()));
    connect(lpButton,SIGNAL(clicked()),this,SLOT(lpChanged()));
    connect(ltButton,SIGNAL(clicked()),this,SLOT(ltChanged()));
    connect(rsButton,SIGNAL(clicked()),this,SLOT(rsChanged()));
    connect(rrButton,SIGNAL(clicked()),this,SLOT(rrChanged()));
    connect(rmButton,SIGNAL(clicked()),this,SLOT(rmChanged()));
    connect(rpButton,SIGNAL(clicked()),this,SLOT(rpChanged()));
    connect(rtButton,SIGNAL(clicked()),this,SLOT(rtChanged()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(nextTab()));
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged()));
    connect(deviceCombo,SIGNAL(currentIndexChanged(int)),deviceHandler,SLOT(setCurrentDevice(int)));
    connect(action_Exit,SIGNAL(triggered()),this,SLOT(closeApp()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(closeApp()));
    connect(exportButton,SIGNAL(clicked()),this,SLOT(saveToFile()));
    connect(vendornameButton,SIGNAL(clicked()),this,SLOT(displayModeVendor()));
    connect(drivernameButton,SIGNAL(clicked()),this,SLOT(displayModeDriver()));
    connect(testButton,SIGNAL(clicked()),this,SLOT(testPam()));
    connect(pathButton,SIGNAL(clicked()),this,SLOT(setPwdPath1()));
    connect(pathEdit,SIGNAL(editingFinished()),this,SLOT(setPwdPath2()));
    connect(pathEdit,SIGNAL(editingFinished()),this,SLOT(enableSaveButton()));
    connect(passwdLine1,SIGNAL(textChanged(const QString&)),this,SLOT(enableSaveButton()));
    connect(passwdLine2,SIGNAL(textChanged(const QString&)),this,SLOT(enableSaveButton()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(savePasswd()));
    connect(action_About,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    connect(action_Help,SIGNAL(triggered(bool)),this,SLOT(showHelp()));
    connect(action_Homepage,SIGNAL(triggered(bool)),this,SLOT(showHomepage()));
    connect(action_Forum_Online,SIGNAL(triggered(bool)),this,SLOT(showForum()));

    currentTab=0;
    tabWidget->setCurrentIndex(currentTab);
    movie = new QMovie(QString::fromUtf8(":/new/prefix1/res/Animation.gif"));
    movie->start();    
    movie->setPaused(true);    
    animationLabel->setMovie(movie);
    textLabels[0]=fpStatusLabel1;
    textLabels[1]=fpStatusLabel2;
    textLabels[2]=fpStatusLabel3;
    textLabels[3]=fpStatusLabel4;
    textLabels[4]=fpStatusLabel5;
    iconLabels[0]=fpResultLabel1;
    iconLabels[1]=fpResultLabel2;
    iconLabels[2]=fpResultLabel3;
    iconLabels[3]=fpResultLabel4;
    iconLabels[4]=fpResultLabel5;
    currentFinger=6;
    currentFingerprint=NULL;
    resultLabel->clear();
    fpPixMap=QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png"));
    fpPix = QPixmap();
}

// slots -----------------------------------------------------------------------
void MainWindowImpl::showAbout(){
    AboutImpl *aDialog=new AboutImpl(this);
    aDialog->show();
}

void MainWindowImpl::showHelp(){
    QLocale locale;
    QString lang=locale.name().left(2);
    QString docfile;
    docfile=QString(DOCDIR)+QString(HELP_BASE)+lang+QString(HELP_EXT);
    QFile doc(docfile);
    if(!doc.exists()){
        docfile=QString(DOCDIR)+QString(HELP_BASE)+QString("en")+QString(HELP_EXT);
    }
    QUrl url("file://"+docfile);
    QDesktopServices srv;
    srv.openUrl(url);
}

void MainWindowImpl::showHomepage(){
    QDesktopServices srv;
    srv.openUrl(QUrl(HOMEPAGE));
}

void MainWindowImpl::showForum(){
    QDesktopServices srv;
    srv.openUrl(QUrl(FORUM_ONLINE));
}

bool MainWindowImpl::getUuid(QString dir){
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    QFile mtab("/etc/mtab");
    if(!mtab.open(QIODevice::ReadOnly)){
        syslog(LOG_ERR,"Could not open \"/etc/mtab\".");
        return false;
    }
//    while(!mtab.atEnd()){
    QTextStream mt(&mtab);
    while(true){
        QString line=mt.readLine();
	if(line.isNull())break;
	if(line.isEmpty())continue;
//syslog(LOG_DEBUG,"LINE %s.",line.toStdString().data());
        QString mountPoint=line.section(' ',1,1);
//syslog(LOG_DEBUG,"DIR: %s, MP: %s.",dir.toStdString().data(),mountPoint.toStdString().data());
        if(mountPoint!="/"&&dir.startsWith(mountPoint)){
            QString dev=line.section(' ',0,0);
//syslog(LOG_DEBUG,"DIR: %s, DEV: %s.",dir.toStdString().data(),dev.toStdString().data());
            QDirIterator uuidIt("/dev/disk/by-uuid/",QDirIterator::NoIteratorFlags);
            while(uuidIt.hasNext()) {
                uuidIt.next();
                QFileInfo info=uuidIt.fileInfo();
                if(info.isSymLink()){
                    if(info.symLinkTarget()==dev){
//syslog(LOG_DEBUG,"UUID: %s, DEV: %s.",info.fileName().toStdString().data(),dev.toStdString().data());
                        passwdUUID=info.fileName();
                        while(!dev.isEmpty()&&dev.right(1).at(0).isDigit())dev.chop(1);//remove digits from device /dev/sdb123 becomes /dev/sdb
//syslog(LOG_DEBUG,"UUID: %s, DEV: %s.",info.fileName().toStdString().data(),dev.toStdString().data());
                        QFile d("/sys/class/block/"+dev.section('/',-1)+"/removable");
//syslog(LOG_DEBUG,"UUID: %s, D: %s.",info.fileName().toStdString().data(),d.fileName().toStdString().data());
                        if(d.exists()&&d.open(QIODevice::ReadOnly)){
                            QString s=d.readAll();
//syslog(LOG_DEBUG,"UUID: %s, S: %s.",info.fileName().toStdString().data(),s.toStdString().data());
                            if(s.at(0)=='1'){
				mtab.close();
                                return true;
			    }
                        }
                        const char* msg="The selected device is not removable!";
                        syslog(LOG_ERR,"%s",msg);
                        msgBox.setText(msg);
                        msgBox.exec();
                        passwdUUID.clear();
			mtab.close();
                        return false;
                    }
                }
            }
        }
    }
    mtab.close();
    const char* msg="Could not get UUID!";
    syslog(LOG_ERR,"%s",msg);
    msgBox.setText(msg);
    msgBox.exec();
    passwdUUID.clear();
    return false;
}

void MainWindowImpl::savePasswd(){
    bool error=false;
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    struct passwd *pws=getpwuid(geteuid());
    QString username(pws->pw_name);
    char host[1000];

    if(gethostname(host,1000)){
        error=true;
    }
    QString hostname(host);
    if(!error&&hostname.isEmpty()){
        error=true;
    }
    if(error){
        const char* msg="Could not get hostname!";
        syslog(LOG_ERR,"%s",msg);
        msgBox.setText(msg);
    }
    if(!error&&username.isEmpty()){
        const char* msg="Could not get username!";
        syslog(LOG_ERR,"%s",msg);
        msgBox.setText(msg);
        error=true;
    }
    if(!error&&passwdLine1->text()!=passwdLine2->text()){
        const char* msg="Passwords don't match!";
        syslog(LOG_ERR,"%s",msg);
        msgBox.setText(msg);
        error=true;
    }
    if(error){
        msgBox.exec();
        return;
    }
    passwdPasswd=passwdLine1->text();
    UserSettings userSettings(
        (char*)passwdPath.toStdString().data(),
        (char*)passwdUUID.toStdString().data(),
        (char*)username.toStdString().data(),
        (char*)hostname.toStdString().data());
    if(!userSettings.writeConfig((char*)passwdPasswd.toStdString().data(),debugTest)){
        const char* msg="Could not save password!";
        syslog(LOG_ERR,"%s",msg);
        msgBox.setText(msg);
        msgBox.exec();
        return;
    }
    const char* msg="Encrypted password saved";
    syslog(LOG_DEBUG,"%s for %s to: %s",msg,username.toStdString().data(),userSettings.pathToPassword.toStdString().data());
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(msg);
    msgBox.exec();
    cancelButton->setEnabled(false);
    okButton->setEnabled(true);
    okButton->setAutoDefault(true);
}

void MainWindowImpl::enableSaveButton(){
    passwdReady=true;
    if(passwdUUID.isEmpty()|passwdPath.isEmpty()|passwdLine1->text().isEmpty()|passwdLine2->text().isEmpty()
            |(passwdLine1->text().length()!=passwdLine2->text().length())){
        passwdReady=false;
    }
    saveButton->setEnabled(passwdReady);
    saveButton->setAutoDefault(passwdReady);
}


void MainWindowImpl::setPwdPath(QString selectedPath){
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    QDir pwdDir(selectedPath);
    if(!pwdDir.exists()){
        const char* msg="Directory doesn't exist!";
        syslog(LOG_ERR,"%s (%s)",msg,pwdDir.absolutePath().toStdString().data());
        msgBox.setText(msg);
        msgBox.exec();
        return;
    }

    passwdPath=pwdDir.absolutePath();
    pathEdit->setText(passwdPath);
    // find the UUID
    if(getUuid(passwdPath)){
        syslog(LOG_DEBUG,"Selected Dir for Password Store: %s (UUID: %s)",
                pwdDir.absolutePath().toStdString().data(),passwdUUID.toStdString().data());
    }
    enableSaveButton();
}

void MainWindowImpl::setPwdPath1(){
    QString dir=QFileDialog::getExistingDirectory(
            this,
            tr("Open Directory on removable Media"),
            "/media",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    setPwdPath(dir);
}

void MainWindowImpl::setPwdPath2(){
    setPwdPath(pathEdit->text());
}

void MainWindowImpl::closeApp(){
    if(currentFingerprint!=NULL){
        syslog(LOG_INFO,"Stopping device...");
        currentFingerprint->getDevice()->stop();
        currentFingerprint->getDevice()->wait(1000);
        syslog(LOG_INFO,"Stopped.");
        delete(currentFingerprint);
    }
    stopTester=true;
    syslog(LOG_DEBUG,"qApp exit.");
    qApp->exit(EXIT_SUCCESS);
}

void MainWindowImpl::testPam(){
    string service=string("");
    bool identify=false;
    for(int i=0;services[i].button!=NULL;i++){
        if(services[i].button->isChecked()){
            service=string(services[i].name);
            identify=services[i].identify;
            break;
        }
    }
    if(service.empty())return;//uups
    tabWidget->setTabEnabled(DEVICE_TAB,false);
    tabWidget->setTabEnabled(FINGER_TAB,false);
    tabWidget->setTabEnabled(SCAN_TAB,false);
    tabWidget->setTabEnabled(PASSWORD_TAB,false);
    okButton->setEnabled(false);
    cancelButton->setEnabled(false);
    exportButton->setEnabled(false);
    testButton->setEnabled(false);
    PamTester tester(testLabel1,testLabel2,service.data(),identify);
    resultLabel->grabKeyboard();
    tester.testPam(deviceHandler,resultLabel);
    testButton->setEnabled(true);
    testLabel1->setText("");
    testLabel2->setText("");
    okButton->setEnabled(true);
    cancelButton->setEnabled(true);
    exportButton->setEnabled(true);
    tabWidget->setTabEnabled(DEVICE_TAB,true);
    tabWidget->setTabEnabled(FINGER_TAB,true);
    tabWidget->setTabEnabled(SCAN_TAB,true);
    tabWidget->setTabEnabled(PASSWORD_TAB,true);
    resultLabel->releaseKeyboard();
}

static bool message=false;
void MainWindowImpl::noDeviceOpen(){
    //don't know why this is called more than once with further tries
    if(message)return;else message=true;
    tabWidget->setCurrentIndex(DEVICE_TAB);
    MessageDialogImpl md(this);
    md.exec();
    message=false;
}

void MainWindowImpl::acquireFinished(int result,struct fp_pic_data *pic){
    movie->setPaused(true);
    if ( !fpPix.isNull() ) {
        freeQPixmapFromFpImg ( &fpPix );
    }
    createQPixmapFromFpImg ( &fpPix, pic, animationLabel->width(), animationLabel->height() );
    if ( !fpPix.isNull() ) {
        animationLabel->setPixmap ( fpPix );
    }
    if(result==RESULT_ENROLL_COMPLETE)
        sDialog=new SavedDialogImpl(MODE_SAVED,this,pic);
    else
        sDialog=new SavedDialogImpl(MODE_NOT_SAVED,this,pic);
    sDialog->show();
    connect(sDialog,SIGNAL(choice(savedDialogChoice)),this,SLOT(savedDialogChosen(savedDialogChoice)));
}

void MainWindowImpl::verifyFinished(int result,struct fp_pic_data * pic){
    movie->setPaused(true);
    if ( !fpPix.isNull() ) {
        freeQPixmapFromFpImg ( &fpPix );
    }
    createQPixmapFromFpImg ( &fpPix, pic, animationLabel->width(), animationLabel->height() );
    if ( !fpPix.isNull() ) {
        animationLabel->setPixmap ( fpPix );
    }
    if(result==RESULT_VERIFY_MATCH)
        sDialog=new SavedDialogImpl(MODE_VERIFIED,this,pic);
    else
        sDialog=new SavedDialogImpl(MODE_NOT_VERIFIED,this,pic);
    sDialog->show();
    connect(sDialog,SIGNAL(choice(savedDialogChoice)),this,SLOT(savedDialogChosen(savedDialogChoice)));
}

void MainWindowImpl::savedDialogChosen(savedDialogChoice choice){
    switch(choice){
        case SAVED_YES:
            tabWidget->setCurrentIndex(FINGER_TAB);
            break;
        case SAVED_NO:
            bool v=currentFingerprint->isValid();
            scanTabToBack();
            if(!v) 
                scanTabToFront();
            break;
    }
    disconnect(this,SLOT(savedDialogChosen(savedDialogChoice)));
}

void MainWindowImpl::existDialogChosen(existDialogChoice choice){
    switch(choice){
        case EXIST_VERIFY:
            currentFingerprint->modeVerify();
        case EXIST_ACQUIRE:
            movie->setPaused(false);
            swipeFinger();
            break;
        case EXIST_CANCEL:
            tabWidget->setCurrentIndex(FINGER_TAB);
    }
    disconnect(this,SLOT(existDialogChosen(existDialogChoice)));
}

int MainWindowImpl::saveToFile(){  //save fingerprints to tar-file (needs tar and zip in path)
    struct passwd *pws=getpwuid(geteuid());

    QString home=QDir::homePath();
    home.append(BACKUP_FILENAME);
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save Fingerprints"),home,tr("Tar Archives (*.tar.gz)"));
    string command="cd ~ ;";
    command.append("pkexec tar -czf \"");
    command.append(fileName.toStdString());
    command.append("\" ");
    command.append(DATA_DIR);
    command.append(pws->pw_name);
    syslog(LOG_DEBUG,"Execute command: %s.",command.data());
    return system(command.data());
}
        
void MainWindowImpl::nextTab(){
    if(currentTab==PASSWORD_TAB){
        if(haveFingerprints()){
            closeApp();                                 //Finish button
        }
        else{
            tabWidget->setCurrentIndex(currentTab-1);   //Back button
            return;
        }
    }
    tabWidget->setCurrentIndex(currentTab+1);
}

void MainWindowImpl::tabChanged(){
    tabChanged(tabWidget->currentIndex());
}

void MainWindowImpl::newDevice(string name){
    deviceCombo->addItem(QString::fromStdString(name),(int) NULL);
}

void MainWindowImpl::showAttachedUSBDevices(){
    usbDeviceListWidget->show();
    usbDeviceListWidget->clear();
    if(deviceHandler->getAttachedUsbDevices()!=NULL){
        for(USBDevice *attachedUSB=deviceHandler->getAttachedUsbDevices();attachedUSB!=NULL;attachedUSB=attachedUSB->next)
            usbDeviceListWidget->addItem(attachedUSB->getDeviceDescriptor());
    }
    //are devices available??
    if(deviceHandler->getFingerprintDevices()==NULL){ //NO
        const char* msg="No Devices Found!";
        syslog(LOG_ERR,"%s",msg);
        deviceCombo->addItem(QString::fromStdString(msg));
        okButton->setEnabled(false);
        tabWidget->setTabEnabled(FINGER_TAB,false);
        tabWidget->setTabEnabled(SCAN_TAB,false);
        tabWidget->setTabEnabled(SETTINGS_TAB,false);
    }
    else{
        okButton->setEnabled(true);
        tabWidget->setTabEnabled(FINGER_TAB,true);
        tabWidget->setTabEnabled(SCAN_TAB,true);
        tabWidget->setTabEnabled(SETTINGS_TAB,true);
    }
}

void MainWindowImpl::setScanTabNeededStages(int stages){
    switch(stages){
        case 1:
            fingerprintLabel2->setPixmap(NULL);
            fingerprintLabel3->setPixmap(NULL);
            fingerprintLabel4->setPixmap(NULL);
            fingerprintLabel5->setPixmap(NULL);
            break;
        case 2:
            fingerprintLabel3->setPixmap(NULL);
            fingerprintLabel4->setPixmap(NULL);
            fingerprintLabel5->setPixmap(NULL);
            fingerprintLabel2->setPixmap(fpPixMap);
            break;
        case 3:
            fingerprintLabel4->setPixmap(NULL);
            fingerprintLabel5->setPixmap(NULL);
            fingerprintLabel2->setPixmap(fpPixMap);
            fingerprintLabel3->setPixmap(fpPixMap);
            break;
        case 4:
            fingerprintLabel5->setPixmap(NULL);
            fingerprintLabel2->setPixmap(fpPixMap);
            fingerprintLabel3->setPixmap(fpPixMap);
            fingerprintLabel4->setPixmap(fpPixMap);
            break;
        case 5:
            fingerprintLabel2->setPixmap(fpPixMap);
            fingerprintLabel3->setPixmap(fpPixMap);
            fingerprintLabel4->setPixmap(fpPixMap);
            fingerprintLabel5->setPixmap(fpPixMap);
    }
    syslog(LOG_DEBUG,"Need %d stages.",stages);
}

// set the current finger
void MainWindowImpl::lsChanged(){setLabel(0);}
void MainWindowImpl::lrChanged(){setLabel(1);}
void MainWindowImpl::lmChanged(){setLabel(2);}
void MainWindowImpl::lpChanged(){setLabel(3);}
void MainWindowImpl::ltChanged(){setLabel(4);}
void MainWindowImpl::rsChanged(){setLabel(9);}
void MainWindowImpl::rrChanged(){setLabel(8);}
void MainWindowImpl::rmChanged(){setLabel(7);}
void MainWindowImpl::rpChanged(){setLabel(6);}
void MainWindowImpl::rtChanged(){setLabel(5);}

//show vendor/device info in combobox
void MainWindowImpl::displayModeVendor(){
    int i;
    disconnect(deviceCombo,SIGNAL(currentIndexChanged(int)),deviceHandler,SLOT(setCurrentDevice(int)));
    deviceHandler->setDisplayNameMode(DISPLAY_VENDOR_NAME);
    deviceCombo->clear();
    deviceHandler->rescan();
    deviceHandler->getCurrentDevice(&i);
    deviceCombo->setCurrentIndex(i);
    connect(deviceCombo,SIGNAL(currentIndexChanged(int)),deviceHandler,SLOT(setCurrentDevice(int)));
}

//show driver info in combobox
void MainWindowImpl::displayModeDriver(){
    int i;
    disconnect(deviceCombo,SIGNAL(currentIndexChanged(int)),deviceHandler,SLOT(setCurrentDevice(int)));
    deviceHandler->setDisplayNameMode(DISPLAY_VENDOR_NAME);
    deviceHandler->setDisplayNameMode(DISPLAY_DRIVER_NAME);
    deviceCombo->clear();
    deviceHandler->rescan();
    deviceHandler->getCurrentDevice(&i);
    deviceCombo->setCurrentIndex(i);
    connect(deviceCombo,SIGNAL(currentIndexChanged(int)),deviceHandler,SLOT(setCurrentDevice(int)));
}

// private helpers -------------------------------------------------------------
void MainWindowImpl::tabChanged(int newTab){
   
    if(newTab==currentTab)
        return;
    switch (currentTab){
        case DEVICE_TAB:
            deviceTabToBack();
            break;
        case FINGER_TAB:
            fingerTabToBack();
            break;
        case SCAN_TAB:
            scanTabToBack();
            break;
        case SETTINGS_TAB:
            settingsTabToBack();
            break;
        case PASSWORD_TAB:
            passwordTabToBack();
            break;
    }
    switch (newTab){
        case DEVICE_TAB:
            deviceTabToFront();
            break;
        case FINGER_TAB:
            fingerTabToFront();
            break;
        case SCAN_TAB:
            scanTabToFront();
            break;
        case SETTINGS_TAB:
            settingsTabToFront();
            break;
        case PASSWORD_TAB:
            passwordTabToFront();
            break;
    }
    currentTab=newTab;
}

void MainWindowImpl::swipeFinger(){
    if(!currentFingerprint->swipe()){
        closeApp(); //something went wrong
    }
}

bool MainWindowImpl::haveFingerprints(){
    struct passwd *pws=getpwuid(geteuid());

    QString userdir(DATA_DIR);
    userdir.append(pws->pw_name);
    QDir *fpDir=new QDir(userdir);
    return(fpDir->exists());
}

void MainWindowImpl::deviceTabToBack(){
}

void MainWindowImpl::fingerTabToBack(){
}

void MainWindowImpl::scanTabToBack(){
    movie->setPaused(true);
    if(currentFingerprint!=NULL){
        disconnect(currentFingerprint->getDevice(),SIGNAL(noDeviceOpen()),this,SLOT(noDeviceOpen()));
        disconnect(currentFingerprint->getDevice(),SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
        disconnect(currentFingerprint,SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
        disconnect(currentFingerprint->getDevice(),SIGNAL(acquireResult(int)),currentFingerprint,SLOT(newAcquireResult(int)));
        disconnect(currentFingerprint->getDevice(),SIGNAL(verifyResult(int,struct fp_pic_data*)),currentFingerprint,SLOT(newVerifyResult(int,struct fp_pic_data*)));
        disconnect(currentFingerprint,SIGNAL(acquireFinished(int,struct fp_pic_data*)),this,SLOT(acquireFinished(int,struct fp_pic_data*)));
        disconnect(currentFingerprint,SIGNAL(verifyFinished(int,struct fp_pic_data*)),this,SLOT(verifyFinished(int,struct fp_pic_data*)));
        delete(currentFingerprint);
        currentFingerprint=NULL;
    }
    //enable other widgets
    tabWidget->setTabEnabled(DEVICE_TAB,true);
    tabWidget->setTabEnabled(FINGER_TAB,true);
    tabWidget->setTabEnabled(SETTINGS_TAB,true);
    okButton->setEnabled(true);
    rescanButton->setEnabled(true);
    vendornameButton->setEnabled(true);
    drivernameButton->setEnabled(true);
    deviceCombo->setEnabled(true);
}

void MainWindowImpl::settingsTabToBack(){
    stopTester=true;
}

void MainWindowImpl::passwordTabToBack(){
    okButton->setText("&Next");
    cancelButton->setEnabled(true);
}

void MainWindowImpl::deviceTabToFront(){
}

void MainWindowImpl::markFinger(int finger){
    QRadioButton *f=NULL;

    switch (finger){
        case 0:
            f=lsButton;
            break;
        case 1:
            f=lrButton;
            break;
        case 2:
            f=lmButton;
            break;
        case 3:
            f=lpButton;
            break;
        case 4:
            f=ltButton;
            break;
        case 5:
            f=rtButton;
            break;
        case 6:
            f=rpButton;
            break;
        case 7:
            f=rmButton;
            break;
        case 8:
            f=rrButton;
            break;
        case 9:
            f=rsButton;
            break;
    }
    if(f==NULL)
        return;
    f->setStyleSheet(QString::fromUtf8(
    "QRadioButton::indicator::unchecked \n"
    "{image: url(:/new/prefix1/res/radiobutton_unchecked_gn.png);}\n"
    "QRadioButton::indicator::checked \n"
    "{image: url(:/new/prefix1/res/radiobutton_checked_gn.png);}\n"
    "QRadioButton::indicator:unchecked:hover\n"
    "{image: url(:/new/prefix1/res/radiobutton_unchecked_hover_gn.png);}\n"
    "QRadioButton::indicator:checked:hover\n"
    "{image: url(:/new/prefix1/res/radiobutton_checked_hover_gn.png);}\n"
    "QRadioButton::indicator:unchecked:pressed\n"
    "{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed_gn.png);}\n"
    "QRadioButton::indicator:checked:pressed\n"
    "{image: url(:/new/prefix1/res/radiobutton_checked_pressed_gn.png);}"));
}

void MainWindowImpl::fingerTabToFront(){
    stopTester=true;
    setLabel(currentFinger);
    for(int i=0;i<10;i++){  // mark fingers with existing bir data
        Fingerprint *f=new Fingerprint(i,deviceHandler->getCurrentDevice(NULL),textLabels,iconLabels);
        if(f->isValid()){
            markFinger(i);
        }
        f->deleteLater();
    }
}

void MainWindowImpl::scanTabToFront(){
	setScanTabNeededStages(1);
    stopTester=true;
    animationLabel->setMovie(movie);
    QString s("Please Swipe Your ");
    s.append(fingers[currentFinger]);
    syslog(LOG_DEBUG,"%s.",s.toStdString().data());
    acquireLabel->setText(s);
    //disable other widgets
    tabWidget->setTabEnabled(DEVICE_TAB,false);
    tabWidget->setTabEnabled(FINGER_TAB,false);
    tabWidget->setTabEnabled(SETTINGS_TAB,false);
    okButton->setEnabled(false);
    rescanButton->setEnabled(false);
    vendornameButton->setEnabled(false);
    drivernameButton->setEnabled(false);
    deviceCombo->setEnabled(false);
    currentFingerprint=new Fingerprint(currentFinger,deviceHandler->getCurrentDevice(NULL),textLabels,iconLabels);
    disconnect(currentFingerprint->getDevice(),SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
    connect(currentFingerprint->getDevice(),SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
    disconnect(currentFingerprint,SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
    connect(currentFingerprint,SIGNAL(neededStages(int)),this,SLOT(setScanTabNeededStages(int)));
    disconnect(currentFingerprint->getDevice(),SIGNAL(noDeviceOpen()),this,SLOT(noDeviceOpen()));
    connect(currentFingerprint->getDevice(),SIGNAL(noDeviceOpen()),this,SLOT(noDeviceOpen()));
    disconnect(currentFingerprint->getDevice(),SIGNAL(acquireResult(int)),currentFingerprint,SLOT(newAcquireResult(int)));
    connect(currentFingerprint->getDevice(),SIGNAL(acquireResult(int)),currentFingerprint,SLOT(newAcquireResult(int)));
    disconnect(currentFingerprint->getDevice(),SIGNAL(verifyResult(int,struct fp_pic_data*)),currentFingerprint,SLOT(newVerifyResult(int,struct fp_pic_data*)));
    connect(currentFingerprint->getDevice(),SIGNAL(verifyResult(int,struct fp_pic_data*)),currentFingerprint,SLOT(newVerifyResult(int,struct fp_pic_data*)));
    disconnect(currentFingerprint,SIGNAL(acquireFinished(int,struct fp_pic_data*)),this,SLOT(acquireFinished(int,struct fp_pic_data*)));
    connect(currentFingerprint,SIGNAL(acquireFinished(int,struct fp_pic_data*)),this,SLOT(acquireFinished(int,struct fp_pic_data*)));
    disconnect(currentFingerprint,SIGNAL(verifyFinished(int,struct fp_pic_data*)),this,SLOT(verifyFinished(int,struct fp_pic_data*)));
    connect(currentFingerprint,SIGNAL(verifyFinished(int,struct fp_pic_data*)),this,SLOT(verifyFinished(int,struct fp_pic_data*)));
    if(currentFingerprint->isValid()){
        eDialog=new ExistDialogImpl(fingers[currentFinger],this);
        eDialog->show();
        connect(eDialog,SIGNAL(choice(existDialogChoice)),this,SLOT(existDialogChosen(existDialogChoice)));
    }
    else{
        movie->setPaused(false);
        swipeFinger();
    }
}

void MainWindowImpl::settingsTabToFront(){
    struct passwd *pws=getpwuid(geteuid());

    if(haveFingerprints()){
        exportButton->setEnabled(true);
        string label1=string("Your fingerprints are saved to \"");
        label1.append(DATA_DIR);
        label1.append(pws->pw_name);
        label1.append("\".");
        fprintLabel1->setText(label1.data());
        fprintLabel1->show();
        fprintLabel2->show();
        noFingerprintsLabel->hide();
    }
    else{
        exportButton->setEnabled(false);
        cancelButton->setEnabled(true);
        fprintLabel1->hide();
        fprintLabel2->hide();
        noFingerprintsLabel->show();
        okButton->setText("&Back");
    }

    findPamServices();
    if(!deviceHandler->getCurrentDevice(NULL)->canIdentify()){
	syslog(LOG_DEBUG,"The selected device doesn't support \"identification\".");
    }

}

void MainWindowImpl::passwordTabToFront(){
    struct passwd *pws=getpwuid(geteuid());

    stopTester=true;
    if(haveFingerprints()){
        okButton->setText("&Finish");
        okButton->setEnabled(false);
        saveButton->setEnabled(false);
    }
    else{
        okButton->setText("&Back");
    }
    QString username(pws->pw_name);    // preset pathEdit if media is connected
    UserSettings us((char*)username.toStdString().data(),debugTest);
    pathEdit->setText(us.getPathToMedia());
}


void MainWindowImpl::findPamServices(){
    services[0]=(pamService){string("gdm"),false,gdmButton,true};
    services[1]=(pamService){string("kdm"),false,kdmButton,true};
    services[2]=(pamService){string("sudo"),false,sudoButton,true};
    services[3]=(pamService){string("su"),false,suButton,true};
    services[4]=(pamService){string("gnome-screensaver"),false,gnomescreensaverButton,true};
    services[5]=(pamService){string("lightdm"),false,lightdmButton,true};
    services[6]=(pamService){string(""),false,NULL,false};
    bool checked=false;
    bool haveServices=false;

    for(int i=0;services[i].button!=NULL;i++){
        QRadioButton *button=services[i].button;
        if(services[i].implemented){
            string *srvc=&services[i].name;
            QFile file(QString("/etc/pam.d/")+QString(srvc->data()));
            if(file.exists()){
                if(!checked)button->setChecked(true);//set the first available service button to checked
                button->setEnabled(true);
                haveServices=true;
                checked=true;
            }
            else{
                button->setEnabled(false);
            }
        }
        else{
            button->setEnabled(false);
        }
    }
    if(haveServices)testButton->setEnabled(true);
    else testButton->setEnabled(false);
}

void MainWindowImpl::setLabel(int finger){
    currentFinger=finger;
    QString f(fingers[currentFinger]);
    currentFingerLabel->setText(f);
}
