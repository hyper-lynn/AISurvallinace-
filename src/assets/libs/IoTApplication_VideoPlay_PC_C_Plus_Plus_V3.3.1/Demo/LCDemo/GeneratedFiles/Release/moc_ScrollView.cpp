/****************************************************************************
** Meta object code from reading C++ file 'ScrollView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/Utils/CommonView/ScrollView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScrollView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordListScrollView_t {
    QByteArrayData data[15];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordListScrollView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordListScrollView_t qt_meta_stringdata_RecordListScrollView = {
    {
QT_MOC_LITERAL(0, 0, 20), // "RecordListScrollView"
QT_MOC_LITERAL(1, 21, 17), // "sgnPlayBtnClicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "index"
QT_MOC_LITERAL(4, 46, 21), // "sgnDownloadBtnClicked"
QT_MOC_LITERAL(5, 68, 19), // "sgnCancelBtnClicked"
QT_MOC_LITERAL(6, 88, 18), // "sgnDownloadPercent"
QT_MOC_LITERAL(7, 107, 7), // "percent"
QT_MOC_LITERAL(8, 115, 17), // "sgnCancelDownload"
QT_MOC_LITERAL(9, 133, 16), // "sgnSetDownloadUI"
QT_MOC_LITERAL(10, 150, 4), // "flag"
QT_MOC_LITERAL(11, 155, 24), // "slotCurlDownloadFinished"
QT_MOC_LITERAL(12, 180, 14), // "unsigned char*"
QT_MOC_LITERAL(13, 195, 4), // "data"
QT_MOC_LITERAL(14, 200, 7) // "dataLen"

    },
    "RecordListScrollView\0sgnPlayBtnClicked\0"
    "\0index\0sgnDownloadBtnClicked\0"
    "sgnCancelBtnClicked\0sgnDownloadPercent\0"
    "percent\0sgnCancelDownload\0sgnSetDownloadUI\0"
    "flag\0slotCurlDownloadFinished\0"
    "unsigned char*\0data\0dataLen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordListScrollView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,
       6,    2,   58,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
       9,    2,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    7,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12, QMetaType::UInt,   13,   14,

       0        // eod
};

void RecordListScrollView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordListScrollView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnPlayBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sgnDownloadBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sgnCancelBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sgnDownloadPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sgnCancelDownload((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sgnSetDownloadUI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->slotCurlDownloadFinished((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecordListScrollView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnPlayBtnClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecordListScrollView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnDownloadBtnClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecordListScrollView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnCancelBtnClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RecordListScrollView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnDownloadPercent)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RecordListScrollView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnCancelDownload)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RecordListScrollView::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordListScrollView::sgnSetDownloadUI)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordListScrollView::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseScrollView::staticMetaObject>(),
    qt_meta_stringdata_RecordListScrollView.data,
    qt_meta_data_RecordListScrollView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordListScrollView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordListScrollView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordListScrollView.stringdata0))
        return static_cast<void*>(this);
    return BaseScrollView::qt_metacast(_clname);
}

int RecordListScrollView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseScrollView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void RecordListScrollView::sgnPlayBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RecordListScrollView::sgnDownloadBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RecordListScrollView::sgnCancelBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RecordListScrollView::sgnDownloadPercent(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RecordListScrollView::sgnCancelDownload(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RecordListScrollView::sgnSetDownloadUI(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
