Description
===========
Fingerprint GUI is an application providing fingerprint-based authentication
on Linux desktops. It features a simple GUI for fingerprint management and
a PAM module.

Fingerprint GUI is based on the libfprint library. Additionally, you may
install the bundled non-free libbsapi library. In this case Fingerprint GUI
will automatically support all fingerprint readers manufactured by UPEK, Inc.

Supported hardware
==================
For the list of fingerprint readers supported by libfprint see
http://www.freedesktop.org/wiki/Software/fprint/libfprint/Supported_devices/.
If you install the bundled libbsapi library, then all hardware by UPEK should
be supported as well.

Installation
============
1. Generate the Makefile by running:
	$ qmake-qt4 or use the shell script "qmake.sh"

2. Build the software by running:
	$ make
In order to compile the software you will need development packages for
libfprint (version 0.1.0~pre2 and newer), libqt4, libqca2, libfakekey,
libusb-1.0-0, libpolkit-qt-1 and libpam.

3. Copy all the files into their appropriate locations by running:
	# make install

4. If you want to add support for UPEK readers, install the bundled proprietary
library by running:
	# make install-upek
Please note that every user that wants to use this library must be member of
group plugdev. This group is created automatically.

5. Since version 1.07 the ownership and permissions of users fingerprint data
in "/var/lib/fingerprint-gui/" has been changed. Fingerprint-gui will not work
with old ownership and permissions. To setup this data for version 1.07 change
old fingerprint data (aquired with version 1.06 and below) by running:
	# make user-data

6. See the Step-by-step guide for instructions on how to modify your PAM
stack to enable fingerprint-based authentication.

Note on files destination:
By default, everything gets installed under /usr/local. If you want to change
the prefix to /usr, you can generate the Makefile (step 1) by running:
	$ qmake-qt4 PREFIX=/usr
Additionally, libraries are installed into $PREFIX/$LIB, helper executables go
into $PREFIX/$LIBEXEC, and the PAM module is installed into /$LIB/security. The
default value for both $LIB and $LIBEXEC is "lib", which should be suitable for
most Linux distributions. However, should you need to adjust the value of these
two variables, you can set them in the same fashion as $PREFIX above. For
instance, on 64-bit Fedora you would generate the Makefile with
	$ qmake-qt4 LIB=lib64 LIBEXEC=libexec
or with
	$ qmake-qt4 PREFIX=/usr LIB=lib64 LIBEXEC=libexec
provided you want to install into /usr.

License
=======
This software is released under GPL-2+. See COPYING for full text of the
license.

Copyright © 2008-2015 Wolfgang Ullrich <contact@ullrich-online.cc>

Bugs
====
Bugs can be sent directly to the author or posted in the forums at
http://home.ullrich-online.cc/fingerprint/Forum/ .

Project home page
=================
http://www.ullrich-online.cc/fingerprint/

