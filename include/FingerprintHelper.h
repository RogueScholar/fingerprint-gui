/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintHelper.h
 * Purpose: Helper process to be used for PAM authentication
 *
 * @author Wolfgang Ullrich
 */

#ifndef _FINGERPRINTHELPER_H
#define _FINGERPRINTHELPER_H

#include <stdio.h>
#include <string>

using namespace std;

void pluginMessage(const char *msg);

#endif /* _FINGERPRINTHELPER_H */
