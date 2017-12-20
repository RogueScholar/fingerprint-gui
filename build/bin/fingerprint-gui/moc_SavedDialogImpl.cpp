/****************************************************************************
** Meta object code from reading C++ file 'SavedDialogImpl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/SavedDialogImpl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SavedDialogImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SavedDialogImpl_t {
    QByteArrayData data[6];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SavedDialogImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SavedDialogImpl_t qt_meta_stringdata_SavedDialogImpl = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SavedDialogImpl"
QT_MOC_LITERAL(1, 16, 6), // "choice"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "savedDialogChoice"
QT_MOC_LITERAL(4, 42, 9), // "yesChoice"
QT_MOC_LITERAL(5, 52, 8) // "noChoice"

    },
    "SavedDialogImpl\0choice\0\0savedDialogChoice\0"
    "yesChoice\0noChoice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SavedDialogImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SavedDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SavedDialogImpl *_t = static_cast<SavedDialogImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choice((*reinterpret_cast< savedDialogChoice(*)>(_a[1]))); break;
        case 1: _t->yesChoice(); break;
        case 2: _t->noChoice(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SavedDialogImpl::*_t)(savedDialogChoice );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SavedDialogImpl::choice)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SavedDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SavedDialogImpl.data,
      qt_meta_data_SavedDialogImpl,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SavedDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SavedDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SavedDialogImpl.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::SavedDialog"))
        return static_cast< Ui::SavedDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int SavedDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SavedDialogImpl::choice(savedDialogChoice _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
