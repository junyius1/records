#ifndef SAVEFILEPOOL_H
#define SAVEFILEPOOL_H

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>
#include "savefile.h"


class SaveFilePool
{
    struct SaveFileRef
    {
        SaveFileRef():_count(0),_saveFile(nullptr)
        {
        }
//        SaveFileRef(long count, const QSharedPointer<SaveFile>& sp):_count(count),_saveFile(sp)
//        {
//        }
        long _count;
        QSharedPointer<SaveFile> _saveFile;
    };

    typedef QHash<QString, SaveFileRef> SAVE_FILE_MAP;
private:

    SAVE_FILE_MAP _saveFilePool;
public:
    SaveFilePool();
    bool delFileSave(const QString &path);
    bool testDelFileSave(const QString &path);

    bool addProcessTask(const QString &path, const QSharedPointer<SaveFile> sp);
    bool addFileSave(const QString &path, const QSharedPointer<SaveFile> sp);

    bool findSaveFile(const QString &path, SaveFilePool::SaveFileRef& saveFileRef);

    static SaveFilePool * instance();
    ~SaveFilePool();

    enum FILE_OPR_RESULT
    {
        NOT_FOUND=0,
        FOUND_AND_FAILED,
        FOUND_AND_SUCCESS
    };

    FILE_OPR_RESULT copy(const QString &startPath, const QString &endPath);
    FILE_OPR_RESULT remove(const QString &fromPath);
    FILE_OPR_RESULT rename(const QString &startPath, const QString &endPath);
    bool renameDir(const QString &startPath, const QString &endPath);

private:
    static SaveFilePool *_instance;
};

#endif // SAVEFILEPOOL_H
