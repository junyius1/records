#include "savefilepool.h"

#include <QHash>

SaveFilePool::SaveFilePool()
{

}

QSharedPointer<SaveFile> SaveFilePool::getSaveFile(const QString &fileName)
{
    SAVE_FILE_MAP::iterator it = _saveFileMap.find(fileName);
    if(it == _saveFileMap.end())
    {
        return _saveFileMap[fileName];
    }
    return it.value();
}

bool SaveFilePool::delSaveFile(const QString &fileName)
{
    SAVE_FILE_MAP::iterator it = _saveFileMap.find(fileName);
    if(it == _saveFileMap.end())
    {
        _saveFileMap.erase(it);
        return true;
    }
    return false;
}
