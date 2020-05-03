#include "common.h"
#include <QFile>

namespace notes {
    void debug(const QString &str)
    {
        qDebug() << str;
    }

    QString getFileNameNoDot(const QString &fileName)
    {
        int dot = fileName.lastIndexOf('.');
        if(dot==-1)
        {
            return fileName;
        }
        return fileName.left(dot);
    }
}
