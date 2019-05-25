TEMPLATE = app
CONFIG += qt thread
TARGET = fingerprint-polkit-agent
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
XDGDIR     = /etc/xdg

target.path     = $${LIBEXECDIR}

desktop.extra = sed -e \"s,LIBEXECDIR,$${LIBEXECDIR},\" fingerprint-polkit-agent.desktop.in > fingerprint-polkit-agent.desktop
desktop.path    = $${XDGDIR}/autostart
desktop.files = fingerprint-polkit-agent.desktop

INSTALLS += target desktop

DEFINES +=LIBEXECDIR=\\\"$${LIBEXECDIR}\\\"
QMAKE_CXXFLAGS+=-fno-strict-aliasing

LIBS += -lusb-1.0 -lfprint -lX11 -lpolkit-qt-agent-1 -lpolkit-qt-core-1

# Input
HEADERS += \
        ../../include/GlobalsImg.h \
        ../../include/PolkitListener.h \
        ../../include/PolkitDialogImpl.h \
        ../../include/PluginDialog.h \
        ../../include/Globals.h

FORMS += \
        ../../src/FingerprintPlugin.ui \
        ../../src/PolkitDialog.ui \
        ../../src/PolkitDetails.ui

SOURCES += \
        ../../src/GlobalsImg.cpp \
        ../../src/PluginDialog.cpp \
        ../../src/PolkitListener.cpp \
        ../../src/PolkitDialogImpl.cpp \
        ../../src/FingerprintPolkit.cpp

RESOURCES += ../../src/widget-res.qrc
