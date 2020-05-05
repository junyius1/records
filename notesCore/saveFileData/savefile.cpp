#include "savefile.h"
#include "saveFileData/savefilepool.h"
#include <QtConcurrent>

SaveFile::SaveFile(const QString &filePath, const QString &keyword):_readCodec(QLatin1String("UTF-8"))
{
    _path = filePath;
   _keyword = keyword;
   connect(&_futureWatcher, &QFutureWatcher<FutureWatcher>::finished, this, &SaveFile::onResult);
//   connect(&_futureReadWatcher, &QFutureWatcher<QString>::finished, this, &SaveFile::onReadFile);
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

void SaveFile::read(const QString codecName)
{
    waitingThread();
    QFuture<FutureWatcher> futureRead = QtConcurrent::run(this, &SaveFile::runReadFile, codecName);
    _futureWatcher.setFuture(futureRead);
}

bool SaveFile::renamePath(const QString &endPath)
{
    waitingThread();
    _path = endPath;
    return true;
}

bool SaveFile::rename(const QString &endPath)
{
    waitingThread();
    _path = endPath;
    return QFile::rename(getPath(), endPath);
}

bool SaveFile::copy(const QString &endPath)
{
    waitingThread();
    return QFile::copy(getPath(), endPath);
}

bool SaveFile::remove()
{
    waitingThread();
    return QFile::remove(getPath());
}

void SaveFile::onResult()
{
    FutureWatcher v = _futureWatcher.result();
    if(v._target == READ)
    {
        onReadFile(v._result);
    } else if(v._target == SAVE)
    {
        onSaveFile(v._result);
    }
}

void SaveFile::onReadFile(const QVariant &v)
{
    _fileData->qVariant2Data(v);
    emit onReadFileOK();
}

void SaveFile::waitingThread(){
    if(!_futureWatcher.isFinished()){
        _futureWatcher.waitForFinished();//block if the save file thread not finished
    }
//    if(!_futureReadWatcher.isFinished()){
//        _futureReadWatcher.waitForFinished();//block if the read file thread not finished
//    }
}

void SaveFile::onSaveFile(const QVariant &v)
{
//    emit onWriteFileOK();
      SaveFilePool::instance()->testDelFileSave(getPath());
}

bool SaveFile::timeoutCB()
{
    waitingThread();
    QVariant variant;
    _fileData->data2QVariant(variant);
    QFuture<FutureWatcher> future = QtConcurrent::run(this, &SaveFile::runSaveFile, variant);
    _futureWatcher.setFuture(future);
    _timer->stop();
    _timer.clear();
    qDebug() << "the time value =" << _timer;
    return true;
}

SaveFile::FutureWatcher SaveFile::runSaveFile(const QVariant &data)
{
    QSaveFile qSaveFile(getPath());
    if(!qSaveFile.open(QIODevice::WriteOnly))
    {
        return SaveFile::FutureWatcher(SAVE);
    }
    QString t = data.toString();
    qSaveFile.write(t.toStdString().c_str());
    qSaveFile.commit();
    return SaveFile::FutureWatcher(SAVE);
}

//QString GetCorrectUnicode(const QByteArray &ba, const char *codecName)
//{
//    QTextCodec::ConverterState state;
//    QTextCodec *codec = QTextCodec::codecForName(codecName);
//    return codec->toUnicode( ba.constData(), ba.size(), &state);
//}

SaveFile::FutureWatcher SaveFile::runReadFile(const QString &codecName)
{
    QString path(getPath());
    QFile file(path);
    FutureWatcher futureWatcher(READ);
    if(file.open(QIODevice::ReadOnly)){

        QTextStream ts(&file);
        Q_ASSERT(codecName != QLatin1String(""));
        ts.setCodec(codecName.toLatin1());

        futureWatcher._result.setValue<QString>(ts.readAll());

        return futureWatcher;
    }
    futureWatcher._result.setValue<QString>(QString(QLatin1String("error open file %s!")).arg(path));
    return futureWatcher;
}

SaveFile::~SaveFile()
{
    _fileData.clear();
}
