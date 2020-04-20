#include "notemodeldata.h"

void LineStringModelData::data2QVariant(QVariant &variant)
{
    QString str;
    for(QList<QVariant>::iterator it =_noteData.begin(); it!= _noteData.end(); it++)
    {
        str += it->toString();
        str.push_back('\n');
    }
    variant.setValue(str);
}

void LineStringModelData::qVariant2Data(const QVariant &variant)
{
    QString str = variant.toString();
    QStringList t = str.split('\n');
    for(QStringList::iterator it =t.begin(); it!= t.end(); it++)
    {
        _noteData.push_back(*it);
    }
}
