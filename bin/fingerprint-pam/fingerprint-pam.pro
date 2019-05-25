TEMPLATE = lib
CONFIG = plugin
TARGET = pam_fingerprint-gui
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
MAN8DIR = $${PREFIX}/share/man/man8

target.path  = /$${LIB}/security
manpage.path  = $${MAN8DIR}
manpage.files = ../../man/$${TARGET}.8
rename.path  = $${target.path}
rename.extra = mv $(INSTALL_ROOT)$${target.path}/lib$${TARGET}.so $(INSTALL_ROOT)$${target.path}/$${TARGET}.so
INSTALLS += target manpage rename
# Caveat: The target is renamed after being copied to its final destination. Hence,
# "make uninstall" will be unable to delete it. There seems to be no workaround applicable.

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

LIBS += -lpam
LIBS += -lX11

# Input
HEADERS += \
        ../../include/Globals.h

SOURCES += \
        ../../src/FingerprintPAM.cpp
