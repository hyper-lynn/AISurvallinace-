/****************************************************************************
** Meta object code from reading C++ file 'SearchDeviceBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/Utils/CommonView/SearchDeviceBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchDeviceBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchDeviceBar_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchDeviceBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchDeviceBar_t qt_meta_stringdata_SearchDeviceBar = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SearchDeviceBar"
QT_MOC_LITERAL(1, 16, 10), // "sgnFocusIn"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "sgnFocusOut"
QT_MOC_LITERAL(4, 40, 15), // "sgnSearchDevice"
QT_MOC_LITERAL(5, 56, 8), // "deviceID"
QT_MOC_LITERAL(6, 65, 16) // "slotSearchDevice"

    },
    "SearchDeviceBar\0sgnFocusIn\0\0sgnFocusOut\0"
    "sgnSearchDevice\0deviceID\0slotSearchDevice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchDeviceBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SearchDeviceBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchDeviceBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnFocusIn(); break;
        case 1: _t->sgnFocusOut(); break;
        case 2: _t->sgnSearchDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotSearchDevice(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchDeviceBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDeviceBar::sgnFocusIn)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchDeviceBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDeviceBar::sgnFocusOut)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchDeviceBar::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDeviceBar::sgnSearchDevice)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SearchDeviceBar::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SearchDeviceBar.data,
    qt_meta_data_SearchDeviceBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SearchDeviceBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchDeviceBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchDeviceBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SearchDeviceBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SearchDeviceBar::sgnFocusIn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SearchDeviceBar::sgnFocusOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SearchDeviceBar::sgnSearchDevice(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
