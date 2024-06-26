/****************************************************************************
** Meta object code from reading C++ file 'canthread.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../06/canthread.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCANThreadENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCANThreadENDCLASS = QtMocHelpers::stringData(
    "CANThread",
    "getCompleteFrame",
    "",
    "frame_complete",
    "fl",
    "fr",
    "saveSignal",
    "fc",
    "position",
    "sleep_50"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCANThreadENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[10];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[3];
    char stringdata5[3];
    char stringdata6[11];
    char stringdata7[3];
    char stringdata8[9];
    char stringdata9[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCANThreadENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCANThreadENDCLASS_t qt_meta_stringdata_CLASSCANThreadENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "CANThread"
        QT_MOC_LITERAL(10, 16),  // "getCompleteFrame"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 14),  // "frame_complete"
        QT_MOC_LITERAL(43, 2),  // "fl"
        QT_MOC_LITERAL(46, 2),  // "fr"
        QT_MOC_LITERAL(49, 10),  // "saveSignal"
        QT_MOC_LITERAL(60, 2),  // "fc"
        QT_MOC_LITERAL(63, 8),  // "position"
        QT_MOC_LITERAL(72, 8)   // "sleep_50"
    },
    "CANThread",
    "getCompleteFrame",
    "",
    "frame_complete",
    "fl",
    "fr",
    "saveSignal",
    "fc",
    "position",
    "sleep_50"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCANThreadENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    1 /* Public */,
       6,    2,   37,    2, 0x06,    4 /* Public */,
       9,    0,   42,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    7,    8,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CANThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CLASSCANThreadENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCANThreadENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCANThreadENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CANThread, std::true_type>,
        // method 'getCompleteFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<frame_complete, std::false_type>,
        QtPrivate::TypeAndForceComplete<frame_complete, std::false_type>,
        // method 'saveSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<frame_complete, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'sleep_50'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CANThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CANThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->getCompleteFrame((*reinterpret_cast< std::add_pointer_t<frame_complete>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<frame_complete>>(_a[2]))); break;
        case 1: _t->saveSignal((*reinterpret_cast< std::add_pointer_t<frame_complete>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: _t->sleep_50(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANThread::*)(frame_complete , frame_complete );
            if (_t _q_method = &CANThread::getCompleteFrame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CANThread::*)(frame_complete , bool );
            if (_t _q_method = &CANThread::saveSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CANThread::*)();
            if (_t _q_method = &CANThread::sleep_50; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *CANThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCANThreadENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CANThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CANThread::getCompleteFrame(frame_complete _t1, frame_complete _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CANThread::saveSignal(frame_complete _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CANThread::sleep_50()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
