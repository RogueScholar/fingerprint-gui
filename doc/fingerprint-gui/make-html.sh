#!/bin/sh
# SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
# SPDX-FileCopyrightText: 🄯 2019-2021 Peter J. Mello <admin@petermello.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
# -----------------------------------------------------------------------------
# A simple script to make new HTML files from XML sources

XML="$(ls -- ./*.xml)"
echo "${XML}"
rm -v ./*.html

for output in ${XML}; do
  xmlto html-nochunks "${output}"
done
