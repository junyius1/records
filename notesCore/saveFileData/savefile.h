#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QSaveFile>
#include <QTimer>
#include <QSharedPointer>
#include "savefiledata.h"

#include <QFuture>
#include <QFutureWatcher>

class SaveFile : public QObject
{
private:
    QSharedPointer<QTimer> _timer;
    QSharedPointer<ISaveFileData> _fileData;
    QFuture<bool> _future;
    QFutureWatcher<bool> _futureWatcher;
    QFuture<QString> _futureRead;
    QFutureWatcher<QString> _futureReadWatcher;
    QString _fileName;
//public Q_SIGNAL:
//    void onReadFileOK();
public Q_SLOTS:
    bool timeoutCB();
    void onReadFile();

public:
    void setSaveFileData(QSharedPointer<ISaveFileData> &other)
    {
        _fileData = other;
    }
    bool runSaveFile(const QString &data);
    QString runReadFile();
    void save();
    void read();
    bool switchNewData();
    SaveFile();
    QSharedPointer<ISaveFileData> getFileData()
    {
        return _fileData;
    }
    void waitingThread();
};

#endif // SAVEFILE_H
