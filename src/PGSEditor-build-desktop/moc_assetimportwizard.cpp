/****************************************************************************
** Meta object code from reading C++ file 'assetimportwizard.h'
**
** Created: Fri Sep 16 12:13:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PGSEditor/assetimportwizard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'assetimportwizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AssetImportWizard[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_AssetImportWizard[] = {
    "AssetImportWizard\0"
};

const QMetaObject AssetImportWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_AssetImportWizard,
      qt_meta_data_AssetImportWizard, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AssetImportWizard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AssetImportWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AssetImportWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AssetImportWizard))
        return static_cast<void*>(const_cast< AssetImportWizard*>(this));
    return QWizard::qt_metacast(_clname);
}

int AssetImportWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
