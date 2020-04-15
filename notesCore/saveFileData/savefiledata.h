#ifndef SAVEFILEDATA_H
#define SAVEFILEDATA_H

#include <QString>

class ISaveFileData
{
public:
    virtual QString data2QString() =0;
    virtual void qString2Data(const QString &str) =0;
    virtual ~ISaveFileData() =0;
};

#endif // SAVEFILEDATA_H
