#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H
#include <QFileSystemModel>
#include <QDebug>
#include "configmodel.h"
#include "serviceregistry.h"

class FileSystemModel : public QFileSystemModel
{
    Q_OBJECT
    QTMVVM_INJECT(ConfigModel*, configModel)
public:
        enum Roles {
            FileIsDir = 2 * Qt::UserRole
        };

    Q_ENUM(Roles)

    Q_INVOKABLE explicit FileSystemModel(QObject *parent = nullptr);

    //switch note file
    void changeNoteFile(const QLatin1String &noteFile);
    void changeDirectory(const QLatin1String &dir);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override
    {
         QHash<int, QByteArray> result = QFileSystemModel::roleNames();
         result.insert(FileIsDir, QByteArrayLiteral("fileIsDir"));
         return result;
    }

    QModelIndex getRootPathIndex();

//public Q_SLOTS:
//    void onDirectoryLoaded(const QString &path);

private:
    ConfigModel* _configModel;
};

#endif // FILESYSTEMMODEL_H
