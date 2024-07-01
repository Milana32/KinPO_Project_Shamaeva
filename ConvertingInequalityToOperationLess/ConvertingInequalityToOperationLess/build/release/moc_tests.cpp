/****************************************************************************
** Meta object code from reading C++ file 'tests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../tests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tests_t {
    QByteArrayData data[12];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tests_t qt_meta_stringdata_Tests = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Tests"
QT_MOC_LITERAL(1, 6, 14), // "testisOperator"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 19), // "testisOperator_data"
QT_MOC_LITERAL(4, 42, 18), // "testisValidOperand"
QT_MOC_LITERAL(5, 61, 23), // "testisValidOperand_data"
QT_MOC_LITERAL(6, 85, 20), // "testbuildLogicalTree"
QT_MOC_LITERAL(7, 106, 25), // "testbuildLogicalTree_data"
QT_MOC_LITERAL(8, 132, 17), // "testConvertToLess"
QT_MOC_LITERAL(9, 150, 22), // "testConvertToLess_data"
QT_MOC_LITERAL(10, 173, 16), // "testTreeToString"
QT_MOC_LITERAL(11, 190, 21) // "testTreeToString_data"

    },
    "Tests\0testisOperator\0\0testisOperator_data\0"
    "testisValidOperand\0testisValidOperand_data\0"
    "testbuildLogicalTree\0testbuildLogicalTree_data\0"
    "testConvertToLess\0testConvertToLess_data\0"
    "testTreeToString\0testTreeToString_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tests[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testisOperator(); break;
        case 1: _t->testisOperator_data(); break;
        case 2: _t->testisValidOperand(); break;
        case 3: _t->testisValidOperand_data(); break;
        case 4: _t->testbuildLogicalTree(); break;
        case 5: _t->testbuildLogicalTree_data(); break;
        case 6: _t->testConvertToLess(); break;
        case 7: _t->testConvertToLess_data(); break;
        case 8: _t->testTreeToString(); break;
        case 9: _t->testTreeToString_data(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Tests::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Tests.data,
    qt_meta_data_Tests,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tests::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tests.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Tests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
