/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
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

#include "UserSettings.h"
#include "Globals.h"
#include "xmlwriter.h"

#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <errno.h>

#include <QFile>
#include <QDir>
#include <QtCrypto/QtCrypto>
#include <QtXml>

using namespace std;

class SettingsParser:public QXmlDefaultHandler{
    private:
        UserSettings *obj;
        bool inSettings;

    public:
    SettingsParser(UserSettings *obj){
        this->obj=obj;
    }

    bool startDocument(){
        inSettings=false;
        return true;
    }

    bool endElement(const QString&,const QString&,const QString &name){
        if(name=="object"){
            inSettings=false;
        }
        return true;
    }

    bool startElement(const QString&,const QString&,const QString &name,const QXmlAttributes &attrs){
        if(inSettings&&attrs.count()>0){
            if(name=="providePassword"){
                if(attrs.localName(0)=="value"){
                    if(attrs.value(0)=="true"){
                        obj->providePassword=true;
//                        syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),"true");
            }}}
            if(name=="uuid"){
                if(attrs.localName(0)=="value"){
                    obj->uuid=QString(attrs.value(0));
//                    syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),attrs.value(0).toStdString().data());
            }}
            if(name=="pathToPassword"){
                if(attrs.localName(0)=="value"){
                    obj->pathToPassword=QString(attrs.value(0));
//                    syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),attrs.value(0).toStdString().data());
            }}
            if(name=="iv"){
                if(attrs.localName(0)=="value"){
                    obj->xIv=QString(attrs.value(0));
//                    syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),attrs.value(0).toStdString().data());
            }}
            if(name=="key"){
                if(attrs.localName(0)=="value"){
                    obj->xKey=QString(attrs.value(0));
//                    syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),attrs.value(0).toStdString().data());
            }}
            if(name=="pass"){
                if(attrs.localName(0)=="value"){
                    obj->xPass=QString(attrs.value(0));
//                    syslog(LOG_DEBUG,"Setting %s to %s.",name.toStdString().data(),attrs.value(0).toStdString().data());
            }}
        }
        if(name=="object"&&attrs.count()>0){
            if(attrs.localName(0)=="class"&&attrs.value(0)=="UserSettings"){
            inSettings=true;
        }}
        return true;
    }
};

// Constructor used for getting password
UserSettings::UserSettings(char *userName,bool debug){
    pid_t child;
    int rc;
    struct stat bStat;
    providePassword=false;
    umountRequired=false;
    string configFilename;
    
    if(!userName)return;
    if(strlen(userName)<1)return;

    // do we have a config.xml for this user?
    string configPath=string(DATA_DIR);
    configPath.append(userName);
    configPath.append("/config.xml");
    if(stat(configPath.data(),&bStat)!=0){	// could not be stated
        syslog(LOG_DEBUG,"%s doesn't exist.",configPath.data());
	return;
    }
    syslog(LOG_DEBUG,"User has %s file.",configPath.data());

    if(geteuid()!=0){	// not running as root (need pkexec)
    // get configfile from /var/lib/<username>/
	child=fork();           // here we start a child process that copies configfile to /tmp
    	switch(child){
            case 0:             // This is the child
            	rc=execl("/usr/bin/pkexec","pkexec",READ_COMMAND,
                    ARG_USER,userName,
		    ARG_FILE,"config.xml",
                    debug?ARG_DEBUG1:NULL,
                    NULL);
           	syslog(LOG_ERR,"ERROR: Could not execute %s %d (%s).",READ_COMMAND,rc,strerror(errno));
            	_exit(EXIT_FAILURE);
            case -1:            // Fork error
            	syslog(LOG_ERR,"ERROR FORKING CHILD PROCESS.");
            	return;
            default:            // This is the parent
            	syslog(LOG_DEBUG,"Child PID: %d.",child);
            	waitpid(child,&rc,0);
            	if(rc!=EXIT_SUCCESS){
                    syslog(LOG_ERR,"ERROR: %s returned %d.",READ_COMMAND_NAME,rc);
                    return;
            	}
    	}
    	configFilename=string("/tmp/read-config.xml");
    }
    else{
    	configFilename=string(configPath.data());
    }
    QFile configFile(configFilename.data());

    if(!configFile.open(QIODevice::ReadOnly)){
        syslog(LOG_ERR,"Could not open config file %s.",configFile.fileName().toStdString().data());
        return;
    }
    syslog(LOG_DEBUG,"Open file %s for reading.",configFile.fileName().toStdString().data());
    // restore settigs from config.xml
    SettingsParser handler(this);
    QXmlInputSource configSource(&configFile);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(configSource);
    configFile.close();
    if(geteuid()!=0){	// not running as root (tmpfile must be deleted)
    	if(unlink("/tmp/read-config.xml")){
	    syslog(LOG_ERR,"Could not delete file \"/tmp/read-config.xml\"!");
    	}
    }
    
    // check for password
    if(providePassword){
        // Check media by UUID and mount it if available
        QString mountPoint=mountUuid(uuid);
        if(mountPoint.isEmpty()){
            syslog(LOG_DEBUG,"Could not mount device %s.",uuid.toStdString().data());
            return;
        }
//syslog(LOG_DEBUG,"Mount point is %s.",mountPoint.toStdString().data());

        // Find password file on media
        QFile passwordFile(mountPoint+"/"+pathToPassword);
        for(int i=0;!passwordFile.exists();i++){
            if(pathToPassword.section("/",i-1).isEmpty()){
                syslog(LOG_ERR,"Could not find password file.");
                return;
            }
            passwordFile.setFileName(mountPoint+"/"+pathToPassword.section("/",i));
//syslog(LOG_DEBUG,"Try %s.",passwordFile.fileName().toStdString().data());
        }
        if(!passwordFile.open(QIODevice::ReadOnly)){
            syslog(LOG_ERR,"Could not open password file %s.",passwordFile.fileName().toStdString().data());
            return;
        }
        syslog(LOG_DEBUG,"Open file %s for reading.",passwordFile.fileName().toStdString().data());
        // restore encrypted password from user@machine.xml
        QXmlInputSource passwdSource(&passwordFile);
        reader.parse(passwdSource);
        passwordFile.close();
        // Force unmounting media for security reason if it wasn't mounted before
        if(umountRequired){ // Media was not mounted before
//syslog(LOG_DEBUG,"Unmount %s.",mountPoint.toStdString().data());
            int i=50;
            // Seems we need to wait some time for media being idle
            while(i>0&&umount2(mountPoint.toStdString().data(),MNT_FORCE)!=0){
//syslog(LOG_DEBUG,"ERRNO %d at %d.",errno,i);
                usleep(20000);i--;
            }
        }
        if(xPass.isEmpty()|xKey.isEmpty()|xIv.isEmpty()){
            syslog(LOG_ERR,"Missing encrypted password, key or iv.");
            return;
        }
        // Decrpypt password
        QCA::Initializer init;
        if(!QCA::isSupported("aes128-cbc-pkcs7")){
            syslog(LOG_ERR,"AES128-CBC not supported! Provider (libqca-ossl.so) not installed?");
            return;
        }
        QCA::SymmetricKey key(QCA::hexToArray(xKey));
        QCA::InitializationVector iv(QCA::hexToArray(xIv));
        QCA::Cipher cipher(
                QString("aes128"),QCA::Cipher::CBC,
                QCA::Cipher::DefaultPadding,
                QCA::Decode,
                key,iv);
        password=QString(QCA::SecureArray(cipher.process(QCA::hexToArray(xPass))).data());
        if(!cipher.ok()){
            syslog(LOG_ERR,"Cipher decryption failed.");
            return;
        }
        syslog(LOG_DEBUG,"Got password from %s",passwordFile.fileName().toStdString().data());
// !!!!!!!!!!! DEVELOPMENT ONLY !!!!!!!!!!!!!
//syslog(LOG_DEBUG,"Have password %s",password.toStdString().data());
// !!!!!!!!!!! DEVELOPMENT ONLY !!!!!!!!!!!!!
    }
}

QString UserSettings::mountUuid(QString uuid){
    const char *filesystems[6]={"vfat","ext2","ext3","ext4","ntfs",(const char*)NULL};
    QString mountPoint;
    QString devName=("/dev/disk/by-uuid/");
    devName.append(uuid);
    QFile dev(devName);
    if(dev.exists()){
//syslog(LOG_DEBUG,"Device %s exists.",dev.fileName().toStdString().data());
        devName=dev.symLinkTarget();
//syslog(LOG_DEBUG,"Device target %s.",devName.toStdString().data());
        QFile mtab("/etc/mtab");
        if(!mtab.open(QIODevice::ReadOnly)){
            syslog(LOG_ERR,"Could not open \"/etc/mtab\".");
            return mountPoint;
        }
//        while(!mtab.atEnd()){
	QTextStream mt(&mtab);
        while(true){
            QString line=mt.readLine();
	    if(line.isNull())break;
	    if(line.isEmpty())continue;
//syslog(LOG_DEBUG,"LINE %s.",line.toStdString().data());
            if(line.startsWith(devName)){
                mountPoint=line.section(' ',1,1);
		mtab.close();
                return mountPoint;
            }
        }
	mtab.close();
        umountRequired=true;
//syslog(LOG_DEBUG,"Device %s is not mounted.",dev.fileName().toStdString().data());
        // create a mount point
        QDir tmpDir(QDir::tempPath()+"/"+uuid);
        if(!tmpDir.exists()){
            tmpDir=QDir(QDir::tempPath());
            if(!tmpDir.mkdir(uuid)){
                syslog(LOG_ERR,"Could not create mount point %s/%s.",tmpDir.absolutePath().toStdString().data(),uuid.toStdString().data());
                umountRequired=false;
                return mountPoint;
            }
            tmpDir=QDir(QDir::tempPath()+"/"+uuid);
        }
        // try to mount the device
        // first try mounting common filesystem types from "filesystems" list
        for(int i=0;i<6;i++){
            if(mount(devName.toStdString().data(),tmpDir.absolutePath().toStdString().data(),filesystems[i],MS_MGC_VAL|MS_RDONLY|MS_NOSUID,"")==0){
//syslog(LOG_DEBUG,"Type %s mounted.",filesystems[i]);
                return tmpDir.absolutePath();
            }
        }
        // Try possible other filesystems from /proc/filesystems
        QFile fstypes("/proc/filesystems");
        if(!fstypes.open(QIODevice::ReadOnly)){
            syslog(LOG_ERR,"Could not open /proc/filesystems.");
            umountRequired=false;
            return mountPoint;
        }
        while(true){
            QString line=fstypes.readLine();
            if(line.isEmpty())
                break;
            if(!line.startsWith("nodev")){
                QString fstype(QString(line.section('\t',1,1)).trimmed());
//syslog(LOG_DEBUG,"Trying %s with type %s.",devName.toStdString().data(),fstype.toStdString().data());
                if(mount(devName.toStdString().data(),tmpDir.absolutePath().toStdString().data(),fstype.toStdString().data(),MS_MGC_VAL|MS_RDONLY|MS_NOSUID,"")==0){
//syslog(LOG_DEBUG,"Type %s mounted.",fstype.toStdString().data());
                    return tmpDir.absolutePath();
                }
            }
        }
    }
    else{
        syslog(LOG_DEBUG,"Device %s not found.",dev.fileName().toStdString().data());
    }
    umountRequired=false;
    return mountPoint;
}

bool UserSettings::getPassword(char **passwd){
    if(!providePassword|password.isEmpty())
        return false;
    *passwd=(char*)malloc(strlen(password.toStdString().data())+1);
    if(*passwd){
        strcpy(*passwd,password.toStdString().data());
        return true;
    }
    return false;
}

const char* UserSettings::getPathToMedia(){
    if(!providePassword|password.isEmpty())
        return NULL;
    QString pathToMedia(pathToPassword.left(pathToPassword.indexOf(QString(PASSWORD_DIR),0)));
    return pathToMedia.toStdString().data();
}

// Constructor used for encryption and save settings
UserSettings::UserSettings(char *extDir,char *uuid,char *userName,char *machineName){
    providePassword=true;
    this->uuid=QString(uuid);
    pathToPassword=QString(extDir);
    while(pathToPassword.endsWith("/"))pathToPassword.truncate(pathToPassword.length()-1);
    if(!pathToPassword.endsWith(PASSWORD_DIR))pathToPassword.append(PASSWORD_DIR);
    passwordDir=pathToPassword;
    pathToPassword.append("/");
    pathToPassword.append(userName);
    pathToPassword.append("@");
    pathToPassword.append(machineName);
    pathToPassword.append(".xml");
    pathToConfig.append("/tmp/config.xml");
    this->user=QString(userName);
}

UserSettings::~UserSettings() {
}

void writeProperty(XmlWriter& xw,const QString& name,const QString& value){
    xw.writeOpenTag(name,AttrMap("value",value));
    xw.writeCloseTag(name);
}

bool UserSettings::writeConfig(char *passwd,bool debug){
    pid_t child;
    int rc;
    providePassword=false;
    QFile configFile(pathToConfig);
    if(!configFile.open(QIODevice::ReadWrite)){
        syslog(LOG_ERR,"Could not open config file %s.",configFile.fileName().toStdString().data());
        return false;
    }

    if(passwd!=NULL){
        QCA::Initializer init;
        if(!QCA::isSupported("aes128-cbc-pkcs7")){
            syslog(LOG_ERR,"AES128-CBC not supported! Provider (libqca-ossl.so) not installed?");
        }
        else {
            QCA::SecureArray clearPassword=passwd;
            // Create a random key
            QCA::SymmetricKey key(16);
           // Create a random initialisation vector
            QCA::InitializationVector iv(16);
            // create a 128 bit AES cipher object using Cipher Block Chaining (CBC) mode
            QCA::Cipher cipher(
                    QString("aes128"),QCA::Cipher::CBC,
                    QCA::Cipher::DefaultPadding,
                    QCA::Encode,
                    key,iv);
            QCA::SecureArray cipherPassword=QCA::SecureArray(cipher.process(clearPassword));
            if(cipher.ok()){
                xKey=QString(QCA::arrayToHex(key.toByteArray()));
                xIv=QString(QCA::arrayToHex(iv.toByteArray()));
                xPass=QString(QCA::arrayToHex(cipherPassword.toByteArray()));
// !!!!!!!!!!! DEVELOPMENT ONLY !!!!!!!!!!!!!
//syslog(LOG_DEBUG,"clear %s, key %s, iv %s, cipher %s",
//            passwd,
//            xKey.toStdString().data(),
//            xIv.toStdString().data(),
//            xPass.toStdString().data()
//            );
// !!!!!!!!!!! DEVELOPMENT ONLY !!!!!!!!!!!!!
                providePassword=true;
            }
            else{
                syslog(LOG_ERR,"Cipher encryption failed! Encrypted password not saved.");
            }
        }
    }

    QDir passDir(passwordDir);
    if(!passDir.exists()){
        if(!passDir.mkpath(passwordDir)){
            syslog(LOG_ERR,"Could not create directory: %s.",passwordDir.toStdString().data());
            providePassword=false;
        }
    }

    QFile passwordFile(pathToPassword);
    if(passwordFile.open(QIODevice::ReadWrite)){
        // Save encrypted password to password file
        XmlWriter xmlWriter(&passwordFile);
        xmlWriter.setAutoNewLine( true );
        xmlWriter.writeRaw( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
        xmlWriter.newLine();
        xmlWriter.writeOpenTag(GUI_NAME,AttrMap("version",VERSION));
            xmlWriter.writeOpenTag("object",AttrMap("class","UserSettings"));
                writeProperty(xmlWriter,"pass",xPass);
            xmlWriter.writeCloseTag("object");
        xmlWriter.writeCloseTag(GUI_NAME);
        passwordFile.resize(passwordFile.pos());// truncate file
        passwordFile.close();
    }
    else{
        syslog(LOG_ERR,"Could not open password file %s. Encrypted password not saved.",passwordFile.fileName().toStdString().data());
        providePassword=false;
    }

    // Save settings to config file
    XmlWriter xmlWriter(&configFile);
    xmlWriter.setAutoNewLine( true );
    xmlWriter.writeRaw( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
    xmlWriter.newLine();
    xmlWriter.writeOpenTag(GUI_NAME,AttrMap("version",VERSION));
        xmlWriter.writeOpenTag("object",AttrMap("class","UserSettings"));
            writeProperty(xmlWriter,"providePassword",QString(providePassword?"true":"false"));
            writeProperty(xmlWriter,"uuid",uuid.toStdString().data());
            writeProperty(xmlWriter,"pathToPassword",pathToPassword.toStdString().data());
            writeProperty(xmlWriter,"iv",xIv.toStdString().data());
            writeProperty(xmlWriter,"key",xKey.toStdString().data());
        xmlWriter.writeCloseTag("object");
    xmlWriter.writeCloseTag(GUI_NAME);
    configFile.resize(configFile.pos());// truncate file
    configFile.close();

    // save configfile to /var/lib/<username>/
    child=fork();           // here we start a child process that saves configfile
    switch(child){
        case 0:             // This is the child
            rc=execl("/usr/bin/pkexec","pkexec",WRITE_COMMAND,
                    ARG_USER,user.toStdString().data(),
		    ARG_FILE,"config.xml",
                    debug?ARG_DEBUG1:NULL,
                    NULL);
           syslog(LOG_ERR,"ERROR: Could not execute %s %d (%s).",WRITE_COMMAND,rc,strerror(errno));
            _exit(EXIT_FAILURE);
        case -1:            // Fork error
            syslog(LOG_ERR,"ERROR FORKING CHILD PROCESS.");
            return false;
        default:            // This is the parent
            syslog(LOG_DEBUG,"Child PID: %d.",child);
            waitpid(child,&rc,0);
            if(rc!=EXIT_SUCCESS){
                syslog(LOG_ERR,"ERROR: %s returned %d.",WRITE_COMMAND_NAME,rc);
                return false;
            }
    }
    return providePassword;
}
