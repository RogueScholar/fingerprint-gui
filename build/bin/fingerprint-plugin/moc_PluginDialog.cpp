/****************************************************************************
** Meta object code from reading C++ file 'PluginDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/PluginDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PluginDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FifoReader_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FifoReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FifoReader_t qt_meta_stringdata_FifoReader = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FifoReader"
QT_MOC_LITERAL(1, 11, 10), // "showPlugin"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "stopPlugin"
QT_MOC_LITERAL(4, 34, 10), // "okReceived"
QT_MOC_LITERAL(5, 45, 17) // "userAuthenticated"

    },
    "FifoReader\0showPlugin\0\0stopPlugin\0"
    "okReceived\0userAuthenticated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FifoReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FifoReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FifoReader *_t = static_cast<FifoReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showPlugin(); break;
        case 1: _t->stopPlugin(); break;
        case 2: _t->okReceived(); break;
        case 3: _t->userAuthenticated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FifoReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FifoReader::showPlugin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FifoReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FifoReader::stopPlugin)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FifoReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FifoReader::okReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (FifoReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FifoReader::userAuthenticated)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FifoReader::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FifoReader.data,
      qt_meta_data_FifoReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FifoReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FifoReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FifoReader.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int FifoReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FifoReader::showPlugin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FifoReader::stopPlugin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FifoReader::okReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FifoReader::userAuthenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_PluginDialog_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginDialog_t qt_meta_stringdata_PluginDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PluginDialog"
QT_MOC_LITERAL(1, 13, 17), // "userAuthenticated"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "pluginStopped"
QT_MOC_LITERAL(4, 46, 10), // "stopPlugin"
QT_MOC_LITERAL(5, 57, 10) // "showPlugin"

    },
    "PluginDialog\0userAuthenticated\0\0"
    "pluginStopped\0stopPlugin\0showPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PluginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PluginDialog *_t = static_cast<PluginDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userAuthenticated(); break;
        case 1: _t->pluginStopped(); break;
        case 2: _t->stopPlugin(); break;
        case 3: _t->showPlugin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PluginDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginDialog::userAuthenticated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PluginDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginDialog::pluginStopped)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PluginDialog::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PluginDialog.data,
      qt_meta_data_PluginDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PluginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::MainFrame"))
        return static_cast< Ui::MainFrame*>(this);
    return QFrame::qt_metacast(_clname);
}

int PluginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PluginDialog::userAuthenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PluginDialog::pluginStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
