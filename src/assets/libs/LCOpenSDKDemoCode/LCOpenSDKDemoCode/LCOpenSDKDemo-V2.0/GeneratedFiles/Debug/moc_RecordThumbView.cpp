/****************************************************************************
** Meta object code from reading C++ file 'RecordThumbView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/View/RecordList/RecordThumbView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordThumbView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordThumbView_t {
    QByteArrayData data[17];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordThumbView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordThumbView_t qt_meta_stringdata_RecordThumbView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RecordThumbView"
QT_MOC_LITERAL(1, 16, 17), // "sgnPlayBtnClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 21), // "sgnDownloadBtnClicked"
QT_MOC_LITERAL(5, 63, 19), // "sgnCancelBtnClicked"
QT_MOC_LITERAL(6, 83, 18), // "slotPlayBtnClicked"
QT_MOC_LITERAL(7, 102, 22), // "slotDownloadBtnClicked"
QT_MOC_LITERAL(8, 125, 20), // "slotCancelBtnClicked"
QT_MOC_LITERAL(9, 146, 14), // "slotMouseEvent"
QT_MOC_LITERAL(10, 161, 6), // "widget"
QT_MOC_LITERAL(11, 168, 7), // "isEnter"
QT_MOC_LITERAL(12, 176, 19), // "slotDownloadPercent"
QT_MOC_LITERAL(13, 196, 7), // "percent"
QT_MOC_LITERAL(14, 204, 18), // "slotCancelDownload"
QT_MOC_LITERAL(15, 223, 17), // "slotSetDownloadUI"
QT_MOC_LITERAL(16, 241, 4) // "flag"

    },
    "RecordThumbView\0sgnPlayBtnClicked\0\0"
    "index\0sgnDownloadBtnClicked\0"
    "sgnCancelBtnClicked\0slotPlayBtnClicked\0"
    "slotDownloadBtnClicked\0slotCancelBtnClicked\0"
    "slotMouseEvent\0widget\0isEnter\0"
    "slotDownloadPercent\0percent\0"
    "slotCancelDownload\0slotSetDownloadUI\0"
    "flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordThumbView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    2,   76,    2, 0x0a /* Public */,
      12,    2,   81,    2, 0x0a /* Public */,
      14,    1,   86,    2, 0x0a /* Public */,
      15,    2,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   13,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,   16,

       0        // eod
};

void RecordThumbView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordThumbView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnPlayBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sgnDownloadBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sgnCancelBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotPlayBtnClicked(); break;
        case 4: _t->slotDownloadBtnClicked(); break;
        case 5: _t->slotCancelBtnClicked(); break;
        case 6: _t->slotMouseEvent((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->slotDownloadPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slotCancelDownload((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotSetDownloadUI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecordThumbView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordThumbView::sgnPlayBtnClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecordThumbView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordThumbView::sgnDownloadBtnClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecordThumbView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordThumbView::sgnCancelBtnClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordThumbView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RecordThumbView.data,
    qt_meta_data_RecordThumbView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordThumbView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordThumbView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordThumbView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RecordThumbView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void RecordThumbView::sgnPlayBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RecordThumbView::sgnDownloadBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RecordThumbView::sgnCancelBtnClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
