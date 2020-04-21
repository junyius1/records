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

    bool addFileRead(const QString &path, SaveFile* saveFile);
    bool addFileSave(const QString &path, SaveFile* saveFile);

    QSharedPointer<SaveFile> findFileRead(const QString &path);
    QSharedPointer<SaveFile> findFileSave(const QString &path);
    static SaveFilePool * instance();
    ~SaveFilePool();

private:
    static SaveFilePool *_instance;
};

#endif // SAVEFILEPOOL_H
