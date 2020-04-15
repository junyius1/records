#include "savefile.h"
#include <QtConcurrent>

SaveFile::SaveFile()
{

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
    _fileData->qString2Data(_futureReadWatcher.result());
}

void SaveFile::waitingThread(){
    if(!_futureWatcher.isFinished()){
        _futureWatcher.waitForFinished();//block if the save file thread not finished
    }
    if(!_futureReadWatcher.isFinished()){
        _futureReadWatcher.waitForFinished();//block if the read file thread not finished
    }
}

bool SaveFile::timeoutCB()
{
    waitingThread();
    _future = QtConcurrent::run(this, &SaveFile::runSaveFile, _fileData->data2QString());
    _futureWatcher.setFuture(_future);
    _timer->stop();
    _timer.clear();
    qDebug() << "the time value =" << _timer;
    return true;
}

bool SaveFile::runSaveFile(const QString &data)
{
    QSaveFile qSaveFile(_fileName);
    if(!qSaveFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    qSaveFile.write(data.toStdString().c_str());
    qSaveFile.commit();
    return true;
}

QString SaveFile::runReadFile()
{
    QFile file(_fileName);
    file.open(QIODevice::ReadOnly);
    QString s;

    QTextStream ts(&file);
    s.append(ts.readAll());
    return s;
}
