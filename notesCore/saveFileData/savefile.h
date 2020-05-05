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
    enum TARGET
    {
        READ=0,
        SAVE,
    };
    struct FutureWatcher
    {
        FutureWatcher(TARGET target):_target(target)
        {
        }
        FutureWatcher(){}//QFuture<T> need this constructor
        enum TARGET _target;
        QVariant _result;

    };
    QSharedPointer<QTimer> _timer;
    QSharedPointer<ISaveFileData> _fileData;
//    QFuture<bool> _future;
    QFutureWatcher<FutureWatcher> _futureWatcher;
//    QFuture<QString> _futureRead;
//    QFutureWatcher<QString> _futureReadWatcher;
    QString _keyword;
    QString _path;
    QString _readCodec;
Q_SIGNALS:
    void onReadFileOK();

public Q_SLOTS:
    const QString &getCodec()
    {
        return _readCodec;
    }
    bool timeoutCB();
    void onResult();

public:
    void onReadFile(const QVariant &v);
    void onSaveFile(const QVariant &v);
    QString getPath()
    {
        return _path;
    }
    void setSaveFileData(QSharedPointer<ISaveFileData> other)
    {
        _fileData = other;
    }
    bool canDelete()
    {
        return _timer.isNull() && _futureWatcher.isFinished();
    }
    FutureWatcher runSaveFile(const QVariant &data);
    FutureWatcher runReadFile(const QString &codecName);
    void save();
    bool copy(const QString &endPath);
    bool rename(const QString &endPath);
    bool renamePath(const QString &endPath);
    bool remove();
    void read(const QString codecName=QLatin1String("UTF-8"));
    SaveFile(const QString &filePath, const QString &keyword);
    QSharedPointer<ISaveFileData> getFileData()
    {
        return _fileData;
    }
    void waitingThread();
    ~SaveFile();
};

#endif // SAVEFILE_H
