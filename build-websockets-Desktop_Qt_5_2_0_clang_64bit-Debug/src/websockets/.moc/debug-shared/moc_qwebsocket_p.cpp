/****************************************************************************
** Meta object code from reading C++ file 'qwebsocket_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../websockets/src/websockets/qwebsocket_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwebsocket_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QWebSocketPrivate_t {
    QByteArrayData data[24];
    char stringdata[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QWebSocketPrivate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QWebSocketPrivate_t qt_meta_stringdata_QWebSocketPrivate = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 5),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 29),
QT_MOC_LITERAL(4, 55, 9),
QT_MOC_LITERAL(5, 65, 6),
QT_MOC_LITERAL(6, 72, 4),
QT_MOC_LITERAL(7, 77, 3),
QT_MOC_LITERAL(8, 81, 4),
QT_MOC_LITERAL(9, 86, 4),
QT_MOC_LITERAL(10, 91, 7),
QT_MOC_LITERAL(11, 99, 15),
QT_MOC_LITERAL(12, 115, 11),
QT_MOC_LITERAL(13, 127, 11),
QT_MOC_LITERAL(14, 139, 4),
QT_MOC_LITERAL(15, 144, 11),
QT_MOC_LITERAL(16, 156, 12),
QT_MOC_LITERAL(17, 169, 11),
QT_MOC_LITERAL(18, 181, 16),
QT_MOC_LITERAL(19, 198, 11),
QT_MOC_LITERAL(20, 210, 7),
QT_MOC_LITERAL(21, 218, 19),
QT_MOC_LITERAL(22, 238, 28),
QT_MOC_LITERAL(23, 267, 11)
    },
    "QWebSocketPrivate\0close\0\0"
    "QWebSocketProtocol::CloseCode\0closeCode\0"
    "reason\0open\0url\0mask\0ping\0payload\0"
    "ignoreSslErrors\0processData\0processPing\0"
    "data\0processPong\0processClose\0closeReason\0"
    "processHandshake\0QTcpSocket*\0pSocket\0"
    "processStateChanged\0QAbstractSocket::SocketState\0"
    "socketState\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWebSocketPrivate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x0a,
       6,    2,   69,    2, 0x0a,
       9,    1,   74,    2, 0x0a,
      11,    0,   77,    2, 0x0a,
      12,    0,   78,    2, 0x08,
      13,    1,   79,    2, 0x08,
      15,    1,   82,    2, 0x08,
      16,    2,   85,    2, 0x08,
      18,    1,   90,    2, 0x08,
      21,    1,   93,    2, 0x08,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QUrl, QMetaType::Bool,    7,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void QWebSocketPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QWebSocketPrivate *_t = static_cast<QWebSocketPrivate *>(_o);
        switch (_id) {
        case 0: _t->close((*reinterpret_cast< QWebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->ping((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->ignoreSslErrors(); break;
        case 4: _t->processData(); break;
        case 5: _t->processPing((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->processPong((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->processClose((*reinterpret_cast< QWebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->processHandshake((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 9: _t->processStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

const QMetaObject QWebSocketPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QWebSocketPrivate.data,
      qt_meta_data_QWebSocketPrivate,  qt_static_metacall, 0, 0}
};


const QMetaObject *QWebSocketPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWebSocketPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QWebSocketPrivate.stringdata))
        return static_cast<void*>(const_cast< QWebSocketPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int QWebSocketPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
