/****************************************************************************
** Meta object code from reading C++ file 'DeviceView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/View/DeviceList/DeviceView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceView_t {
    QByteArrayData data[17];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceView_t qt_meta_stringdata_DeviceView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DeviceView"
QT_MOC_LITERAL(1, 11, 17), // "sgnGetDevicesList"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "sgnShowDeviceOperate"
QT_MOC_LITERAL(4, 51, 11), // "deviceIndex"
QT_MOC_LITERAL(5, 63, 7), // "sgnPlay"
QT_MOC_LITERAL(6, 71, 18), // "sgnShowLocalRecord"
QT_MOC_LITERAL(7, 90, 18), // "sgnShowCloudRecord"
QT_MOC_LITERAL(8, 109, 24), // "sgnShowAlarmMsgsListView"
QT_MOC_LITERAL(9, 134, 22), // "sgnDecryptShadeClicked"
QT_MOC_LITERAL(10, 157, 16), // "slotDeviceRemove"
QT_MOC_LITERAL(11, 174, 21), // "slotShowDeviceOperate"
QT_MOC_LITERAL(12, 196, 8), // "slotPlay"
QT_MOC_LITERAL(13, 205, 19), // "slotShowLocalRecord"
QT_MOC_LITERAL(14, 225, 19), // "slotShowCloudRecord"
QT_MOC_LITERAL(15, 245, 25), // "slotShowAlarmMsgsListView"
QT_MOC_LITERAL(16, 271, 23) // "slotDecryptShadeClicked"

    },
    "DeviceView\0sgnGetDevicesList\0\0"
    "sgnShowDeviceOperate\0deviceIndex\0"
    "sgnPlay\0sgnShowLocalRecord\0"
    "sgnShowCloudRecord\0sgnShowAlarmMsgsListView\0"
    "sgnDecryptShadeClicked\0slotDeviceRemove\0"
    "slotShowDeviceOperate\0slotPlay\0"
    "slotShowLocalRecord\0slotShowCloudRecord\0"
    "slotShowAlarmMsgsListView\0"
    "slotDecryptShadeClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    1,   85,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,
       6,    1,   91,    2, 0x06 /* Public */,
       7,    1,   94,    2, 0x06 /* Public */,
       8,    1,   97,    2, 0x06 /* Public */,
       9,    1,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DeviceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnGetDevicesList(); break;
        case 1: _t->sgnShowDeviceOperate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sgnPlay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sgnShowLocalRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sgnShowCloudRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sgnShowAlarmMsgsListView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sgnDecryptShadeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotDeviceRemove(); break;
        case 8: _t->slotShowDeviceOperate(); break;
        case 9: _t->slotPlay(); break;
        case 10: _t->slotShowLocalRecord(); break;
        case 11: _t->slotShowCloudRecord(); break;
        case 12: _t->slotShowAlarmMsgsListView(); break;
        case 13: _t->slotDecryptShadeClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnGetDevicesList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnShowDeviceOperate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnPlay)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnShowLocalRecord)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnShowCloudRecord)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnShowAlarmMsgsListView)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DeviceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnDecryptShadeClicked)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DeviceView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DeviceView.data,
    qt_meta_data_DeviceView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DeviceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void DeviceView::sgnGetDevicesList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceView::sgnShowDeviceOperate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeviceView::sgnPlay(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeviceView::sgnShowLocalRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeviceView::sgnShowCloudRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DeviceView::sgnShowAlarmMsgsListView(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DeviceView::sgnDecryptShadeClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
