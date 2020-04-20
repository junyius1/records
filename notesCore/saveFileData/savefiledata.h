#ifndef SAVEFILEDATA_H
#define SAVEFILEDATA_H

#include <QVariant>

class ISaveFileData
{
public:
    virtual void data2QVariant(QVariant &variant) =0;
    virtual void qVariant2Data(const QVariant &str) =0;
    virtual ~ISaveFileData(){}
};

#endif // SAVEFILEDATA_H
