TEMPLATE = app
TARGET = fingerprint-rw
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
POLKIT1DIR = "/usr/share/polkit-1"

target.path = $${LIBEXECDIR}
linkr.path = $${target.path}
linkr.extra = ln -fs $${TARGET} $(INSTALL_ROOT)$${target.path}/$${TARGET}-read
linkw.path  = $${target.path}
linkw.extra = ln -fs $${TARGET} $(INSTALL_ROOT)$${target.path}/$${TARGET}-write
polkit1.extra = sed -e \"s,LIBEXECDIR,$${LIBEXECDIR},\" cc.ullrich-online.fingerprint-gui.policy.in > cc.ullrich-online.fingerprint-gui.policy
polkit1.path  = $${POLKIT1DIR}/actions
polkit1.files = cc.ullrich-online.fingerprint-gui.policy

INSTALLS += target linkr linkw polkit1

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

HEADERS += \
           ../../include/GlobalsImg.h \
           ../../include/Globals.h

SOURCES += \
           ../../src/GlobalsImg.cpp \
           ../../src/FingerprintRw.cpp
