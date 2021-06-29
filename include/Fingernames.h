/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: Fingercodes.h
 * Purpose: defines numbering of fingers
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

#ifndef _FINGERNAMES_H
#define _FINGERNAMES_H

#include <QtGlobal>

#include "Globals.h"

static const char *fingers[] = {
    QT_TRANSLATE_NOOP("Fingernames", "Left Little"),
    QT_TRANSLATE_NOOP("Fingernames", "Left Ring"),
    QT_TRANSLATE_NOOP("Fingernames", "Left Middle"),
    QT_TRANSLATE_NOOP("Fingernames", "Left Index"),
    QT_TRANSLATE_NOOP("Fingernames", "Left Thumb"),
    QT_TRANSLATE_NOOP("Fingernames", "Right Thumb"),
    QT_TRANSLATE_NOOP("Fingernames", "Right Index"),
    QT_TRANSLATE_NOOP("Fingernames", "Right Middle"),
    QT_TRANSLATE_NOOP("Fingernames", "Right Ring"),
    QT_TRANSLATE_NOOP("Fingernames", "Right Little")};

#endif /* _FINGERCODES_H */
