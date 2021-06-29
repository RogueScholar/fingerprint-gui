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

#ifndef _FINGERCODES_H
#define _FINGERCODES_H

#include "Globals.h"

// This translates my own fingercodes like represented in "fingers[]"
// to the enum fp_finger
static const fp_finger fingerCode[10] = {
    /*Left Little*/ LEFT_LITTLE,
    /*Left Ring*/ LEFT_RING,
    /*Left Middle*/ LEFT_MIDDLE,
    /*Left Index*/ LEFT_INDEX,
    /*Left Thumb*/ LEFT_THUMB,
    /*Right Thumb*/ RIGHT_THUMB,
    /*Right Index*/ RIGHT_INDEX,
    /*Right Middle*/ RIGHT_MIDDLE,
    /*Right Ring*/ RIGHT_RING,
    /*Right Little*/ RIGHT_LITTLE};

#endif /* _FINGERCODES_H */
