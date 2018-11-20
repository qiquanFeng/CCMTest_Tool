/****************************************************************************
** Meta object code from reading C++ file 'ccmviewcontrols.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ccmviewcontrols.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccmviewcontrols.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCMLogBar_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCMLogBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCMLogBar_t qt_meta_stringdata_CCMLogBar = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CCMLogBar"
QT_MOC_LITERAL(1, 10, 11), // "slot_addLog"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "CCMLogBar\0slot_addLog\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCMLogBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QColor,    2,    2,

       0        // eod
};

void CCMLogBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCMLogBar *_t = static_cast<CCMLogBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_addLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CCMLogBar::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_CCMLogBar.data,
      qt_meta_data_CCMLogBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CCMLogBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCMLogBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CCMLogBar.stringdata0))
        return static_cast<void*>(const_cast< CCMLogBar*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int CCMLogBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_CCMViewBar_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCMViewBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCMViewBar_t qt_meta_stringdata_CCMViewBar = {
    {
QT_MOC_LITERAL(0, 0, 10) // "CCMViewBar"

    },
    "CCMViewBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCMViewBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CCMViewBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CCMViewBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CCMViewBar.data,
      qt_meta_data_CCMViewBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CCMViewBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCMViewBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CCMViewBar.stringdata0))
        return static_cast<void*>(const_cast< CCMViewBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int CCMViewBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CCMConnectStatusBar_t {
    QByteArrayData data[3];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCMConnectStatusBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCMConnectStatusBar_t qt_meta_stringdata_CCMConnectStatusBar = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CCMConnectStatusBar"
QT_MOC_LITERAL(1, 20, 16), // "sig_statuschange"
QT_MOC_LITERAL(2, 37, 0) // ""

    },
    "CCMConnectStatusBar\0sig_statuschange\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCMConnectStatusBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CCMConnectStatusBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCMConnectStatusBar *_t = static_cast<CCMConnectStatusBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_statuschange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CCMConnectStatusBar::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CCMConnectStatusBar::sig_statuschange)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CCMConnectStatusBar::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CCMConnectStatusBar.data,
      qt_meta_data_CCMConnectStatusBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CCMConnectStatusBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCMConnectStatusBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CCMConnectStatusBar.stringdata0))
        return static_cast<void*>(const_cast< CCMConnectStatusBar*>(this));
    return QThread::qt_metacast(_clname);
}

int CCMConnectStatusBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CCMConnectStatusBar::sig_statuschange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
