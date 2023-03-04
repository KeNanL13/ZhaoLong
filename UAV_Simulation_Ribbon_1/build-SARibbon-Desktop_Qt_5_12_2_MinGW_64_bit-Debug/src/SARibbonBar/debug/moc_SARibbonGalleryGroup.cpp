/****************************************************************************
** Meta object code from reading C++ file 'SARibbonGalleryGroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SARibbon-master/src/SARibbonBar/SARibbonGalleryGroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SARibbonGalleryGroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SARibbonGalleryGroupModel_t {
    QByteArrayData data[1];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonGalleryGroupModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonGalleryGroupModel_t qt_meta_stringdata_SARibbonGalleryGroupModel = {
    {
QT_MOC_LITERAL(0, 0, 25) // "SARibbonGalleryGroupModel"

    },
    "SARibbonGalleryGroupModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonGalleryGroupModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SARibbonGalleryGroupModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SARibbonGalleryGroupModel::staticMetaObject = { {
    &QAbstractListModel::staticMetaObject,
    qt_meta_stringdata_SARibbonGalleryGroupModel.data,
    qt_meta_data_SARibbonGalleryGroupModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonGalleryGroupModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonGalleryGroupModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonGalleryGroupModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SARibbonGalleryGroupModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_SARibbonGalleryGroup_t {
    QByteArrayData data[12];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonGalleryGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonGalleryGroup_t qt_meta_stringdata_SARibbonGalleryGroup = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SARibbonGalleryGroup"
QT_MOC_LITERAL(1, 21, 17), // "groupTitleChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "title"
QT_MOC_LITERAL(4, 46, 9), // "triggered"
QT_MOC_LITERAL(5, 56, 8), // "QAction*"
QT_MOC_LITERAL(6, 65, 6), // "action"
QT_MOC_LITERAL(7, 72, 7), // "hovered"
QT_MOC_LITERAL(8, 80, 13), // "onItemClicked"
QT_MOC_LITERAL(9, 94, 11), // "QModelIndex"
QT_MOC_LITERAL(10, 106, 5), // "index"
QT_MOC_LITERAL(11, 112, 13) // "onItemEntered"

    },
    "SARibbonGalleryGroup\0groupTitleChanged\0"
    "\0title\0triggered\0QAction*\0action\0"
    "hovered\0onItemClicked\0QModelIndex\0"
    "index\0onItemEntered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonGalleryGroup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   48,    2, 0x08 /* Private */,
      11,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void SARibbonGalleryGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SARibbonGalleryGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->groupTitleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->hovered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->onItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->onItemEntered((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SARibbonGalleryGroup::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonGalleryGroup::groupTitleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SARibbonGalleryGroup::*)(QAction * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonGalleryGroup::triggered)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SARibbonGalleryGroup::*)(QAction * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonGalleryGroup::hovered)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SARibbonGalleryGroup::staticMetaObject = { {
    &QListView::staticMetaObject,
    qt_meta_stringdata_SARibbonGalleryGroup.data,
    qt_meta_data_SARibbonGalleryGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonGalleryGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonGalleryGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonGalleryGroup.stringdata0))
        return static_cast<void*>(this);
    return QListView::qt_metacast(_clname);
}

int SARibbonGalleryGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SARibbonGalleryGroup::groupTitleChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SARibbonGalleryGroup::triggered(QAction * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SARibbonGalleryGroup::hovered(QAction * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
