/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Wed Sep 21 14:38:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PGSEditor/controller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controller[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      48,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   11,   11,   11, 0x0a,
      76,   11,   11,   11, 0x0a,
      99,   12,   11,   11, 0x0a,
     123,   11,   11,   11, 0x0a,
     139,   11,   11,   11, 0x0a,
     160,   11,   11,   11, 0x0a,
     168,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0dir\0sceneDirectorySelected(QString)\0"
    "sceneChanged()\0onNewScene()\0"
    "onNewSceneConfigured()\0onSaveNewScene(QString)\0"
    "onImportAsset()\0onImportConfigured()\0"
    "onRun()\0onExport()\0"
};

const QMetaObject Controller::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Controller,
      qt_meta_data_Controller, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controller::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controller))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QWidget::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sceneDirectorySelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: sceneChanged(); break;
        case 2: onNewScene(); break;
        case 3: onNewSceneConfigured(); break;
        case 4: onSaveNewScene((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: onImportAsset(); break;
        case 6: onImportConfigured(); break;
        case 7: onRun(); break;
        case 8: onExport(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Controller::sceneDirectorySelected(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
