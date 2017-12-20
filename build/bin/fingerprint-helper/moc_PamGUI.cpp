/****************************************************************************
** Meta object code from reading C++ file 'PamGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/PamGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PamGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PamGUI_t {
    QByteArrayData data[9];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PamGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PamGUI_t qt_meta_stringdata_PamGUI = {
    {
QT_MOC_LITERAL(0, 0, 6), // "PamGUI"
QT_MOC_LITERAL(1, 7, 9), // "timerTick"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "matchResult"
QT_MOC_LITERAL(4, 30, 5), // "match"
QT_MOC_LITERAL(5, 36, 12), // "fp_pic_data*"
QT_MOC_LITERAL(6, 49, 3), // "pic"
QT_MOC_LITERAL(7, 53, 15), // "newVerifyResult"
QT_MOC_LITERAL(8, 69, 6) // "result"

    },
    "PamGUI\0timerTick\0\0matchResult\0match\0"
    "fp_pic_data*\0pic\0newVerifyResult\0"
    "result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PamGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    2,   30,    2, 0x0a /* Public */,
       7,    2,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    8,    6,

       0        // eod
};

void PamGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PamGUI *_t = static_cast<PamGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timerTick(); break;
        case 1: _t->matchResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 2: _t->newVerifyResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject PamGUI::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PamGUI.data,
      qt_meta_data_PamGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PamGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PamGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PamGUI.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::MainFrame"))
        return static_cast< Ui::MainFrame*>(this);
    return QFrame::qt_metacast(_clname);
}

int PamGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
