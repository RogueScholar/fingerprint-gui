/****************************************************************************
** Meta object code from reading C++ file 'Fingerprint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/Fingerprint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Fingerprint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Fingerprint_t {
    QByteArrayData data[11];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fingerprint_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fingerprint_t qt_meta_stringdata_Fingerprint = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Fingerprint"
QT_MOC_LITERAL(1, 12, 12), // "neededStages"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "stages"
QT_MOC_LITERAL(4, 33, 15), // "acquireFinished"
QT_MOC_LITERAL(5, 49, 6), // "result"
QT_MOC_LITERAL(6, 56, 12), // "fp_pic_data*"
QT_MOC_LITERAL(7, 69, 3), // "pic"
QT_MOC_LITERAL(8, 73, 14), // "verifyFinished"
QT_MOC_LITERAL(9, 88, 16), // "newAcquireResult"
QT_MOC_LITERAL(10, 105, 15) // "newVerifyResult"

    },
    "Fingerprint\0neededStages\0\0stages\0"
    "acquireFinished\0result\0fp_pic_data*\0"
    "pic\0verifyFinished\0newAcquireResult\0"
    "newVerifyResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fingerprint[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    2,   42,    2, 0x06 /* Public */,
       8,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   52,    2, 0x0a /* Public */,
      10,    2,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,

       0        // eod
};

void Fingerprint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fingerprint *_t = static_cast<Fingerprint *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->neededStages((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->acquireFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 2: _t->verifyFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 3: _t->newAcquireResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->newVerifyResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Fingerprint::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fingerprint::neededStages)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Fingerprint::*_t)(int , fp_pic_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fingerprint::acquireFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Fingerprint::*_t)(int , fp_pic_data * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fingerprint::verifyFinished)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Fingerprint::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Fingerprint.data,
      qt_meta_data_Fingerprint,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Fingerprint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fingerprint::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Fingerprint.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Fingerprint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Fingerprint::neededStages(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Fingerprint::acquireFinished(int _t1, fp_pic_data * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Fingerprint::verifyFinished(int _t1, fp_pic_data * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
