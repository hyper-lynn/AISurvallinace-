/****************************************************************************
** Meta object code from reading C++ file 'RecordPlayView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/VideoPlay/RecordPlayView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordPlayView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordPlayView_t {
    QByteArrayData data[15];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordPlayView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordPlayView_t qt_meta_stringdata_RecordPlayView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RecordPlayView"
QT_MOC_LITERAL(1, 15, 19), // "sgnBackToRecordList"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 10), // "recordType"
QT_MOC_LITERAL(4, 47, 18), // "slotBackBtnClicked"
QT_MOC_LITERAL(5, 66, 23), // "slotPlayerStatusChanged"
QT_MOC_LITERAL(6, 90, 6), // "status"
QT_MOC_LITERAL(7, 97, 14), // "slotPlayerTime"
QT_MOC_LITERAL(8, 112, 4), // "time"
QT_MOC_LITERAL(9, 117, 24), // "slotFullScreenBtnClicked"
QT_MOC_LITERAL(10, 142, 16), // "slotProgressSeek"
QT_MOC_LITERAL(11, 159, 5), // "value"
QT_MOC_LITERAL(12, 165, 18), // "slotPlayBtnClicked"
QT_MOC_LITERAL(13, 184, 20), // "slotVideoBaseClicked"
QT_MOC_LITERAL(14, 205, 23) // "slotSpeedPlayBtnClicked"

    },
    "RecordPlayView\0sgnBackToRecordList\0\0"
    "recordType\0slotBackBtnClicked\0"
    "slotPlayerStatusChanged\0status\0"
    "slotPlayerTime\0time\0slotFullScreenBtnClicked\0"
    "slotProgressSeek\0value\0slotPlayBtnClicked\0"
    "slotVideoBaseClicked\0slotSpeedPlayBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordPlayView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   62,    2, 0x08 /* Private */,
       5,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    1,   70,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,
      13,    0,   74,    2, 0x08 /* Private */,
      14,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Long,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordPlayView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordPlayView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnBackToRecordList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotBackBtnClicked(); break;
        case 2: _t->slotPlayerStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotPlayerTime((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->slotFullScreenBtnClicked(); break;
        case 5: _t->slotProgressSeek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotPlayBtnClicked(); break;
        case 7: _t->slotVideoBaseClicked(); break;
        case 8: _t->slotSpeedPlayBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecordPlayView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordPlayView::sgnBackToRecordList)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordPlayView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_RecordPlayView.data,
    qt_meta_data_RecordPlayView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordPlayView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordPlayView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordPlayView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RecordPlayView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void RecordPlayView::sgnBackToRecordList(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
