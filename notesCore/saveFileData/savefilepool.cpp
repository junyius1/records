#include "savefilepool.h"

#include <QHash>

SaveFilePool *SaveFilePool::_instance = nullptr;
SaveFilePool::SaveFilePool()
{

}

QSharedPointer<SaveFile> SaveFilePool::getSaveFile(const QString &path)
{
    QSharedPointer<SaveFile> p = findFileSave(path);
    if(p.isNull())
    {
        return findFileRead(path);
    }
    return p;
}

bool SaveFilePool::addFileRead(const QString &path, SaveFile* saveFile)
{
    QSharedPointer<SaveFile> p = findFileSave(path);
    if(p.isNull())
    {
        _fileReadMap[path] = QSharedPointer<SaveFile>(saveFile);
    }
    return true;
}

bool SaveFilePool::addFileSave(const QString &path, SaveFile* saveFile)
{
    QSharedPointer<SaveFile> p = findFileSave(path);
    if(p.isNull())
    {
        _fileSaveMap[path] = QSharedPointer<SaveFile>(saveFile);
    }
    return true;
}

QSharedPointer<SaveFile> SaveFilePool::findFileRead(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _fileReadMap.find(path);
    if(it != _fileReadMap.end())
    {
        return it.value();
    }
    return nullptr;
}

QSharedPointer<SaveFile> SaveFilePool::findFileSave(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _fileSaveMap.find(path);
    if(it != _fileSaveMap.end())
    {
        return it.value();
    }
    return nullptr;
}

bool SaveFilePool::delFileRead(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _fileReadMap.find(path);
    if(it == _fileReadMap.end())
    {
        _fileReadMap.erase(it);
        return true;
    }
    return false;
}

bool SaveFilePool::delFileSave(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _fileSaveMap.find(path);
    if(it == _fileSaveMap.end())
    {
        _fileSaveMap.erase(it);
        return true;
    }
    return false;
}

SaveFilePool * SaveFilePool::instance()
{
    if(_instance)
    {
        return _instance;
    }

    _instance = new SaveFilePool();
    return _instance;
}

