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

#ifndef _FINGERCODES_H
#define _FINGERCODES_H

#include "Globals.h"

// This translates my own finger codes like represented in "fingers[]" to the
// enum fp_finger
static const fp_finger fingerCode[10] = {
    LEFT_LITTLE,
    LEFT_RING,
    LEFT_MIDDLE,
    LEFT_INDEX,
    LEFT_THUMB,
    RIGHT_THUMB,
    RIGHT_INDEX,
    RIGHT_MIDDLE,
    RIGHT_RING,
    RIGHT_LITTLE};

#endif /* _FINGERCODES_H */
