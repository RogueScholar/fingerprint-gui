/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintHelper.h
 * Purpose: Helper process to be used for PAM authentication
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * @author  Wolfgang Ullrich
 * Copyright (C) 2008-2016 Wolfgang Ullrich
 */

/*
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _FINGERPRINTHELPER_H
#define	_FINGERPRINTHELPER_H

#include <stdio.h>
#include <string>

using namespace std;

void pluginMessage(const char *msg);

#endif	/* _FINGERPRINTHELPER_H */

