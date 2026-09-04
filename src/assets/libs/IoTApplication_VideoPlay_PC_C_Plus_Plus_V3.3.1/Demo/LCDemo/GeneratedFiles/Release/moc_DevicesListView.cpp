/****************************************************************************
** Meta object code from reading C++ file 'DevicesListView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/DeviceList/DevicesListView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DevicesListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DevicesListView_t {
    QByteArrayData data[25];
    char stringdata0[399];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DevicesListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DevicesListView_t qt_meta_stringdata_DevicesListView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DevicesListView"
QT_MOC_LITERAL(1, 16, 16), // "sgnReturnToLogin"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "sgnShowAddDevice"
QT_MOC_LITERAL(4, 51, 20), // "sgnShowDeviceOperate"
QT_MOC_LITERAL(5, 72, 11), // "deviceIndex"
QT_MOC_LITERAL(6, 84, 16), // "sgnGetChannelPic"
QT_MOC_LITERAL(7, 101, 7), // "sgnPlay"
QT_MOC_LITERAL(8, 109, 18), // "sgnShowLocalRecord"
QT_MOC_LITERAL(9, 128, 18), // "sgnShowCloudRecord"
QT_MOC_LITERAL(10, 147, 18), // "slotGetDevicesList"
QT_MOC_LITERAL(11, 166, 17), // "slotReturnToLogin"
QT_MOC_LITERAL(12, 184, 17), // "slotShowAddDevice"
QT_MOC_LITERAL(13, 202, 21), // "slotShowDeviceOperate"
QT_MOC_LITERAL(14, 224, 25), // "slotGetChannelPicFinished"
QT_MOC_LITERAL(15, 250, 6), // "pixmap"
QT_MOC_LITERAL(16, 257, 8), // "slotPlay"
QT_MOC_LITERAL(17, 266, 19), // "slotShowLocalRecord"
QT_MOC_LITERAL(18, 286, 19), // "slotShowCloudRecord"
QT_MOC_LITERAL(19, 306, 16), // "slotHandleResult"
QT_MOC_LITERAL(20, 323, 6), // "result"
QT_MOC_LITERAL(21, 330, 21), // "slotShowDecryptKeyBox"
QT_MOC_LITERAL(22, 352, 15), // "decryptKeyIndex"
QT_MOC_LITERAL(23, 368, 19), // "slotDecryptKeyBoxOK"
QT_MOC_LITERAL(24, 388, 10) // "decryptKey"

    },
    "DevicesListView\0sgnReturnToLogin\0\0"
    "sgnShowAddDevice\0sgnShowDeviceOperate\0"
    "deviceIndex\0sgnGetChannelPic\0sgnPlay\0"
    "sgnShowLocalRecord\0sgnShowCloudRecord\0"
    "slotGetDevicesList\0slotReturnToLogin\0"
    "slotShowAddDevice\0slotShowDeviceOperate\0"
    "slotGetChannelPicFinished\0pixmap\0"
    "slotPlay\0slotShowLocalRecord\0"
    "slotShowCloudRecord\0slotHandleResult\0"
    "result\0slotShowDecryptKeyBox\0"
    "decryptKeyIndex\0slotDecryptKeyBoxOK\0"
    "decryptKey"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DevicesListView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       4,    1,  106,    2, 0x06 /* Public */,
       6,    1,  109,    2, 0x06 /* Public */,
       7,    1,  112,    2, 0x06 /* Public */,
       8,    1,  115,    2, 0x06 /* Public */,
       9,    1,  118,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  121,    2, 0x08 /* Private */,
      11,    0,  122,    2, 0x08 /* Private */,
      12,    0,  123,    2, 0x08 /* Private */,
      13,    1,  124,    2, 0x08 /* Private */,
      14,    2,  127,    2, 0x08 /* Private */,
      16,    1,  132,    2, 0x08 /* Private */,
      17,    1,  135,    2, 0x08 /* Private */,
      18,    1,  138,    2, 0x08 /* Private */,
      19,    1,  141,    2, 0x08 /* Private */,
      21,    1,  144,    2, 0x08 /* Private */,
      23,    1,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QPixmap,    5,   15,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::QString,   24,

       0        // eod
};

void DevicesListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DevicesListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnReturnToLogin(); break;
        case 1: _t->sgnShowAddDevice(); break;
        case 2: _t->sgnShowDeviceOperate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sgnGetChannelPic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sgnPlay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sgnShowLocalRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sgnShowCloudRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotGetDevicesList(); break;
        case 8: _t->slotReturnToLogin(); break;
        case 9: _t->slotShowAddDevice(); break;
        case 10: _t->slotShowDeviceOperate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotGetChannelPicFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2]))); break;
        case 12: _t->slotPlay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slotShowLocalRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slotShowCloudRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slotHandleResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slotShowDecryptKeyBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->slotDecryptKeyBoxOK((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DevicesListView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnReturnToLogin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnShowAddDevice)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnShowDeviceOperate)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnGetChannelPic)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnPlay)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnShowLocalRecord)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DevicesListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevicesListView::sgnShowCloudRecord)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DevicesListView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DevicesListView.data,
    qt_meta_data_DevicesListView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DevicesListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DevicesListView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DevicesListView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DevicesListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void DevicesListView::sgnReturnToLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DevicesListView::sgnShowAddDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DevicesListView::sgnShowDeviceOperate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DevicesListView::sgnGetChannelPic(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DevicesListView::sgnPlay(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DevicesListView::sgnShowLocalRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DevicesListView::sgnShowCloudRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
