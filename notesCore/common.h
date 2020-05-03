#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDebug>
//#include <QtQml/QQmlApplicationEngine>

namespace notes {
    void debug(const QString &str);

    QString getFileNameNoDot(const QString &fileName);
}

#endif // COMMON_H
