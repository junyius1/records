#ifndef NOTEDATAPOOL_H
#define NOTEDATAPOOL_H

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>
#include "notemodel.h"


class NoteDataPool
{
    typedef QHash<QString, QSharedPointer<NoteModelData>> NOTE_MODEL_DATA_MAP;
private:
    NOTE_MODEL_DATA_MAP _noteModelDataMap;
public:
    NoteDataPool();
    QSharedPointer<NoteModelData> getNoteModelData(const QString &path);
    bool delNoteModelData(const QString &path);
    static NoteDataPool * instance();

private:
    static NoteDataPool *_instance;
};

#endif // NOTEDATAPOOL_H
