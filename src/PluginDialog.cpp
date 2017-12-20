/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PluginDialog.cpp,PluginDialog.h
 * Purpose: GUI dialog requesting finger swipes
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

#include <sys/poll.h>
#include <unistd.h>
#include <string>
#include <qthread.h>

#include "../include/PluginDialog.h"

using namespace std;

static string syslogIdent=string(PLUGIN_NAME);

FifoReader::FifoReader(QLabel *la,QLabel *bar){
    statusBar=bar;
    label=la;   // The QLabel to put text to received from named pipe
}

void FifoReader::run(){
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
//                syslog(LOG_DEBUG,"Read from fifo: %s",s.data());
                if(s.find(MSG_STOP)!=string::npos){     // Stop fingerprint-plugin
                    syslog(LOG_DEBUG,"Received STOP message");
                    close(fifo);
                    emit stopPlugin();
                    return;
                }
                emit showPlugin();
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
                    syslog(LOG_DEBUG,"Received AUTH message");
                    emit userAuthenticated();
                }
                while(line[end++]!='\0') ;
            }
        }
    }
}

PluginDialog::PluginDialog(QDialog *parent,bool exitOnStop)
    : QFrame(){
    QMovie *movie;
    setupUi(this);
    this->parent=parent;
    this->exitOnStop=exitOnStop;
    fifoReader=new FifoReader(label,statusBar);
    fifoReader->start();
    connect(fifoReader,SIGNAL(showPlugin()),SLOT(show()));
    connect(fifoReader,SIGNAL(stopPlugin()),SLOT(stopPlugin()));
    if(parent){
        connect(fifoReader,SIGNAL(showPlugin()),parent,SLOT(resize()));
    }
    ANIMATION_MOVIE
}

PluginDialog::~PluginDialog(){
    syslog(LOG_DEBUG,"Plugin terminating.");
    fifoReader->terminate();
    fifoReader->wait(5000);
    delete(fifoReader);
}

void PluginDialog::showPlugin(){
    SET_TEXT_COLOR
    show();
}

void PluginDialog::stopPlugin(){
    hide();
    syslog(LOG_DEBUG,"Plugin hidden/stopped.");
    if(exitOnStop){
        qApp->exit(EXIT_SUCCESS);
    }
}
