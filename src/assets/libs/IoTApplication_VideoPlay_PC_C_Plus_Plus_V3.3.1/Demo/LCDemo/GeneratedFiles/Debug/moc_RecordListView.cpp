/****************************************************************************
** Meta object code from reading C++ file 'RecordListView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/RecordList/RecordListView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordListView_t {
    QByteArrayData data[25];
    char stringdata0[369];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordListView_t qt_meta_stringdata_RecordListView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RecordListView"
QT_MOC_LITERAL(1, 15, 18), // "sgnPlayCloudRecord"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 19), // "sgnPlayDeviceRecord"
QT_MOC_LITERAL(5, 61, 22), // "sgnReturnToDevicesList"
QT_MOC_LITERAL(6, 84, 18), // "refreshDevicesList"
QT_MOC_LITERAL(7, 103, 18), // "sgnDownloadPercent"
QT_MOC_LITERAL(8, 122, 7), // "percent"
QT_MOC_LITERAL(9, 130, 17), // "sgnCancelDownload"
QT_MOC_LITERAL(10, 148, 16), // "sgnSetDownloadUI"
QT_MOC_LITERAL(11, 165, 4), // "flag"
QT_MOC_LITERAL(12, 170, 14), // "sgnSetShowInfo"
QT_MOC_LITERAL(13, 185, 4), // "info"
QT_MOC_LITERAL(14, 190, 22), // "slotRecordThreadResult"
QT_MOC_LITERAL(15, 213, 6), // "result"
QT_MOC_LITERAL(16, 220, 18), // "slotPlayBtnClicked"
QT_MOC_LITERAL(17, 239, 22), // "slotDownloadBtnClicked"
QT_MOC_LITERAL(18, 262, 20), // "slotCancelBtnClicked"
QT_MOC_LITERAL(19, 283, 18), // "slotBackBtnClicked"
QT_MOC_LITERAL(20, 302, 10), // "slotSearch"
QT_MOC_LITERAL(21, 313, 4), // "date"
QT_MOC_LITERAL(22, 318, 22), // "slotShowOrHideCalendar"
QT_MOC_LITERAL(23, 341, 11), // "slotSetText"
QT_MOC_LITERAL(24, 353, 15) // "slotSetShowInfo"

    },
    "RecordListView\0sgnPlayCloudRecord\0\0"
    "index\0sgnPlayDeviceRecord\0"
    "sgnReturnToDevicesList\0refreshDevicesList\0"
    "sgnDownloadPercent\0percent\0sgnCancelDownload\0"
    "sgnSetDownloadUI\0flag\0sgnSetShowInfo\0"
    "info\0slotRecordThreadResult\0result\0"
    "slotPlayBtnClicked\0slotDownloadBtnClicked\0"
    "slotCancelBtnClicked\0slotBackBtnClicked\0"
    "slotSearch\0date\0slotShowOrHideCalendar\0"
    "slotSetText\0slotSetShowInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordListView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    1,  100,    2, 0x06 /* Public */,
       7,    2,  103,    2, 0x06 /* Public */,
       9,    1,  108,    2, 0x06 /* Public */,
      10,    2,  111,    2, 0x06 /* Public */,
      12,    1,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  119,    2, 0x08 /* Private */,
      16,    1,  122,    2, 0x08 /* Private */,
      17,    1,  125,    2, 0x08 /* Private */,
      18,    1,  128,    2, 0x08 /* Private */,
      19,    0,  131,    2, 0x08 /* Private */,
      20,    1,  132,    2, 0x08 /* Private */,
      22,    0,  135,    2, 0x08 /* Private */,
      23,    1,  136,    2, 0x08 /* Private */,
      24,    1,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    8,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   21,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void RecordListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnPlayCloudRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sgnPlayDeviceRecord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sgnReturnToDevicesList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sgnDownloadPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sgnCancelDownload((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sgnSetDownloadUI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->sgnSetShowInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slotRecordThreadResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotPlayBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotDownloadBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotCancelBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotBackBtnClicked(); break;
        case 12: _t->slotSearch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->slotShowOrHideCalendar(); break;
        case 14: _t->slotSetText((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 15: _t->slotSetShowInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecordListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnPlayCloudRecord)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnPlayDeviceRecord)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnReturnToDevicesList)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnDownloadPercent)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnCancelDownload)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnSetDownloadUI)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (RecordListView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListView::sgnSetShowInfo)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordListView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_RecordListView.data,
    qt_meta_data_RecordListView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordListView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordListView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "LCOpenSDK_DownloadListener"))
        return static_cast< LCOpenSDK_DownloadListener*>(this);
    return QWidget::qt_metacast(_clname);
}

int RecordListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void RecordListView::sgnPlayCloudRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RecordListView::sgnPlayDeviceRecord(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RecordListView::sgnReturnToDevicesList(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RecordListView::sgnDownloadPercent(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RecordListView::sgnCancelDownload(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RecordListView::sgnSetDownloadUI(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void RecordListView::sgnSetShowInfo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
