TEMPLATE = app
CONFIG += qt thread
TARGET = fingerprint-identifier
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
BINDIR  = $${PREFIX}/bin
LIBEXECDIR = $${PREFIX}/$${LIBEXEC}/fingerprint-gui
MAN1DIR = $${PREFIX}/share/man/man1

target.path   = $${BINDIR}
manpage.path  = $${MAN1DIR}
manpage.files = ../../man/$${TARGET}.1
INSTALLS += target manpage

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

LIBS += -lusb-1.0 -lfprint -lpam -ldl

# Input
HEADERS += ../../include/GlobalsImg.h \
           ../../include/DeviceHandler.h \
           ../../include/Fingercodes.h \
           ../../include/FingerprintDevice.h \
           ../../src/drivers/UpekDevice.h \
           ../../src/drivers/GenericDevice.h \
           ../../include/FingerprintData.h \
           ../../include/FingerprintDiscoverer.h \
           ../../include/Globals.h \
           ../../include/UsbDevice.h \
           ../../include/IdentifierGUI.h
FORMS += ../../src/FingerprintIdentifier.ui
SOURCES += ../../src/GlobalsImg.cpp \
           ../../src/DeviceHandler.cpp \
           ../../src/UsbDevice.cpp \
           ../../src/drivers/UpekDevice.cpp \
           ../../src/drivers/GenericDevice.cpp \
           ../../src/FingerprintData.cpp \
           ../../src/FingerprintDiscoverer.cpp \
           ../../src/IdentifierGUI.cpp \
           ../../src/FingerprintIdentifier.cpp
RESOURCES += ../../src/widget-res.qrc
