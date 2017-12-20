/****************************************************************************
** Meta object code from reading C++ file 'PolkitListener.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/PolkitListener.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PolkitListener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PolkitListener_t {
    QByteArrayData data[28];
    char stringdata0[385];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PolkitListener_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PolkitListener_t qt_meta_stringdata_PolkitListener = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PolkitListener"
QT_MOC_LITERAL(1, 15, 22), // "initiateAuthentication"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 8), // "actionId"
QT_MOC_LITERAL(4, 48, 7), // "message"
QT_MOC_LITERAL(5, 56, 8), // "iconName"
QT_MOC_LITERAL(6, 65, 18), // "PolkitQt1::Details"
QT_MOC_LITERAL(7, 84, 7), // "details"
QT_MOC_LITERAL(8, 92, 6), // "cookie"
QT_MOC_LITERAL(9, 99, 25), // "PolkitQt1::Identity::List"
QT_MOC_LITERAL(10, 125, 10), // "identities"
QT_MOC_LITERAL(11, 136, 30), // "PolkitQt1::Agent::AsyncResult*"
QT_MOC_LITERAL(12, 167, 6), // "result"
QT_MOC_LITERAL(13, 174, 28), // "initiateAuthenticationFinish"
QT_MOC_LITERAL(14, 203, 20), // "cancelAuthentication"
QT_MOC_LITERAL(15, 224, 8), // "tryAgain"
QT_MOC_LITERAL(16, 233, 21), // "finishObtainPrivilege"
QT_MOC_LITERAL(17, 255, 7), // "request"
QT_MOC_LITERAL(18, 263, 4), // "echo"
QT_MOC_LITERAL(19, 268, 9), // "completed"
QT_MOC_LITERAL(20, 278, 19), // "gainedAuthorization"
QT_MOC_LITERAL(21, 298, 9), // "showError"
QT_MOC_LITERAL(22, 308, 4), // "text"
QT_MOC_LITERAL(23, 313, 14), // "dialogAccepted"
QT_MOC_LITERAL(24, 328, 14), // "dialogCanceled"
QT_MOC_LITERAL(25, 343, 12), // "userSelected"
QT_MOC_LITERAL(26, 356, 19), // "PolkitQt1::Identity"
QT_MOC_LITERAL(27, 376, 8) // "identity"

    },
    "PolkitListener\0initiateAuthentication\0"
    "\0actionId\0message\0iconName\0"
    "PolkitQt1::Details\0details\0cookie\0"
    "PolkitQt1::Identity::List\0identities\0"
    "PolkitQt1::Agent::AsyncResult*\0result\0"
    "initiateAuthenticationFinish\0"
    "cancelAuthentication\0tryAgain\0"
    "finishObtainPrivilege\0request\0echo\0"
    "completed\0gainedAuthorization\0showError\0"
    "text\0dialogAccepted\0dialogCanceled\0"
    "userSelected\0PolkitQt1::Identity\0"
    "identity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PolkitListener[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    7,   69,    2, 0x0a /* Public */,
      13,    0,   84,    2, 0x0a /* Public */,
      14,    0,   85,    2, 0x0a /* Public */,
      15,    0,   86,    2, 0x0a /* Public */,
      16,    0,   87,    2, 0x0a /* Public */,
      17,    2,   88,    2, 0x0a /* Public */,
      19,    1,   93,    2, 0x0a /* Public */,
      21,    1,   96,    2, 0x0a /* Public */,
      23,    0,   99,    2, 0x08 /* Private */,
      24,    0,  100,    2, 0x08 /* Private */,
      25,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 6, QMetaType::QString, 0x80000000 | 9, 0x80000000 | 11,    3,    4,    5,    7,    8,   10,   12,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   17,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,

       0        // eod
};

void PolkitListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PolkitListener *_t = static_cast<PolkitListener *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initiateAuthentication((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const PolkitQt1::Details(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const PolkitQt1::Identity::List(*)>(_a[6])),(*reinterpret_cast< PolkitQt1::Agent::AsyncResult*(*)>(_a[7]))); break;
        case 1: { bool _r = _t->initiateAuthenticationFinish();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->cancelAuthentication(); break;
        case 3: _t->tryAgain(); break;
        case 4: _t->finishObtainPrivilege(); break;
        case 5: _t->request((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->completed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->dialogAccepted(); break;
        case 9: _t->dialogCanceled(); break;
        case 10: _t->userSelected((*reinterpret_cast< PolkitQt1::Identity(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PolkitListener::staticMetaObject = {
    { &Listener::staticMetaObject, qt_meta_stringdata_PolkitListener.data,
      qt_meta_data_PolkitListener,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PolkitListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolkitListener::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PolkitListener.stringdata0))
        return static_cast<void*>(this);
    return Listener::qt_metacast(_clname);
}

int PolkitListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Listener::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
