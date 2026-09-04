/****************************************************************************
** Meta object code from reading C++ file 'DevicesListCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/Ctrl/DevicesListCtrl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DevicesListCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DevicesListCtrl_t {
    QByteArrayData data[10];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DevicesListCtrl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DevicesListCtrl_t qt_meta_stringdata_DevicesListCtrl = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DevicesListCtrl"
QT_MOC_LITERAL(1, 16, 24), // "sgnGetChannelPicFinished"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 11), // "deviceIndex"
QT_MOC_LITERAL(4, 54, 6), // "pixmap"
QT_MOC_LITERAL(5, 61, 17), // "slotGetChannelPic"
QT_MOC_LITERAL(6, 79, 24), // "slotCurlDownloadFinished"
QT_MOC_LITERAL(7, 104, 14), // "unsigned char*"
QT_MOC_LITERAL(8, 119, 4), // "data"
QT_MOC_LITERAL(9, 124, 7) // "dataLen"

    },
    "DevicesListCtrl\0sgnGetChannelPicFinished\0"
    "\0deviceIndex\0pixmap\0slotGetChannelPic\0"
    "slotCurlDownloadFinished\0unsigned char*\0"
    "data\0dataLen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DevicesListCtrl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   34,    2, 0x08 /* Private */,
       6,    2,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QPixmap,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 7, QMetaType::UInt,    8,    9,

       0        // eod
};

void DevicesListCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DevicesListCtrl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnGetChannelPicFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2]))); break;
        case 1: _t->slotGetChannelPic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotCurlDownloadFinished((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DevicesListCtrl::*)(int , QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListCtrl::sgnGetChannelPicFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DevicesListCtrl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DevicesListCtrl.data,
    qt_meta_data_DevicesListCtrl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DevicesListCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DevicesListCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DevicesListCtrl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DevicesListCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void DevicesListCtrl::sgnGetChannelPicFinished(int _t1, QPixmap _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
