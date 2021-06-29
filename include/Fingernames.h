/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: Fingercodes.h
 * Purpose: Defines numbering of fingers
 *
 * @author Wolfgang Ullrich
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
