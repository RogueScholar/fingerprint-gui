/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: PamNonGUI.cpp, PamNonGUI.h
 * Purpose: Main object for libpam_fingerprint module for running in non-gui environments
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

#include <unistd.h>
#include "PamNonGUI.h"
#include "FingerprintHelper.h"

#define NORMAL  "[0;39m"
#define RED     "[1;31m"
#define GREEN   "[1;32m"
#define YELLOW  "[1;33m"
#define BLUE    "[1;34m"
#define MAGENTA "[1;35m"
#define CYAN    "[1;36m"
#define WHITE   "[1;37m"

// Helper for sending messages to PAM prompt -----------------------------------
void PamNonGUI::pamMessage(const char *target,const char *style,const char *msg){
    if(prompt)
        printf("%s%s%s\n",style,msg,NORMAL);
    if(target==NULL)
        return;
    string fifoMsg(""); // Compose a message for fingerprint-plugin
    fifoMsg.append(target);
    fifoMsg.append(msg);
    fifoMsg.append("\0");
    pluginMessage(fifoMsg.data());
}

// NonGUI object ---------------------------------------------------------------
PamNonGUI::PamNonGUI(bool writeToPrompt,FingerprintDevice *dev,const char *user,const char *fing,QObject* parent)
: QObject(parent) {
    result=-2;
    repeatDelay=0;
    device=dev;
    finger=fing;
    prompt=writeToPrompt;

    connect(device,SIGNAL(matchResult(int,struct fp_pic_data*)),this,SLOT(matchResult(int,struct fp_pic_data*)));
    connect(device,SIGNAL(verifyResult(int,struct fp_pic_data*)),this,SLOT(newVerifyResult(int,struct fp_pic_data*)));
    device->start();
    usleep(100000);             //Give it a chance to stop with some error
    if(!device->isRunning())    //Exit quietly if device is not running for some reason
        return;

    string title=string("\nFingerprint Login ");
    title.append(VERSION);
    pamMessage(NULL,MAGENTA,title.data());
    string s=string("Authenticating ");
    s.append(user);
    pamMessage(MSG_NORMAL,MAGENTA,s.data());
    s=string("Swipe your ");
    if(finger==NULL)
        s.append("finger");
    else
        s.append(finger);
    s.append(" or type your password:");
    pamMessage(NULL,MAGENTA,s.data());
    START_TIMER
}

PamNonGUI::~PamNonGUI(){
    device->stop();
}

// slots -----------------------------------------------------------------------
void PamNonGUI::matchResult(int match,struct fp_pic_data __attribute__ ((unused)) *pic){
    device->stop();
    if(match>=0){
        syslog(LOG_DEBUG,"showMessage: OK");
        pamMessage(MSG_BOLD,GREEN,"OK");
	timer->stop();
        //exit with index (match) as exit code
        qApp->processEvents();
        device->wait(5000);
        result=match;
        qApp->exit(match);
        return;
    }
    syslog(LOG_DEBUG,"showMessage: Not identified!");
    pamMessage(MSG_BOLD,RED,"Not identified!");
    repeatDelay=3;   //let 'em see the result before exiting
}

void PamNonGUI::newVerifyResult(int result,struct fp_pic_data __attribute__ ((unused)) *pic){
    switch(result){
        case RESULT_VERIFY_NO_MATCH:
            syslog(LOG_DEBUG,"showMessage: No match!");
            pamMessage(MSG_NORMAL,RED,"No match!");
            break;
        case RESULT_VERIFY_RETRY_TOO_SHORT:
            syslog(LOG_DEBUG,"showMessage: Swipe too short...");
            pamMessage(MSG_NORMAL,RED,"Swipe too short...");
            break;
        case RESULT_VERIFY_RETRY_CENTER:
            syslog(LOG_DEBUG,"showMessage: Please center...");
            pamMessage(MSG_NORMAL,RED,"Please center...");
            break;
        case RESULT_VERIFY_RETRY:
        case RESULT_VERIFY_RETRY_REMOVE:
            syslog(LOG_DEBUG,"showMessage: Try again...");
            pamMessage(MSG_NORMAL,RED,"Try again...");
            break;
    }
}

// Helper thread for restart
void PamNonGUI::timerTick(){
    string s;
    pluginMessage(MSG_ALIVE);
    switch(repeatDelay){
        case 0:
            if(!device->isRunning()){
                syslog(LOG_ERR,"ERROR: Fingerprint device not running.");
                qApp->exit(-1);
                return;
            }
            //do nothing
            break;
        case 1:
            syslog(LOG_INFO,"Waiting for device to stop...");
            device->wait(5000);
            syslog(LOG_INFO,"Stopped, restarting");
            //restart fingerprint scanner
            s=string("Swipe your ");
            if(finger==NULL)
                s.append("finger");
            else
                s.append(finger);
            s.append(" or type your password:");
            pamMessage(NULL,MAGENTA,s.data());
            device->start();
            repeatDelay--;
            break;
        default:
            repeatDelay--;  //still wait
    }
}
