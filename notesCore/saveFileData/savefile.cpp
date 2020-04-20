#include "savefile.h"
#include "saveFileData/savefilepool.h"
#include <QtConcurrent>

SaveFile::SaveFile(const QString &filePath, const QString &keyword)
{
    _path = filePath;
   _keyword = keyword;
}

void SaveFile::save()
{
    if(_timer) return;
    _timer = QSharedPointer<QTimer> (
            new QTimer(),
            &QTimer::deleteLater
         );

    connect(_timer.data(), &QTimer::timeout, this, &SaveFile::timeoutCB);
    _timer->start(50000);
}

void SaveFile::read()
{
    waitingThread();
    _futureRead = QtConcurrent::run(this, &SaveFile::runReadFile);
    connect(&_futureReadWatcher, &QFutureWatcherBase::finished, this, &SaveFile::onReadFile);
    _futureWatcher.setFuture(_future);
}

void SaveFile::onReadFile()
{
    _fileData->qVariant2Data(_futureReadWatcher.result());
    emit onReadFileOK();
    SaveFilePool::instance()->delFileRead(getPath());
}

void SaveFile::waitingThread(){
    if(!_futureWatcher.isFinished()){
        _futureWatcher.waitForFinished();//block if the save file thread not finished
    }
    if(!_futureReadWatcher.isFinished()){
        _futureReadWatcher.waitForFinished();//block if the read file thread not finished
    }
}

void SaveFile::onSaveFile()
{
//    emit onWriteFileOK();
    SaveFilePool::instance()->delFileSave(getPath());
}

bool SaveFile::timeoutCB()
{
    waitingThread();
    QVariant variant;
    _fileData->data2QVariant(variant);
    _future = QtConcurrent::run(this, &SaveFile::runSaveFile, variant);
    connect(&_futureWatcher, &QFutureWatcherBase::finished, this, &SaveFile::onSaveFile);
    _futureWatcher.setFuture(_future);
    _timer->stop();
    _timer.clear();
    qDebug() << "the time value =" << _timer;
    return true;
}

bool SaveFile::runSaveFile(const QVariant &data)
{
    QSaveFile qSaveFile(_keyword);
    if(!qSaveFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QString t = data.toString();
    qSaveFile.write(t.toStdString().c_str());
    qSaveFile.commit();
    return true;
}

QString SaveFile::runReadFile()
{
    QFile file(_keyword);
    file.open(QIODevice::ReadOnly);
    QString s;

    QTextStream ts(&file);
    s.append(ts.readAll());
    return s;
}
