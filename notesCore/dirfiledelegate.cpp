#include "dirfiledelegate.h"
#include <QFile>
#include <QDir>
#include "saveFileData/savefilepool.h"

DirFileDelegate *DirFileDelegate::_instance = nullptr;

DirFileDelegate::DirFileDelegate(QObject *parent):QObject(parent),_cachePath(QLatin1String(""))
{

}

bool DirFileDelegate::rename(const QString &startPath, const QString &endPath)
{
    SaveFilePool::FILE_OPR_RESULT result = SaveFilePool::instance()->rename(startPath, endPath);
    if(result == SaveFilePool::FILE_OPR_RESULT::NOT_FOUND)
    {
        return QFile::rename(startPath, endPath);
    }
    return result == SaveFilePool::FILE_OPR_RESULT::FOUND_AND_SUCCESS;
}

bool DirFileDelegate::copy(const QString &startPath, const QString &endPath)
{
    SaveFilePool::FILE_OPR_RESULT result = SaveFilePool::instance()->copy(startPath, endPath);
    if(result == SaveFilePool::FILE_OPR_RESULT::NOT_FOUND)
    {
        return QFile::copy(startPath, endPath);
    }
    return result == SaveFilePool::FILE_OPR_RESULT::FOUND_AND_SUCCESS;
}

bool DirFileDelegate::remove(const QString &fromPath)
{
    SaveFilePool::FILE_OPR_RESULT result = SaveFilePool::instance()->remove(fromPath);
    if(result == SaveFilePool::FILE_OPR_RESULT::NOT_FOUND)
    {
        return QFile::remove(fromPath);
    }
    return result == SaveFilePool::FILE_OPR_RESULT::FOUND_AND_SUCCESS;
}

bool DirFileDelegate::canPaste()
{
    return _cachePath != QLatin1String("") && !isRename();
}

bool DirFileDelegate::isRename()
{
    return RENAME == _operatorType || RENAME_DIR == _operatorType;
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

void DirFileDelegate::startRename(QString fromPath, bool isDir)
{
    _cachePath = fromPath;
    _operatorType = isDir?RENAME_DIR:RENAME;
}

void DirFileDelegate::__removeDir(const QString &fromPath)
{
    QDir dir(fromPath);
    if (! dir.exists())
        return;
    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = fromPath + QDir::separator() + d;
        __removeDir(dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        remove(fromPath + QDir::separator() + f);
    }

    dir.rmdir(fromPath);
}

void DirFileDelegate::removeDir(const QString &fromPath)
{
    __removeDir(fromPath);
    emit delFileOrDir(fromPath);
}

void DirFileDelegate::remove(QString fromPath, bool isDir)
{
    if(isDir)
    {
        removeDir(fromPath);
    } else{
        remove(fromPath);
        emit delFileOrDir(fromPath);
    }
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
        if(!copy(_cachePath, endPath+fileName))
        {
            int i =0;
            while(true)
            {
                QString copyName(genCopyName(fileName, i));
                if(copy(_cachePath, endPath+copyName)) break;
                else i++;
            }
        }
    } else if(_operatorType==CUT)
    {
        QString fileName = getFileName(_cachePath);
        if(!rename(_cachePath, endPath+fileName))
        {
            int i =0;
            while(true)
            {
                QString copyName(genCopyName(fileName, i));
                if(rename(_cachePath, endPath+copyName)) break;
                else i++;
            }
        }
    } else if(_operatorType == COPY_DIR)
    {
        copyDir(_cachePath, endPath);
    } else if(_operatorType == CUT_DIR)
    {
//        copyDir(_cachePath, endPath);
//        removeDir(_cachePath);
        QDir dir(_cachePath);
        if (! dir.exists())
            return;
        SaveFilePool::instance()->renameDir(_cachePath, endPath);
        dir.rename(_cachePath, endPath);
    }else if(_operatorType == RENAME)
    {
        rename(_cachePath, endPath);
    } else if(_operatorType == RENAME_DIR)
    {
        QDir dir(_cachePath);
        if (! dir.exists())
            return;
        SaveFilePool::instance()->renameDir(_cachePath, endPath);
        dir.rename(_cachePath, endPath);
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
    QLatin1Char separator('/');

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = endPath + separator + d;
        dir.mkpath(dst_path);
        __copyDir(startPath + separator + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        copy(startPath + separator + f, endPath + separator + f);
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
