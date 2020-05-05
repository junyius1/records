#include "savefilepool.h"

#include <QHash>

SaveFilePool *SaveFilePool::_instance = nullptr;
SaveFilePool::SaveFilePool()
{

}


//when add viewModel than register saveFile
bool SaveFilePool::addFileSave(const QString &path, const QSharedPointer<SaveFile> sp)
{
    SaveFileRef sf;
    if(findSaveFile(path, sf))
    {
        sf._count ++;
    } else{
        sf._saveFile = sp;
        _saveFilePool[path] = sf;
    }
    return true;
}


bool SaveFilePool::findSaveFile(const QString &path, SaveFilePool::SaveFileRef& saveFileRef)
{
    SAVE_FILE_MAP::iterator it = _saveFilePool.find(path);
    if(it != _saveFilePool.end())
    {
        saveFileRef = it.value();
        return true;
    }
    return false;
}

bool SaveFilePool::testDelFileSave(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _saveFilePool.find(path);
    if(it != _saveFilePool.end())
    {
        if(it->_count <=0 && it->_saveFile->canDelete())
            _saveFilePool.erase(it);
        return true;
    }
    return false;
}

bool SaveFilePool::delFileSave(const QString &path)
{
    SAVE_FILE_MAP::iterator it = _saveFilePool.find(path);
    if(it != _saveFilePool.end())
    {
        it->_count--;
        if(it->_count <=0 && it->_saveFile->canDelete())
            _saveFilePool.erase(it);
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

SaveFilePool::~SaveFilePool()
{

}

//kill all related file thread when rename dir
bool SaveFilePool::renameDir(const QString &startPath, const QString &endPath)
{
    for(SAVE_FILE_MAP::iterator it = _saveFilePool.begin(); it != _saveFilePool.end(); it++ )
    {
        QString path(it->_saveFile->getPath());
        if(path.contains(startPath))
            it->_saveFile->renamePath(endPath);
    }
    return true;
}

SaveFilePool::FILE_OPR_RESULT SaveFilePool::rename(const QString &startPath, const QString &endPath)
{
    SaveFileRef sf;
    if(findSaveFile(startPath, sf))
    {
        return sf._saveFile->rename(endPath)?FOUND_AND_SUCCESS:FOUND_AND_FAILED;
    } else{
        return NOT_FOUND;
    }
}

SaveFilePool::FILE_OPR_RESULT SaveFilePool::copy(const QString &startPath, const QString &endPath)
{
    SaveFileRef sf;
    if(findSaveFile(startPath, sf))
    {
        return sf._saveFile->copy(endPath)?FOUND_AND_SUCCESS:FOUND_AND_FAILED;
    } else{
        return NOT_FOUND;
    }
}

SaveFilePool::FILE_OPR_RESULT SaveFilePool::remove(const QString &fromPath)
{
    SaveFileRef sf;
    if(findSaveFile(fromPath, sf))
    {
        return sf._saveFile->remove()?FOUND_AND_SUCCESS:FOUND_AND_FAILED;
    } else{
        return NOT_FOUND;
    }
}
