/****************************************************************************
** Meta object code from reading C++ file 'FingerprintDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/FingerprintDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FingerprintDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FingerprintDevice_t {
    QByteArrayData data[12];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FingerprintDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FingerprintDevice_t qt_meta_stringdata_FingerprintDevice = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FingerprintDevice"
QT_MOC_LITERAL(1, 18, 12), // "neededStages"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "stages"
QT_MOC_LITERAL(4, 39, 13), // "acquireResult"
QT_MOC_LITERAL(5, 53, 6), // "result"
QT_MOC_LITERAL(6, 60, 12), // "verifyResult"
QT_MOC_LITERAL(7, 73, 12), // "fp_pic_data*"
QT_MOC_LITERAL(8, 86, 3), // "pic"
QT_MOC_LITERAL(9, 90, 11), // "matchResult"
QT_MOC_LITERAL(10, 102, 5), // "match"
QT_MOC_LITERAL(11, 108, 12) // "noDeviceOpen"

    },
    "FingerprintDevice\0neededStages\0\0stages\0"
    "acquireResult\0result\0verifyResult\0"
    "fp_pic_data*\0pic\0matchResult\0match\0"
    "noDeviceOpen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FingerprintDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    2,   45,    2, 0x06 /* Public */,
       9,    2,   50,    2, 0x06 /* Public */,
      11,    0,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    5,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   10,    8,
    QMetaType::Void,

       0        // eod
};

void FingerprintDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FingerprintDevice *_t = static_cast<FingerprintDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->neededStages((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->acquireResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->verifyResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 3: _t->matchResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 4: _t->noDeviceOpen(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FingerprintDevice::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FingerprintDevice::neededStages)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FingerprintDevice::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FingerprintDevice::acquireResult)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FingerprintDevice::*_t)(int , fp_pic_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FingerprintDevice::verifyResult)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (FingerprintDevice::*_t)(int , fp_pic_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FingerprintDevice::matchResult)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (FingerprintDevice::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FingerprintDevice::noDeviceOpen)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject FingerprintDevice::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FingerprintDevice.data,
      qt_meta_data_FingerprintDevice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FingerprintDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FingerprintDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FingerprintDevice.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int FingerprintDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FingerprintDevice::neededStages(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FingerprintDevice::acquireResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FingerprintDevice::verifyResult(int _t1, fp_pic_data * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FingerprintDevice::matchResult(int _t1, fp_pic_data * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FingerprintDevice::noDeviceOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
