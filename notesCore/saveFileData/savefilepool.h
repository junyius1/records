#ifndef SAVEFILEPOOL_H
#define SAVEFILEPOOL_H

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>
#include "savefile.h"


class SaveFilePool
{
    typedef QHash<QString, QSharedPointer<SaveFile>> SAVE_FILE_MAP;
private:
    SAVE_FILE_MAP _fileReadMap;
    SAVE_FILE_MAP _fileSaveMap;
public:
    SaveFilePool();
    QSharedPointer<SaveFile> getSaveFile(const QString &path);
    bool delFileRead(const QString &path);
    bool delFileSave(const QString &path);
    static SaveFilePool * instance();

private:
    static SaveFilePool *_instance;
};

#endif // SAVEFILEPOOL_H
