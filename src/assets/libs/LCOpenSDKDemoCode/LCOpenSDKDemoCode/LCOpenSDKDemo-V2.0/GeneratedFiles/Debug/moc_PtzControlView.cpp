/****************************************************************************
** Meta object code from reading C++ file 'PtzControlView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/View/VideoPlay/PtzControlView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PtzControlView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PtzControlView_t {
    QByteArrayData data[25];
    char stringdata0[442];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PtzControlView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PtzControlView_t qt_meta_stringdata_PtzControlView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PtzControlView"
QT_MOC_LITERAL(1, 15, 12), // "sgnShowWhole"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "isWhole"
QT_MOC_LITERAL(4, 37, 13), // "sgnPtzControl"
QT_MOC_LITERAL(5, 51, 7), // "ptzCtrl"
QT_MOC_LITERAL(6, 59, 11), // "ptzCtrlType"
QT_MOC_LITERAL(7, 71, 16), // "slotArrowClicked"
QT_MOC_LITERAL(8, 88, 16), // "slotPtzUpClicked"
QT_MOC_LITERAL(9, 105, 18), // "slotPtzLeftClicked"
QT_MOC_LITERAL(10, 124, 18), // "slotPtzDownClicked"
QT_MOC_LITERAL(11, 143, 19), // "slotPtzRightClicked"
QT_MOC_LITERAL(12, 163, 20), // "slotPtzLeftUpClicked"
QT_MOC_LITERAL(13, 184, 22), // "slotPtzLeftDownClicked"
QT_MOC_LITERAL(14, 207, 21), // "slotPtzRightUpClicked"
QT_MOC_LITERAL(15, 229, 23), // "slotPtzRightDownClicked"
QT_MOC_LITERAL(16, 253, 18), // "slotPtzUpLongPress"
QT_MOC_LITERAL(17, 272, 7), // "isPress"
QT_MOC_LITERAL(18, 280, 20), // "slotPtzLeftLongPress"
QT_MOC_LITERAL(19, 301, 20), // "slotPtzDownLongPress"
QT_MOC_LITERAL(20, 322, 21), // "slotPtzRightLongPress"
QT_MOC_LITERAL(21, 344, 22), // "slotPtzLeftUpLongPress"
QT_MOC_LITERAL(22, 367, 24), // "slotPtzLeftDownLongPress"
QT_MOC_LITERAL(23, 392, 23), // "slotPtzRightUpLongPress"
QT_MOC_LITERAL(24, 416, 25) // "slotPtzRightDownLongPress"

    },
    "PtzControlView\0sgnShowWhole\0\0isWhole\0"
    "sgnPtzControl\0ptzCtrl\0ptzCtrlType\0"
    "slotArrowClicked\0slotPtzUpClicked\0"
    "slotPtzLeftClicked\0slotPtzDownClicked\0"
    "slotPtzRightClicked\0slotPtzLeftUpClicked\0"
    "slotPtzLeftDownClicked\0slotPtzRightUpClicked\0"
    "slotPtzRightDownClicked\0slotPtzUpLongPress\0"
    "isPress\0slotPtzLeftLongPress\0"
    "slotPtzDownLongPress\0slotPtzRightLongPress\0"
    "slotPtzLeftUpLongPress\0slotPtzLeftDownLongPress\0"
    "slotPtzRightUpLongPress\0"
    "slotPtzRightDownLongPress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PtzControlView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    2,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  117,    2, 0x08 /* Private */,
       8,    0,  118,    2, 0x08 /* Private */,
       9,    0,  119,    2, 0x08 /* Private */,
      10,    0,  120,    2, 0x08 /* Private */,
      11,    0,  121,    2, 0x08 /* Private */,
      12,    0,  122,    2, 0x08 /* Private */,
      13,    0,  123,    2, 0x08 /* Private */,
      14,    0,  124,    2, 0x08 /* Private */,
      15,    0,  125,    2, 0x08 /* Private */,
      16,    1,  126,    2, 0x08 /* Private */,
      18,    1,  129,    2, 0x08 /* Private */,
      19,    1,  132,    2, 0x08 /* Private */,
      20,    1,  135,    2, 0x08 /* Private */,
      21,    1,  138,    2, 0x08 /* Private */,
      22,    1,  141,    2, 0x08 /* Private */,
      23,    1,  144,    2, 0x08 /* Private */,
      24,    1,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   17,

       0        // eod
};

void PtzControlView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PtzControlView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnShowWhole((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sgnPtzControl((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotArrowClicked(); break;
        case 3: _t->slotPtzUpClicked(); break;
        case 4: _t->slotPtzLeftClicked(); break;
        case 5: _t->slotPtzDownClicked(); break;
        case 6: _t->slotPtzRightClicked(); break;
        case 7: _t->slotPtzLeftUpClicked(); break;
        case 8: _t->slotPtzLeftDownClicked(); break;
        case 9: _t->slotPtzRightUpClicked(); break;
        case 10: _t->slotPtzRightDownClicked(); break;
        case 11: _t->slotPtzUpLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->slotPtzLeftLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->slotPtzDownLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->slotPtzRightLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->slotPtzLeftUpLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->slotPtzLeftDownLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->slotPtzRightUpLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->slotPtzRightDownLongPress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PtzControlView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PtzControlView::sgnShowWhole)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PtzControlView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PtzControlView::sgnPtzControl)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PtzControlView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PtzControlView.data,
    qt_meta_data_PtzControlView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PtzControlView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PtzControlView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PtzControlView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PtzControlView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void PtzControlView::sgnShowWhole(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PtzControlView::sgnPtzControl(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
