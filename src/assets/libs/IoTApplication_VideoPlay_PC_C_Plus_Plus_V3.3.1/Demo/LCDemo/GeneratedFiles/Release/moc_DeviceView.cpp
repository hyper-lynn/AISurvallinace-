/****************************************************************************
** Meta object code from reading C++ file 'DeviceView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/DeviceList/DeviceView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceView_t {
    QByteArrayData data[15];
    char stringdata0[244];
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
QT_MOC_LITERAL(8, 109, 22), // "sgnDecryptShadeClicked"
QT_MOC_LITERAL(9, 132, 16), // "slotDeviceRemove"
QT_MOC_LITERAL(10, 149, 21), // "slotShowDeviceOperate"
QT_MOC_LITERAL(11, 171, 8), // "slotPlay"
QT_MOC_LITERAL(12, 180, 19), // "slotShowLocalRecord"
QT_MOC_LITERAL(13, 200, 19), // "slotShowCloudRecord"
QT_MOC_LITERAL(14, 220, 23) // "slotDecryptShadeClicked"

    },
    "DeviceView\0sgnGetDevicesList\0\0"
    "sgnShowDeviceOperate\0deviceIndex\0"
    "sgnPlay\0sgnShowLocalRecord\0"
    "sgnShowCloudRecord\0sgnDecryptShadeClicked\0"
    "slotDeviceRemove\0slotShowDeviceOperate\0"
    "slotPlay\0slotShowLocalRecord\0"
    "slotShowCloudRecord\0slotDecryptShadeClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    1,   78,    2, 0x06 /* Public */,
       6,    1,   81,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   90,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
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
        case 5: _t->sgnDecryptShadeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotDeviceRemove(); break;
        case 7: _t->slotShowDeviceOperate(); break;
        case 8: _t->slotPlay(); break;
        case 9: _t->slotShowLocalRecord(); break;
        case 10: _t->slotShowCloudRecord(); break;
        case 11: _t->slotDecryptShadeClicked(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceView::sgnDecryptShadeClicked)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DeviceView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
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
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeviceView::sgnPlay(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeviceView::sgnShowLocalRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeviceView::sgnShowCloudRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DeviceView::sgnDecryptShadeClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
