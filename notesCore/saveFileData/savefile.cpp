#include "savefile.h"
#include "saveFileData/savefilepool.h"
#include <QtConcurrent>

SaveFile::SaveFile(const QString &filePath, const QString &keyword):_readCodec(QLatin1String("UTF-8"))
{
    _path = filePath;
   _keyword = keyword;
   connect(&_futureWatcher, &QFutureWatcher<bool>::finished, this, &SaveFile::onSaveFile);
   connect(&_futureReadWatcher, &QFutureWatcher<QString>::finished, this, &SaveFile::onReadFile);
}

void SaveFile::save(const QSharedPointer<SaveFile> sp)
{
    if(_timer) return;
    _timer = QSharedPointer<QTimer> (
            new QTimer(),
            &QTimer::deleteLater
         );
    SaveFilePool::instance()->addFileSave(getPath(), sp);

    connect(_timer.data(), &QTimer::timeout, this, &SaveFile::timeoutCB);
    _timer->start(50000);
}

void SaveFile::read(const QSharedPointer<SaveFile> sp, const QString codecName)
{
    waitingThread();
    SaveFilePool::instance()->addFileRead(getPath(), sp);
    QFuture<QString> futureRead = QtConcurrent::run(this, &SaveFile::runReadFile, codecName);
    _futureReadWatcher.setFuture(futureRead);
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
    QFuture<bool> future = QtConcurrent::run(this, &SaveFile::runSaveFile, variant);
    _futureWatcher.setFuture(future);
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

//QString GetCorrectUnicode(const QByteArray &ba, const char *codecName)
//{
//    QTextCodec::ConverterState state;
//    QTextCodec *codec = QTextCodec::codecForName(codecName);
//    return codec->toUnicode( ba.constData(), ba.size(), &state);
//}

QString SaveFile::runReadFile(const QString &codecName)
{
    QString path(getPath());
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){

        QTextStream ts(&file);
        Q_ASSERT(codecName != QLatin1String(""));
        ts.setCodec(codecName.toLatin1());

        return ts.readAll();
    }
    return QString(QLatin1String("error open file %s!")).arg(path);
}

SaveFile::~SaveFile()
{
    _fileData.clear();
}
