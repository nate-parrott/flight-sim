/****************************************************************************
** Meta object code from reading C++ file 'qwebsocketserver_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../websockets/src/websockets/qwebsocketserver_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwebsocketserver_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QWebSocketServerPrivate_t {
    QByteArrayData data[5];
    char stringdata[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QWebSocketServerPrivate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QWebSocketServerPrivate_t qt_meta_stringdata_QWebSocketServerPrivate = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 15),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 17),
QT_MOC_LITERAL(4, 59, 17)
    },
    "QWebSocketServerPrivate\0onNewConnection\0"
    "\0onCloseConnection\0handshakeReceived\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWebSocketServerPrivate[] = {

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
       1,    0,   29,    2, 0x08,
       3,    0,   30,    2, 0x08,
       4,    0,   31,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QWebSocketServerPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QWebSocketServerPrivate *_t = static_cast<QWebSocketServerPrivate *>(_o);
        switch (_id) {
        case 0: _t->onNewConnection(); break;
        case 1: _t->onCloseConnection(); break;
        case 2: _t->handshakeReceived(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QWebSocketServerPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QWebSocketServerPrivate.data,
      qt_meta_data_QWebSocketServerPrivate,  qt_static_metacall, 0, 0}
};


const QMetaObject *QWebSocketServerPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWebSocketServerPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QWebSocketServerPrivate.stringdata))
        return static_cast<void*>(const_cast< QWebSocketServerPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QWebSocketServerPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
