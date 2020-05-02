#include "dirfiledelegate.h"
#include <QFile>
#include <QDir>

DirFileDelegate *DirFileDelegate::_instance = nullptr;

DirFileDelegate::DirFileDelegate(QObject *parent):QObject(parent),_cachePath(QLatin1String(""))
{

}

bool DirFileDelegate::canPaste()
{
    return _cachePath != QLatin1String("");
}

void DirFileDelegate::startCopy(QString fromPath, bool isDir)
{
    _cachePath = fromPath;
    _operatorType = isDir?COPY_DIR:COPY;
}

void DirFileDelegate::startCut(QString fromPath, bool isDir)
{
    _cachePath = fromPath;
    _operatorType = isDir?CUT_DIR:CUT;
}

void DirFileDelegate::removeDir(const QString &fromPath)
{
    QDir dir(fromPath);
    if (! dir.exists())
        return;
    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = fromPath + QDir::separator() + d;
        removeDir(dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::remove(fromPath + QDir::separator() + f);
    }

    dir.rmdir(fromPath);
}

void DirFileDelegate::remove(QString fromPath, bool isDir)
{
    if(isDir)
    {
        removeDir(fromPath);
    } else
        QFile::remove(fromPath);
}

QString genCopyName(const QString &str, int i)
{
    int dot = str.lastIndexOf('.');
    if(dot==-1)
    {
        return QString(QLatin1String("%1(%2)")).arg(str).arg(i);
    }
    QString pathNoDot = str.mid(0, dot);
    return QString(QLatin1String("%1(%2)%3")).arg(pathNoDot).arg(i).arg(str.right(str.length()-dot));
}

QString getFileName(const QString &filePath)
{
    int index = filePath.lastIndexOf('/');
    return filePath.right(filePath.length() - index);
}

void DirFileDelegate::endPaste(QString endPath)
{
    if(_operatorType==COPY)
    {
        QString fileName = getFileName(_cachePath);
        if(!QFile::copy(_cachePath, endPath+fileName))
        {
            int i =0;
            while(true)
            {
                QString copyName(genCopyName(fileName, i));
                if(QFile::copy(_cachePath, endPath+copyName)) break;
                else i++;
            }
        }
    } else if(_operatorType==CUT)
    {
        QString fileName = getFileName(_cachePath);
        if(!QFile::rename(_cachePath, endPath+fileName))
        {
            int i =0;
            while(true)
            {
                QString copyName(genCopyName(fileName, i));
                if(QFile::rename(_cachePath, endPath+copyName)) break;
                else i++;
            }
        }
    } else if(_operatorType == COPY_DIR)
    {
        copyDir(_cachePath, endPath);
    } else if(_operatorType == CUT_DIR)
    {
        copyDir(_cachePath, endPath);
        removeDir(_cachePath);
    }
    _cachePath = QLatin1String("");
}

QString getPath(const QString &filePath)
{
    int index = filePath.lastIndexOf('/');
    return filePath.left(index);
}

QString getDirName(const QString &filePath)
{
    int index = filePath.lastIndexOf('/');
    return filePath.right(filePath.length() - index -1);
}

QString genDirName(const QString &str, int i)
{
    return QString(QLatin1String("%1(%2)")).arg(str).arg(i);
}

void DirFileDelegate::copyDir(const QString &startPath, const QString &endPath)
{
    QDir dir(endPath);
    if (! dir.exists())
        return;
    QString endDirPathName(QLatin1String(""));

    if(getPath(startPath) == endPath)
    {
        QString copyDir(getDirName(startPath));
        int i =0;
        while(true)
        {
            QString copyName(genDirName(copyDir, i));
            if(dir.mkdir(copyName)) {
                endDirPathName = copyName;
                break;
            }
            else i++;
        }
    }
    __copyDir(startPath, endPath +QDir::separator()+ endDirPathName);
}

void DirFileDelegate::__copyDir(const QString &startPath, const QString &endPath)
{
    QDir dir(startPath);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = endPath + QDir::separator() + d;
        dir.mkpath(dst_path);
        __copyDir(startPath + QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(startPath + QDir::separator() + f, endPath + QDir::separator() + f);
    }
}

DirFileDelegate * DirFileDelegate::instance()
{
    if(_instance)
    {
        return _instance;
    }

    _instance = new DirFileDelegate();
    return _instance;
}
