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
    Q_OBJECT
private:
    QSharedPointer<QTimer> _timer;
    QSharedPointer<ISaveFileData> _fileData;
//    QFuture<bool> _future;
    QFutureWatcher<bool> _futureWatcher;
//    QFuture<QString> _futureRead;
    QFutureWatcher<QString> _futureReadWatcher;
    QString _keyword;
    QString _path;
    QString _readCodec;
Q_SIGNALS:
    void onReadFileOK();
//    void onSaveFileOK();
public Q_SLOTS:
    const QString &getCodec()
    {
        return _readCodec;
    }
    bool timeoutCB();
    void onReadFile();
    void onSaveFile();

public:
    QString getPath()
    {
        return _path;
    }
    void setSaveFileData(QSharedPointer<ISaveFileData> other)
    {
        _fileData = other;
    }
    bool runSaveFile(const QVariant &data);
    QString runReadFile(const QString &codecName);
    void save(const QSharedPointer<SaveFile> sp);
    void read(const QSharedPointer<SaveFile> sp, const QString codecName=QLatin1String("UTF-8"));
    bool switchNewData();
    SaveFile(const QString &filePath, const QString &keyword);
    QSharedPointer<ISaveFileData> getFileData()
    {
        return _fileData;
    }
    void waitingThread();
    ~SaveFile();
};

#endif // SAVEFILE_H
