/****************************************************************************
** Meta object code from reading C++ file 'SARibbonActionsManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SARibbon-master/src/SARibbonBar/SARibbonActionsManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SARibbonActionsManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SARibbonActionsManager_t {
    QByteArrayData data[9];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonActionsManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonActionsManager_t qt_meta_stringdata_SARibbonActionsManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SARibbonActionsManager"
QT_MOC_LITERAL(1, 23, 16), // "actionTagChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 3), // "tag"
QT_MOC_LITERAL(4, 45, 8), // "isdelete"
QT_MOC_LITERAL(5, 54, 17), // "onActionDestroyed"
QT_MOC_LITERAL(6, 72, 1), // "o"
QT_MOC_LITERAL(7, 74, 22), // "onCategoryTitleChanged"
QT_MOC_LITERAL(8, 97, 5) // "title"

    },
    "SARibbonActionsManager\0actionTagChanged\0"
    "\0tag\0isdelete\0onActionDestroyed\0o\0"
    "onCategoryTitleChanged\0title"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonActionsManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   34,    2, 0x08 /* Private */,
       7,    1,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    6,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void SARibbonActionsManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SARibbonActionsManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actionTagChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->onActionDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->onCategoryTitleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SARibbonActionsManager::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonActionsManager::actionTagChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SARibbonActionsManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SARibbonActionsManager.data,
    qt_meta_data_SARibbonActionsManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonActionsManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonActionsManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonActionsManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SARibbonActionsManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SARibbonActionsManager::actionTagChanged(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SARibbonActionsManagerModel_t {
    QByteArrayData data[5];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonActionsManagerModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonActionsManagerModel_t qt_meta_stringdata_SARibbonActionsManagerModel = {
    {
QT_MOC_LITERAL(0, 0, 27), // "SARibbonActionsManagerModel"
QT_MOC_LITERAL(1, 28, 18), // "onActionTagChanged"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 3), // "tag"
QT_MOC_LITERAL(4, 52, 8) // "isdelete"

    },
    "SARibbonActionsManagerModel\0"
    "onActionTagChanged\0\0tag\0isdelete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonActionsManagerModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,

       0        // eod
};

void SARibbonActionsManagerModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SARibbonActionsManagerModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onActionTagChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SARibbonActionsManagerModel::staticMetaObject = { {
    &QAbstractListModel::staticMetaObject,
    qt_meta_stringdata_SARibbonActionsManagerModel.data,
    qt_meta_data_SARibbonActionsManagerModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonActionsManagerModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonActionsManagerModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonActionsManagerModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SARibbonActionsManagerModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
