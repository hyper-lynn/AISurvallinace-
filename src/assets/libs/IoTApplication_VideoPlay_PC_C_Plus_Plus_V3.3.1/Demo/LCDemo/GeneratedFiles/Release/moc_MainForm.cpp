/****************************************************************************
** Meta object code from reading C++ file 'MainForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/View/MainForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainForm_t {
    QByteArrayData data[19];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainForm_t qt_meta_stringdata_MainForm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MainForm"
QT_MOC_LITERAL(1, 9, 17), // "sgnGetDevicesList"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "slotShowDevicesList"
QT_MOC_LITERAL(4, 48, 17), // "slotReturnToLogin"
QT_MOC_LITERAL(5, 66, 17), // "slotShowAddDevice"
QT_MOC_LITERAL(6, 84, 23), // "slotReturnToDevicesList"
QT_MOC_LITERAL(7, 108, 18), // "refreshDevicesList"
QT_MOC_LITERAL(8, 127, 21), // "slotShowDeviceOperate"
QT_MOC_LITERAL(9, 149, 11), // "deviceIndex"
QT_MOC_LITERAL(10, 161, 8), // "slotPlay"
QT_MOC_LITERAL(11, 170, 23), // "slotShowLocalRecordList"
QT_MOC_LITERAL(12, 194, 23), // "slotShowCloudRecordList"
QT_MOC_LITERAL(13, 218, 12), // "slotCloseWin"
QT_MOC_LITERAL(14, 231, 19), // "slotPlayCloudRecord"
QT_MOC_LITERAL(15, 251, 11), // "recordIndex"
QT_MOC_LITERAL(16, 263, 20), // "slotPlayDeviceRecord"
QT_MOC_LITERAL(17, 284, 20), // "slotBackToRecordList"
QT_MOC_LITERAL(18, 305, 10) // "recordType"

    },
    "MainForm\0sgnGetDevicesList\0\0"
    "slotShowDevicesList\0slotReturnToLogin\0"
    "slotShowAddDevice\0slotReturnToDevicesList\0"
    "refreshDevicesList\0slotShowDeviceOperate\0"
    "deviceIndex\0slotPlay\0slotShowLocalRecordList\0"
    "slotShowCloudRecordList\0slotCloseWin\0"
    "slotPlayCloudRecord\0recordIndex\0"
    "slotPlayDeviceRecord\0slotBackToRecordList\0"
    "recordType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainForm[] = {

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
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    1,   86,    2, 0x08 /* Private */,
      10,    1,   89,    2, 0x08 /* Private */,
      11,    1,   92,    2, 0x08 /* Private */,
      12,    1,   95,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    2,   99,    2, 0x08 /* Private */,
      16,    2,  104,    2, 0x08 /* Private */,
      17,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   15,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void MainForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnGetDevicesList(); break;
        case 1: _t->slotShowDevicesList(); break;
        case 2: _t->slotReturnToLogin(); break;
        case 3: _t->slotShowAddDevice(); break;
        case 4: _t->slotReturnToDevicesList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slotShowDeviceOperate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotPlay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotShowLocalRecordList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotShowCloudRecordList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotCloseWin(); break;
        case 10: _t->slotPlayCloudRecord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->slotPlayDeviceRecord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->slotBackToRecordList((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainForm::sgnGetDevicesList)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_MainForm.data,
    qt_meta_data_MainForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainForm.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int MainForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void MainForm::sgnGetDevicesList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
