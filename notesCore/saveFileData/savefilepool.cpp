#include "savefilepool.h"

#include <QHash>

SaveFilePool *SaveFilePool::_instance = nullptr;
SaveFilePool::SaveFilePool()
{

}

QSharedPointer<SaveFile> SaveFilePool::getSaveFile(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _fileSaveMap.find(path);
    if(it != _fileSaveMap.end())
    {
        return it.value();
    }
    it = _fileReadMap.find(path);
    if(it != _fileReadMap.end())
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

