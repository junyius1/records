#ifndef SAVEFILEPOOL_H
#define SAVEFILEPOOL_H

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>
#include "savefile.h"


class SaveFilePool
{
    typedef QHash<QString, QSharedPointer<SaveFile>> SAVE_FILE_MAP;
private:
    SAVE_FILE_MAP _saveFileMap;
public:
    SaveFilePool();
    QSharedPointer<SaveFile> getSaveFile(const QString &fileName);
    bool delSaveFile(const QString &fileName);
};

#endif // SAVEFILEPOOL_H
