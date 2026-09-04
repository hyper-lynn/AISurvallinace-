/****************************************************************************
** Meta object code from reading C++ file 'TokenCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Src/Ctrl/TokenCtrl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TokenCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TokenCtrl_t {
    QByteArrayData data[5];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TokenCtrl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TokenCtrl_t qt_meta_stringdata_TokenCtrl = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TokenCtrl"
QT_MOC_LITERAL(1, 10, 20), // "sgnGetPlayInfoReslut"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "bGetIotToken"
QT_MOC_LITERAL(4, 45, 19) // "sgnGetP2pInfoReslut"

    },
    "TokenCtrl\0sgnGetPlayInfoReslut\0\0"
    "bGetIotToken\0sgnGetP2pInfoReslut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TokenCtrl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void TokenCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TokenCtrl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sgnGetPlayInfoReslut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sgnGetP2pInfoReslut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TokenCtrl::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TokenCtrl::sgnGetPlayInfoReslut)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TokenCtrl::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TokenCtrl::sgnGetP2pInfoReslut)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TokenCtrl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TokenCtrl.data,
    qt_meta_data_TokenCtrl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TokenCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TokenCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TokenCtrl.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Common::NetworkListener"))
        return static_cast< Common::NetworkListener*>(this);
    return QObject::qt_metacast(_clname);
}

int TokenCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TokenCtrl::sgnGetPlayInfoReslut(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TokenCtrl::sgnGetP2pInfoReslut(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
