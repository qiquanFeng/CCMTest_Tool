/****************************************************************************
** Meta object code from reading C++ file 'dtccmtest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dtccmtest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dtccmtest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dtCCMTest_t {
    QByteArrayData data[8];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dtCCMTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dtCCMTest_t qt_meta_stringdata_dtCCMTest = {
    {
QT_MOC_LITERAL(0, 0, 9), // "dtCCMTest"
QT_MOC_LITERAL(1, 10, 10), // "sgl_addLog"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 18), // "slot_connectStatus"
QT_MOC_LITERAL(4, 41, 15), // "slot_showConfig"
QT_MOC_LITERAL(5, 57, 12), // "slot_butPlay"
QT_MOC_LITERAL(6, 70, 20), // "slot_butSelectConfig"
QT_MOC_LITERAL(7, 91, 21) // "slot_butNewConfig_Add"

    },
    "dtCCMTest\0sgl_addLog\0\0slot_connectStatus\0"
    "slot_showConfig\0slot_butPlay\0"
    "slot_butSelectConfig\0slot_butNewConfig_Add"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dtCCMTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       1,    1,   54,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   57,    2, 0x0a /* Public */,
       4,    0,   60,    2, 0x0a /* Public */,
       5,    0,   61,    2, 0x0a /* Public */,
       6,    0,   62,    2, 0x0a /* Public */,
       7,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QColor,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dtCCMTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dtCCMTest *_t = static_cast<dtCCMTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgl_addLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 1: _t->sgl_addLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slot_connectStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_showConfig(); break;
        case 4: _t->slot_butPlay(); break;
        case 5: _t->slot_butSelectConfig(); break;
        case 6: _t->slot_butNewConfig_Add(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (dtCCMTest::*_t)(QString , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&dtCCMTest::sgl_addLog)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject dtCCMTest::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dtCCMTest.data,
      qt_meta_data_dtCCMTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *dtCCMTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dtCCMTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_dtCCMTest.stringdata0))
        return static_cast<void*>(const_cast< dtCCMTest*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dtCCMTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void dtCCMTest::sgl_addLog(QString _t1, QColor _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
