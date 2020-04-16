#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(const QString &path, QObject *parent):
_configModel(ConfigModel::instance())
{
    qDebug() << "currentPath=" << path;
    setRootPath(path);
//    connect(this, &QFileSystemModel::directoryLoaded, this, &FileSystemModel::onDirectoryLoaded);
}

//void FileSystemModel::onDirectoryLoaded(const QString &path)
//{
//    qDebug() << "new path: " << path;
//}

QModelIndex FileSystemModel::getRootPathIndex()
{
    return index(rootPath());
}

void FileSystemModel::changeNoteFile(const QLatin1String &noteFile)
{
    _configModel->updateCurFile(noteFile);
}

void FileSystemModel::changeDirectory(const QLatin1String &dir)
{
    _configModel->updateCurDirectory(dir);
}

/*!
    \reimp
*/
QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.model() != this)
        return QVariant();

    switch (role) {
    case FileIsDir:
        return isDir(index);
    }

    return QFileSystemModel::data(index, role);
}
