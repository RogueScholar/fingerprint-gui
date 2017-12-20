/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamTester.cpp, PamTester.h
 * Purpose: Testing of PAM settings with "libpam_fingerprint.so"
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

#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include "PamTester.h"

volatile bool stopTester=false;
static volatile bool returnPressed=false;
static pam_response* pamResponse=NULL; 
QApplication *app;

TestFifoReader::TestFifoReader(QLabel *la,QLabel *bar){
    statusBar=bar;
    label=la;   // The QLabel to put text to received from named pipe
}

void TestFifoReader::run(){
//    QFont font;

    if((fifo=open(PLUGIN_FIFO,O_RDONLY))<0){    // This blocks until someone has opened the other end for write
        syslog(LOG_ERR,"Error open fifo: %s: %s",strerror(errno),PLUGIN_FIFO);
        return;
    }
    syslog(LOG_DEBUG,"Fifo opened: %d",fifo);
    char line[1024];
    int rc;
    while(true){
        rc=read(fifo,line,1024);
        if(rc>0){
            line[rc-1]='\0';
            int end=0;
            while(end<rc){
                int pos=0;
                string s=string(&line[end]);
                syslog(LOG_DEBUG,"Read from fifo: %s",s.data());
                if(s.find(MSG_STOP)!=string::npos){     // Stop fingerprint-plugin
                    syslog(LOG_DEBUG,"Received STOP message");
                    close(fifo);
                    return;
                }
                if(s.find(MSG_ALIVE)!=string::npos){
//                    syslog(LOG_DEBUG,"ALIVE-%d",++i);
                }
                if(s.find(MSG_LABEL)!=string::npos){    // Show message on label
                    pos=strlen(MSG_LABEL);
                    string finger=s.substr(pos,string::npos);
                    label->setText(finger.data());
                }
                if(s.find(MSG_BOLD)!=string::npos){     // Show message bold on statusBar
//                    font.setPointSize(10);
//                    font.setBold(true);
//                    statusBar->setFont(font);
                    pos=strlen(MSG_BOLD);
                    statusBar->setText((s.substr(pos,string::npos)).data());
                }
                if(s.find(MSG_NORMAL)!=string::npos){   // Show message normal on statusBar
//                    font.setPointSize(9);
//                    font.setBold(false);
//                    statusBar->setFont(font);
                    pos=strlen(MSG_NORMAL);
                    statusBar->setText((s.substr(pos,string::npos)).data());
                }
                if((s.substr(pos,string::npos)).find(MSG_AUTH)!=string::npos){// User authenticated
                    syslog(LOG_DEBUG,"Received AUTH message");// for debug only
                }
                while(line[end++]!='\0') ;
            }
        }
    }
}

int callback(int,const struct pam_message **,struct pam_response **resp,void *){
    pamResponse=(pam_response*)malloc(sizeof(pam_response));
    closelog();
    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    if(debugTest)
        setlogmask(-1);
    else
        setlogmask(LOG_UPTO(LOG_ERR));
    syslog(LOG_DEBUG,"PAM_CALLBACK, waiting.");
    while(!(returnPressed)){
        app->processEvents();
        usleep(50000);
    }
    usleep(100000);
    pamResponse->resp=strdup("");
    pamResponse->resp_retcode=PAM_SUCCESS;
    *resp=pamResponse;
    syslog(LOG_DEBUG,"PAM_CALLBACK return PAM_SUCCESS.");
    return PAM_SUCCESS;
}

PamTester::PamTester(QLabel *label1,QLabel *label2,const char *svc,bool identify){
    if(svc==NULL)return; //uups
    struct passwd *pws=getpwuid(geteuid());
    service=svc;
    pamconv=(pam_conv){callback,NULL};
    pamh=NULL;
    user=NULL;
    app=qApp;
    if(!identify){   // This service doesn't require to identify the user
        user=pws->pw_name;
    }
    label1->setText("Please swipe a finger...");
    fifoReader=new TestFifoReader(label1,label2);
}

void PamTester::testPam(DeviceHandler *deviceHandler,QLineEdit *result){
    stopTester=false;
    returnPressed=false;
    int rc;
    line=result;
    string message;

    mkfifo(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
    chmod(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
    syslog(LOG_DEBUG,"Testing service \"%s\"",service);
    line->clear();
    line->setFocus();
// Release the fingerprint device so pam_fingerprint-gui.so can use it
    deviceHandler->release();

    if((rc=pam_start(service,user,&pamconv,&pamh))!=PAM_SUCCESS){
        syslog(LOG_ERR,"Error PAM_START: %s.",pam_strerror(pamh,rc));
        return;
    }
    connect(line,SIGNAL(returnPressed()),this,SLOT(haveResult()));
    fifoReader->start();
    line->setText("");
    if((rc=pam_authenticate(pamh,0))!=PAM_SUCCESS){
        message=string("Fingerprint authentication failed.");
    }
    else{
        message=string("Authentication successful.");
    }
    disconnect(line,SIGNAL(returnPressed()),this,SLOT(haveResult()));
    if((rc=pam_end(pamh,rc))!=PAM_SUCCESS){
        syslog(LOG_ERR,"Error PAM_END: %s.",pam_strerror(pamh,rc));
    }

// Grab the fingerprint device so we can use it again    
    deviceHandler->initialize();
    line->setText(message.data());
    syslog(LOG_DEBUG,"Message: %s.",message.data());
    unlink(PLUGIN_FIFO);
}

void PamTester::haveResult(){
    syslog(LOG_DEBUG,"Caught line input.");
    returnPressed=true;
}
