#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent):
_configModel(ConfigModel::instance())
{
    qDebug() << "currentPath=" << QDir::currentPath();
    setRootPath(_configModel->getValue(QLatin1String("CUR_DIR")));
//    connect(this, &QFileSystemModel::directoryLoaded, this, &FileSystemModel::onDirectoryLoaded);
}

//void FileSystemModel::onDirectoryLoaded(const QString &path)
//{
//    qDebug() << "new path: " << path;
//}

QModelIndex FileSystemModel::getRootPathIndex()
{
    return index(_configModel->getValue(QLatin1String("CUR_DIR")));
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
