/****************************************************************************
** Meta object code from reading C++ file 'Network.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/Network/Network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Common__Network_t {
    QByteArrayData data[10];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Common__Network_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Common__Network_t qt_meta_stringdata_Common__Network = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Common::Network"
QT_MOC_LITERAL(1, 16, 16), // "onNetWorkTimeOut"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "onSSLErrors"
QT_MOC_LITERAL(4, 46, 16), // "QList<QSslError>"
QT_MOC_LITERAL(5, 63, 6), // "errors"
QT_MOC_LITERAL(6, 70, 11), // "onReadyRead"
QT_MOC_LITERAL(7, 82, 10), // "onFinished"
QT_MOC_LITERAL(8, 93, 7), // "onError"
QT_MOC_LITERAL(9, 101, 27) // "QNetworkReply::NetworkError"

    },
    "Common::Network\0onNetWorkTimeOut\0\0"
    "onSSLErrors\0QList<QSslError>\0errors\0"
    "onReadyRead\0onFinished\0onError\0"
    "QNetworkReply::NetworkError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Common__Network[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x09 /* Protected */,
       3,    1,   40,    2, 0x09 /* Protected */,
       6,    0,   43,    2, 0x09 /* Protected */,
       7,    0,   44,    2, 0x09 /* Protected */,
       8,    1,   45,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void Common::Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNetWorkTimeOut(); break;
        case 1: _t->onSSLErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 2: _t->onReadyRead(); break;
        case 3: _t->onFinished(); break;
        case 4: _t->onError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Common::Network::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Common__Network.data,
    qt_meta_data_Common__Network,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Common::Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Common::Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Common__Network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Common::Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
