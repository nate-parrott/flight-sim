/****************************************************************************
** Meta object code from reading C++ file 'qqmlwebsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../websockets/src/imports/qmlwebsockets/qqmlwebsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qqmlwebsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QQmlWebSocket_t {
    QByteArrayData data[26];
    char stringdata[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QQmlWebSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QQmlWebSocket_t qt_meta_stringdata_QQmlWebSocket = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 19),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 7),
QT_MOC_LITERAL(4, 43, 13),
QT_MOC_LITERAL(5, 57, 6),
QT_MOC_LITERAL(6, 64, 6),
QT_MOC_LITERAL(7, 71, 13),
QT_MOC_LITERAL(8, 85, 8),
QT_MOC_LITERAL(9, 94, 18),
QT_MOC_LITERAL(10, 113, 11),
QT_MOC_LITERAL(11, 125, 10),
QT_MOC_LITERAL(12, 136, 15),
QT_MOC_LITERAL(13, 152, 7),
QT_MOC_LITERAL(14, 160, 28),
QT_MOC_LITERAL(15, 189, 5),
QT_MOC_LITERAL(16, 195, 14),
QT_MOC_LITERAL(17, 210, 28),
QT_MOC_LITERAL(18, 239, 5),
QT_MOC_LITERAL(19, 245, 3),
QT_MOC_LITERAL(20, 249, 6),
QT_MOC_LITERAL(21, 256, 10),
QT_MOC_LITERAL(22, 267, 4),
QT_MOC_LITERAL(23, 272, 7),
QT_MOC_LITERAL(24, 280, 6),
QT_MOC_LITERAL(25, 287, 5)
    },
    "QQmlWebSocket\0textMessageReceived\0\0"
    "message\0statusChanged\0Status\0status\0"
    "activeChanged\0isActive\0errorStringChanged\0"
    "errorString\0urlChanged\0sendTextMessage\0"
    "onError\0QAbstractSocket::SocketError\0"
    "error\0onStateChanged\0QAbstractSocket::SocketState\0"
    "state\0url\0active\0Connecting\0Open\0"
    "Closing\0Closed\0Error\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QQmlWebSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   76, // properties
       1,   92, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06,
       4,    1,   57,    2, 0x06,
       7,    1,   60,    2, 0x06,
       9,    1,   63,    2, 0x06,
      11,    0,   66,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      12,    1,   67,    2, 0x0a,
      13,    1,   70,    2, 0x08,
      16,    1,   73,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

 // properties: name, type, flags
      19, QMetaType::QUrl, 0x00495103,
       6, 0x80000000 | 5, 0x00495009,
      10, QMetaType::QString, 0x00495001,
      20, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       4,
       1,
       3,
       2,

 // enums: name, flags, count, data
       5, 0x0,    5,   96,

 // enum data: key, value
      21, uint(QQmlWebSocket::Connecting),
      22, uint(QQmlWebSocket::Open),
      23, uint(QQmlWebSocket::Closing),
      24, uint(QQmlWebSocket::Closed),
      25, uint(QQmlWebSocket::Error),

       0        // eod
};

void QQmlWebSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QQmlWebSocket *_t = static_cast<QQmlWebSocket *>(_o);
        switch (_id) {
        case 0: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->statusChanged((*reinterpret_cast< Status(*)>(_a[1]))); break;
        case 2: _t->activeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->errorStringChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->urlChanged(); break;
        case 5: _t->sendTextMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: _t->onStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QQmlWebSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQmlWebSocket::textMessageReceived)) {
                *result = 0;
            }
        }
        {
            typedef void (QQmlWebSocket::*_t)(Status );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQmlWebSocket::statusChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (QQmlWebSocket::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQmlWebSocket::activeChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (QQmlWebSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQmlWebSocket::errorStringChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (QQmlWebSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQmlWebSocket::urlChanged)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject QQmlWebSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QQmlWebSocket.data,
      qt_meta_data_QQmlWebSocket,  qt_static_metacall, 0, 0}
};


const QMetaObject *QQmlWebSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QQmlWebSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QQmlWebSocket.stringdata))
        return static_cast<void*>(const_cast< QQmlWebSocket*>(this));
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(const_cast< QQmlWebSocket*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(const_cast< QQmlWebSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int QQmlWebSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = url(); break;
        case 1: *reinterpret_cast< Status*>(_v) = status(); break;
        case 2: *reinterpret_cast< QString*>(_v) = errorString(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isActive(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setUrl(*reinterpret_cast< QUrl*>(_v)); break;
        case 3: setActive(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QQmlWebSocket::textMessageReceived(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QQmlWebSocket::statusChanged(Status _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QQmlWebSocket::activeChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QQmlWebSocket::errorStringChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QQmlWebSocket::urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
