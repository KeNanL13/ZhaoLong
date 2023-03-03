/****************************************************************************
** Meta object code from reading C++ file 'SARibbonGallery.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SARibbon-master/src/SARibbonBar/SARibbonGallery.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SARibbonGallery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SARibbonGallery_t {
    QByteArrayData data[13];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonGallery_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonGallery_t qt_meta_stringdata_SARibbonGallery = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SARibbonGallery"
QT_MOC_LITERAL(1, 16, 9), // "triggered"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "QAction*"
QT_MOC_LITERAL(4, 36, 6), // "action"
QT_MOC_LITERAL(5, 43, 7), // "hovered"
QT_MOC_LITERAL(6, 51, 6), // "pageUp"
QT_MOC_LITERAL(7, 58, 8), // "pageDown"
QT_MOC_LITERAL(8, 67, 14), // "showMoreDetail"
QT_MOC_LITERAL(9, 82, 13), // "onItemClicked"
QT_MOC_LITERAL(10, 96, 11), // "QModelIndex"
QT_MOC_LITERAL(11, 108, 5), // "index"
QT_MOC_LITERAL(12, 114, 11) // "onTriggered"

    },
    "SARibbonGallery\0triggered\0\0QAction*\0"
    "action\0hovered\0pageUp\0pageDown\0"
    "showMoreDetail\0onItemClicked\0QModelIndex\0"
    "index\0onTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonGallery[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    1,   58,    2, 0x09 /* Protected */,
      12,    1,   61,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SARibbonGallery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SARibbonGallery *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->hovered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->pageUp(); break;
        case 3: _t->pageDown(); break;
        case 4: _t->showMoreDetail(); break;
        case 5: _t->onItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->onTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 6:
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
            using _t = void (SARibbonGallery::*)(QAction * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonGallery::triggered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SARibbonGallery::*)(QAction * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SARibbonGallery::hovered)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SARibbonGallery::staticMetaObject = { {
    &QFrame::staticMetaObject,
    qt_meta_stringdata_SARibbonGallery.data,
    qt_meta_data_SARibbonGallery,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonGallery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonGallery::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonGallery.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int SARibbonGallery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SARibbonGallery::triggered(QAction * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SARibbonGallery::hovered(QAction * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_SARibbonGalleryViewport_t {
    QByteArrayData data[6];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SARibbonGalleryViewport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SARibbonGalleryViewport_t qt_meta_stringdata_SARibbonGalleryViewport = {
    {
QT_MOC_LITERAL(0, 0, 23), // "SARibbonGalleryViewport"
QT_MOC_LITERAL(1, 24, 18), // "widgetTitleChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "QWidget*"
QT_MOC_LITERAL(4, 53, 1), // "w"
QT_MOC_LITERAL(5, 55, 5) // "title"

    },
    "SARibbonGalleryViewport\0widgetTitleChanged\0"
    "\0QWidget*\0w\0title"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SARibbonGalleryViewport[] = {

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
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,

       0        // eod
};

void SARibbonGalleryViewport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SARibbonGalleryViewport *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widgetTitleChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SARibbonGalleryViewport::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SARibbonGalleryViewport.data,
    qt_meta_data_SARibbonGalleryViewport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SARibbonGalleryViewport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SARibbonGalleryViewport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SARibbonGalleryViewport.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SARibbonGalleryViewport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
