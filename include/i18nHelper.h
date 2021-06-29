/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: i18nHelper.h
 * Purpose: Internationalization definitions
 *
 * @author Wolfgang Ullrich
 */

#ifndef I18NHELPER_H
#define I18NHELPER_H
#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QTranslator>
#ifndef LOCALE_DIR
#define LOCALE_DIR "."
#endif

#define loadTranslations(app)                                                  \
  QTranslator t;                                                               \
  if (t.load(QLocale(), QString(""), QString(""), QString(LOCALE_DIR)))        \
  app.installTranslator(&t)
#endif // I18NHELPER_H
