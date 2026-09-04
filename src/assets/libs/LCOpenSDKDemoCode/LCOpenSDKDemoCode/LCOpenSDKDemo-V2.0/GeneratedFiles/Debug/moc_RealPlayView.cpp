/****************************************************************************
** Meta object code from reading C++ file 'RealPlayView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/View/VideoPlay/RealPlayView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RealPlayView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RealPlayView_t {
    QByteArrayData data[20];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RealPlayView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RealPlayView_t qt_meta_stringdata_RealPlayView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RealPlayView"
QT_MOC_LITERAL(1, 13, 22), // "sgnReturnToDevicesList"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 18), // "refreshDevicesList"
QT_MOC_LITERAL(4, 56, 18), // "slotBackBtnClicked"
QT_MOC_LITERAL(5, 75, 18), // "slotSnapBtnClicked"
QT_MOC_LITERAL(6, 94, 20), // "slotRecordBtnClicked"
QT_MOC_LITERAL(7, 115, 24), // "slotDefinitionBtnClicked"
QT_MOC_LITERAL(8, 140, 18), // "slotTalkBtnClicked"
QT_MOC_LITERAL(9, 159, 19), // "slotAudioBtnClicked"
QT_MOC_LITERAL(10, 179, 24), // "slotFullScreenBtnClicked"
QT_MOC_LITERAL(11, 204, 23), // "slotPlayerStatusChanged"
QT_MOC_LITERAL(12, 228, 6), // "status"
QT_MOC_LITERAL(13, 235, 25), // "slotRecorderStatusChanged"
QT_MOC_LITERAL(14, 261, 23), // "slotTalkerStatusChanged"
QT_MOC_LITERAL(15, 285, 16), // "slotPtzViewState"
QT_MOC_LITERAL(16, 302, 6), // "isShow"
QT_MOC_LITERAL(17, 309, 14), // "slotPtzControl"
QT_MOC_LITERAL(18, 324, 7), // "ptzCtrl"
QT_MOC_LITERAL(19, 332, 11) // "ptzCtrlType"

    },
    "RealPlayView\0sgnReturnToDevicesList\0"
    "\0refreshDevicesList\0slotBackBtnClicked\0"
    "slotSnapBtnClicked\0slotRecordBtnClicked\0"
    "slotDefinitionBtnClicked\0slotTalkBtnClicked\0"
    "slotAudioBtnClicked\0slotFullScreenBtnClicked\0"
    "slotPlayerStatusChanged\0status\0"
    "slotRecorderStatusChanged\0"
    "slotTalkerStatusChanged\0slotPtzViewState\0"
    "isShow\0slotPtzControl\0ptzCtrl\0ptzCtrlType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealPlayView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    1,   89,    2, 0x08 /* Private */,
      13,    1,   92,    2, 0x08 /* Private */,
      14,    1,   95,    2, 0x08 /* Private */,
      15,    1,   98,    2, 0x08 /* Private */,
      17,    2,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,

       0        // eod
};

void RealPlayView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RealPlayView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnReturnToDevicesList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotBackBtnClicked(); break;
        case 2: _t->slotSnapBtnClicked(); break;
        case 3: _t->slotRecordBtnClicked(); break;
        case 4: _t->slotDefinitionBtnClicked(); break;
        case 5: _t->slotTalkBtnClicked(); break;
        case 6: _t->slotAudioBtnClicked(); break;
        case 7: _t->slotFullScreenBtnClicked(); break;
        case 8: _t->slotPlayerStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotRecorderStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotTalkerStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotPtzViewState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->slotPtzControl((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RealPlayView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RealPlayView::sgnReturnToDevicesList)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RealPlayView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RealPlayView.data,
    qt_meta_data_RealPlayView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RealPlayView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealPlayView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RealPlayView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RealPlayView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void RealPlayView::sgnReturnToDevicesList(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
