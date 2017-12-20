/****************************************************************************
** Meta object code from reading C++ file 'ExistDialogImpl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/ExistDialogImpl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExistDialogImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExistDialogImpl_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExistDialogImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExistDialogImpl_t qt_meta_stringdata_ExistDialogImpl = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ExistDialogImpl"
QT_MOC_LITERAL(1, 16, 6), // "choice"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "existDialogChoice"
QT_MOC_LITERAL(4, 42, 12), // "cancelChoice"
QT_MOC_LITERAL(5, 55, 12), // "verifyChoice"
QT_MOC_LITERAL(6, 68, 13) // "acquireChoice"

    },
    "ExistDialogImpl\0choice\0\0existDialogChoice\0"
    "cancelChoice\0verifyChoice\0acquireChoice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExistDialogImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExistDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExistDialogImpl *_t = static_cast<ExistDialogImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choice((*reinterpret_cast< existDialogChoice(*)>(_a[1]))); break;
        case 1: _t->cancelChoice(); break;
        case 2: _t->verifyChoice(); break;
        case 3: _t->acquireChoice(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ExistDialogImpl::*_t)(existDialogChoice );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ExistDialogImpl::choice)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ExistDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ExistDialogImpl.data,
      qt_meta_data_ExistDialogImpl,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ExistDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExistDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExistDialogImpl.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::ExistDialog"))
        return static_cast< Ui::ExistDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int ExistDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void ExistDialogImpl::choice(existDialogChoice _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
