# Fingerprint GUI

Fingerprint GUI is an application providing fingerprint-based authentication on
Linux desktops. Based on the libfprint library, it features a simple GUI for
fingerprint management and a PAM module. Additionally, you may install the
bundled non-free libbsapi library, in which case Fingerprint GUI will
automatically support all fingerprint readers manufactured by UPEK, Inc.

## Supported hardware

The list of fingerprint readers supported by libfprint is available [here](https://fprint.freedesktop.org/supported-devices.html).

If you install the libbsapi library, then all hardware by UPEK should be
supported as well.

## Compilation

### Prepare the build environment

This project is built using the Qt 4 development framework. The required
packages can be installed on any recent Debian-based Linux distributions with
the command:

```bash
sudo apt install -y libqt4-dev libqt4-dev-bin libqtcore4 qtcore4-l10n \
qt4-dev-tools qt4-qmake qt4-qtconfig qtchooser
```

### Install dependencies

In order to compile the software you will need development packages for
libfprint, libqt4, libqca2, libfakekey, libusb-1.0, libpolkit-qt-1 and libpam.

If you are running a recent Debian-based distribution, use the
following command:

```bash
sudo apt install -y libfprint-dev libqt4-dev libqt4-dev-bin libqca2-dev \
libqca2-plugins libfakekey-dev libusb-1.0-0-dev libpolkit-qt-1-dev libpam0g-dev
```

### Generate the Makefile

```bash
qmake -makefile fingerprint.pro
```

or use the included shell script

```bash
bash ./qmake.sh
```

#### Installation paths

By default, everything gets installed under `/usr/local/`. If you want to
change the prefix to `/usr/`, you can generate the Makefile by running:

```bash
qmake -makefile fingerprint.pro PREFIX=/usr
```

Additionally, libraries are installed into `$PREFIX/$LIB`, helper executables
go into `$PREFIX/$LIBEXEC`, and the PAM module is installed into
`$LIB/security`. The default value for both `$LIB` and `$LIBEXEC` is `/lib`,
which should be suitable for most Linux distributions. However, should you need
to adjust the value of these two variables, you can set them in the same way as
`$PREFIX` above. For instance, on 64-bit Fedora you would generate the Makefile
with:

```bash
qmake -makefile fingerprint.pro LIB=/lib64 LIBEXEC=/libexec
```

or with

```bash
qmake -makefile fingerprint.pro PREFIX=/usr LIB=/lib64 LIBEXEC=/libexec
```

if you want to install into /usr.

### Build the software

```bash
make -j$(nproc)
```

### Install the compiled software

```bash
sudo make install
```

### Add support for UPEK readers (install the bundled proprietary library `libbsapi`)

```bash
sudo make install-upek
```

### Upgrading from older versions

Beginning with version 1.07 of Fingerprint GUI, the ownership and
permissions of users' fingerprint data in `/var/lib/fingerprint-gui/` has been
changed. To apply the new ownership and permissions needed for version 1.07 and
above to fingerprint data from an older version, run:

```bash
sudo make user-data
```

## Account membership

Please note that every user that wants to use this library must be member of
group `plugdev`. This group is created automatically. The following command
will add your current user account to the `plugdev` group:

```bash
sudo usermod -a -G plugdev $(id -un)
```

## PAM configuration

See the following guides for instructions on how to modify your PAM stack to
enable fingerprint-based authentication:

* [Fingerprint GUI Step-By-Step Manual](http://www.ullrich-online.cc/fingerprint/doc/Step-by-step-manual.html#idp34500608)
* [ArchWiki](https://wiki.archlinux.org/index.php/Fingerprint_GUI)
* [ThinkWiki](http://www.thinkwiki.org/wiki/How_to_enable_the_integrated_fingerprint_reader)

## License

This software is released under GPL-2+. See [COPYING](COPYING) for the full
text of the license.

Copyright © 2008-2015 Wolfgang Ullrich <contact@ullrich-online.cc>

## Bugs

Bugs can be sent directly to the author or posted in the [forums](http://home.ullrich-online.cc/fingerprint/Forum/).
