/****************************************************************************
** Meta object code from reading C++ file 'pdf_demo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pdf_demo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdf_demo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PDF_Demo_t {
    QByteArrayData data[7];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PDF_Demo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PDF_Demo_t qt_meta_stringdata_PDF_Demo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PDF_Demo"
QT_MOC_LITERAL(1, 9, 19), // "slot_LoadLeftImgage"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "slot_LoadRightImgage"
QT_MOC_LITERAL(4, 51, 16), // "slot_calibration"
QT_MOC_LITERAL(5, 68, 14), // "slot_showImage"
QT_MOC_LITERAL(6, 83, 9) // "slot_test"

    },
    "PDF_Demo\0slot_LoadLeftImgage\0\0"
    "slot_LoadRightImgage\0slot_calibration\0"
    "slot_showImage\0slot_test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PDF_Demo[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       3,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    2,   48,    2, 0x0a /* Public */,
       6,    2,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void PDF_Demo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PDF_Demo *_t = static_cast<PDF_Demo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_LoadLeftImgage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_LoadRightImgage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_calibration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_showImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_test((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject PDF_Demo::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PDF_Demo.data,
      qt_meta_data_PDF_Demo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PDF_Demo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PDF_Demo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PDF_Demo.stringdata0))
        return static_cast<void*>(const_cast< PDF_Demo*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PDF_Demo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
