/****************************************************************************
** Meta object code from reading C++ file 'IdentifierGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/IdentifierGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IdentifierGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IdentifierGUI_t {
    QByteArrayData data[14];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IdentifierGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IdentifierGUI_t qt_meta_stringdata_IdentifierGUI = {
    {
QT_MOC_LITERAL(0, 0, 13), // "IdentifierGUI"
QT_MOC_LITERAL(1, 14, 11), // "matchResult"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "match"
QT_MOC_LITERAL(4, 33, 12), // "fp_pic_data*"
QT_MOC_LITERAL(5, 46, 3), // "pic"
QT_MOC_LITERAL(6, 50, 15), // "newVerifyResult"
QT_MOC_LITERAL(7, 66, 6), // "result"
QT_MOC_LITERAL(8, 73, 9), // "timerTick"
QT_MOC_LITERAL(9, 83, 13), // "keyPressEvent"
QT_MOC_LITERAL(10, 97, 10), // "QKeyEvent*"
QT_MOC_LITERAL(11, 108, 1), // "e"
QT_MOC_LITERAL(12, 110, 10), // "closeEvent"
QT_MOC_LITERAL(13, 121, 12) // "QCloseEvent*"

    },
    "IdentifierGUI\0matchResult\0\0match\0"
    "fp_pic_data*\0pic\0newVerifyResult\0"
    "result\0timerTick\0keyPressEvent\0"
    "QKeyEvent*\0e\0closeEvent\0QCloseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IdentifierGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x0a /* Public */,
       6,    2,   44,    2, 0x0a /* Public */,
       8,    0,   49,    2, 0x0a /* Public */,
       9,    1,   50,    2, 0x0a /* Public */,
      12,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    7,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   11,

       0        // eod
};

void IdentifierGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IdentifierGUI *_t = static_cast<IdentifierGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->matchResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 1: _t->newVerifyResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< fp_pic_data*(*)>(_a[2]))); break;
        case 2: _t->timerTick(); break;
        case 3: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject IdentifierGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IdentifierGUI.data,
      qt_meta_data_IdentifierGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IdentifierGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IdentifierGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IdentifierGUI.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::IdentifierWindow"))
        return static_cast< Ui::IdentifierWindow*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int IdentifierGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
