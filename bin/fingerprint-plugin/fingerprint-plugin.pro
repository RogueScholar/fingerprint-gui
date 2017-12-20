TEMPLATE = app
CONFIG += qt thread
TARGET = fingerprint-plugin
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
LIBEXECDIR = $${PREFIX}/$${LIBEXEC}/fingerprint-gui

target.path = $${LIBEXECDIR}
INSTALLS += target

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

HEADERS += \
           ../../include/GlobalsImg.h \
           ../../include/Globals.h \
           ../../include/PluginDialog.h

FORMS += ../../src/FingerprintPlugin.ui

SOURCES += \
           ../../src/GlobalsImg.cpp \
           ../../src/PluginDialog.cpp \
           ../../src/FingerprintPlugin.cpp

RESOURCES += ../../src/widget-res.qrc
