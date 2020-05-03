#include "notedatapool.h"

#include <QHash>
#include "common.h"

NoteDataPool *NoteDataPool::_instance = nullptr;

NoteDataPool::NoteDataPool()
{

}

QSharedPointer<NoteModelData> &NoteDataPool::getNoteModelData(const QString &path)
{
    NOTE_MODEL_DATA_MAP::iterator it = _noteModelDataMap.find(path);
    if(it == _noteModelDataMap.end())
    {
        return _noteModelDataMap[path];
    }
    return it.value();
}

bool NoteDataPool::delNoteModelData(const QString &path)
{
    NOTE_MODEL_DATA_MAP::iterator it = _noteModelDataMap.find(path);
    if(it == _noteModelDataMap.end())
    {
        _noteModelDataMap.erase(it);
        return true;
    }
    return false;
}

NoteDataPool * NoteDataPool::instance()
{
    if(_instance)
    {
        return _instance;
    }

    _instance = new NoteDataPool();
    return _instance;
}

NoteDataPool::~NoteDataPool()
{
     for(NOTE_MODEL_DATA_MAP::iterator it = _noteModelDataMap.begin(); it != _noteModelDataMap.end(); it++)
     {
         it->clear();
     }
     _noteModelDataMap.clear();
}

NoteModelData* NoteDataPool::createNoteModelData(const QString &filePath, const QString &keyword)
{
    QString kw = notes::getFileNameNoDot(keyword);
    QString suffix = keyword.right(keyword.length() - kw.length() - 1);
    if(suffix == QLatin1String("kw"))
    {
        return new KWStringModelData(filePath, kw);
    } else {
        return new LineStringModelData(filePath, kw);
    }
}
