TEMPLATE = app
CONFIG += qt thread crypto
TARGET = fingerprint-gui
QT += xml
DEPENDPATH += . ../../include ../../src
INCLUDEPATH += . ../../include ../../upek/include

isEmpty(PREFIX) {
	PREFIX = /usr/local
}
isEmpty(LIB) {
	LIB = lib
}
isEmpty(LIBEXEC) {
	LIBEXEC = lib
}
BINDIR     = $${PREFIX}/bin
LIBEXECDIR = $${PREFIX}/$${LIBEXEC}/fingerprint-gui
SHAREDIR   = $${PREFIX}/share
MAN1DIR    = $${PREFIX}/share/man/man1
DOCDIR     = $${PREFIX}/share/doc/fingerprint-gui

target.path     = $${BINDIR}
desktop.path    = $${SHAREDIR}/applications
desktop.files   = fingerprint-gui.desktop
pixmaps.path    = $${SHAREDIR}/pixmaps
pixmaps.files   = ../../src/res/fingerprint-gui.xpm
icons16x16.path = $${SHAREDIR}/icons/hicolor/16x16/apps
icons16x16.files= ../../src/res/hicolor/16x16/apps/fingerprint-gui.png
icons24x24.path = $${SHAREDIR}/icons/hicolor/24x24/apps
icons24x24.files= ../../src/res/hicolor/24x24/apps/fingerprint-gui.png
icons32x32.path = $${SHAREDIR}/icons/hicolor/32x32/apps
icons32x32.files= ../../src/res/hicolor/32x32/apps/fingerprint-gui.png
icons48x48.path = $${SHAREDIR}/icons/hicolor/48x48/apps
icons48x48.files= ../../src/res/hicolor/48x48/apps/fingerprint-gui.png
icons96x96.path = $${SHAREDIR}/icons/hicolor/96x96/apps
icons96x96.files= ../../src/res/hicolor/96x96/apps/fingerprint-gui.png
manpage.path    = $${MAN1DIR}
manpage.files   = ../../man/$${TARGET}.1
help.path       = $${DOCDIR}
help.files      = ../../doc/Manual_??.html \
		  ../../doc/*.png
directory.path  = /var/lib/fingerprint-gui
directory.extra = :
INSTALLS += target desktop pixmaps icons16x16 icons24x24 icons32x32 icons48x48 icons96x96 manpage help directory

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

LIBS += -lusb-1.0 -lfprint -lpam -ldl -lqca

# Input
HEADERS += ../../include/GlobalsImg.h \
           ../../include/DeviceHandler.h \
           ../../include/Globals.h \
           ../../include/AboutImpl.h \
           ../../include/ExistDialogImpl.h \
           ../../include/Fingercodes.h \
           ../../include/Fingerprint.h \
           ../../include/FingerprintDevice.h \
           ../../include/FingerprintData.h \
           ../../src/drivers/UpekDevice.h \
           ../../src/drivers/GenericDevice.h \
           ../../include/MainWindowImpl.h \
           ../../include/SavedDialogImpl.h \
           ../../include/MessageDialogImpl.h \
           ../../include/PamTester.h \
           ../../include/xmlwriter.h \
           ../../include/UserSettings.h \
           ../../include/UsbDevice.h

FORMS += ../../src/About.ui \
         ../../src/ExistDialog.ui \
         ../../src/FingerprintGUI.ui \
         ../../src/SavedDialog.ui \
         ../../src/Message.ui

SOURCES += ../../src/GlobalsImg.cpp \
           ../../src/DeviceHandler.cpp \
           ../../src/AboutImpl.cpp \
           ../../src/ExistDialogImpl.cpp \
           ../../src/Fingerprint.cpp \
           ../../src/FingerprintData.cpp \
           ../../src/drivers/UpekDevice.cpp \
           ../../src/drivers/GenericDevice.cpp \
           ../../src/FingerprintGUI.cpp \
           ../../src/MainWindowImpl.cpp \
           ../../src/SavedDialogImpl.cpp \
           ../../src/MessageDialogImpl.cpp \
           ../../src/PamTester.cpp \
           ../../src/xmlwriter.cpp \
           ../../src/UserSettings.cpp \
           ../../src/UsbDevice.cpp

RESOURCES += ../../src/GUI-res.qrc\
             ../../src/About-res.qrc
