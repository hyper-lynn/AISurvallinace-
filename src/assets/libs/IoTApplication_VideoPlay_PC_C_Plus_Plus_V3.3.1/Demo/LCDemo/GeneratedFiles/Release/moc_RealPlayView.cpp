/****************************************************************************
** Meta object code from reading C++ file 'RealPlayView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/VideoPlay/RealPlayView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RealPlayView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SleepOverlay_t {
    QByteArrayData data[3];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SleepOverlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SleepOverlay_t qt_meta_stringdata_SleepOverlay = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SleepOverlay"
QT_MOC_LITERAL(1, 13, 7), // "clicked"
QT_MOC_LITERAL(2, 21, 0) // ""

    },
    "SleepOverlay\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SleepOverlay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void SleepOverlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SleepOverlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SleepOverlay::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SleepOverlay::clicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SleepOverlay::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SleepOverlay.data,
    qt_meta_data_SleepOverlay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SleepOverlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SleepOverlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SleepOverlay.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SleepOverlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SleepOverlay::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_RealPlayView_t {
    QByteArrayData data[27];
    char stringdata0[464];
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
QT_MOC_LITERAL(19, 332, 11), // "ptzCtrlType"
QT_MOC_LITERAL(20, 344, 21), // "slotStreamModeChanged"
QT_MOC_LITERAL(21, 366, 4), // "mode"
QT_MOC_LITERAL(22, 371, 18), // "slotSleepCountdown"
QT_MOC_LITERAL(23, 390, 7), // "seconds"
QT_MOC_LITERAL(24, 398, 22), // "slotSleepCountdownTick"
QT_MOC_LITERAL(25, 421, 18), // "slotDeviceSleeping"
QT_MOC_LITERAL(26, 440, 23) // "slotSleepOverlayClicked"

    },
    "RealPlayView\0sgnReturnToDevicesList\0"
    "\0refreshDevicesList\0slotBackBtnClicked\0"
    "slotSnapBtnClicked\0slotRecordBtnClicked\0"
    "slotDefinitionBtnClicked\0slotTalkBtnClicked\0"
    "slotAudioBtnClicked\0slotFullScreenBtnClicked\0"
    "slotPlayerStatusChanged\0status\0"
    "slotRecorderStatusChanged\0"
    "slotTalkerStatusChanged\0slotPtzViewState\0"
    "isShow\0slotPtzControl\0ptzCtrl\0ptzCtrlType\0"
    "slotStreamModeChanged\0mode\0"
    "slotSleepCountdown\0seconds\0"
    "slotSleepCountdownTick\0slotDeviceSleeping\0"
    "slotSleepOverlayClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealPlayView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  107,    2, 0x08 /* Private */,
       5,    0,  108,    2, 0x08 /* Private */,
       6,    0,  109,    2, 0x08 /* Private */,
       7,    0,  110,    2, 0x08 /* Private */,
       8,    0,  111,    2, 0x08 /* Private */,
       9,    0,  112,    2, 0x08 /* Private */,
      10,    0,  113,    2, 0x08 /* Private */,
      11,    1,  114,    2, 0x08 /* Private */,
      13,    1,  117,    2, 0x08 /* Private */,
      14,    1,  120,    2, 0x08 /* Private */,
      15,    1,  123,    2, 0x08 /* Private */,
      17,    2,  126,    2, 0x08 /* Private */,
      20,    1,  131,    2, 0x08 /* Private */,
      22,    1,  134,    2, 0x08 /* Private */,
      24,    0,  137,    2, 0x08 /* Private */,
      25,    0,  138,    2, 0x08 /* Private */,
      26,    0,  139,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        case 13: _t->slotStreamModeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->slotSleepCountdown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slotSleepCountdownTick(); break;
        case 16: _t->slotDeviceSleeping(); break;
        case 17: _t->slotSleepOverlayClicked(); break;
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
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
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
void RealPlayView::sgnReturnToDevicesList(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
