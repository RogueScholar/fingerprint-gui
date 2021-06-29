/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: AboutImpl.cpp, AboutImpl.h
 * Purpose: About dialog
 *
 * @author Wolfgang Ullrich
 */

#ifndef _ABOUTIMPL_H
#define _ABOUTIMPL_H

#include "ui_About.h"
#include <QObject>
#include <QtGui>
#include <iostream>
#include <qstring.h>
#include <qwidget.h>
#include <string>

#include "Globals.h"

using namespace std;

class AboutImpl : public QDialog, public Ui::AboutDialog {
  Q_OBJECT

public:
  AboutImpl(QWidget *parent = 0, Qt::WindowFlags f = 0);

private slots:
  void bitcoin();
  void donate();
  void license();
  void homepage();
};

#endif /* _ABOUTIMPL_H */
