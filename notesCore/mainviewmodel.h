#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "viewmodel.h"
#include <QtCore/QStringListModel>
#include "filesystemmodel.h"

class MainViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    QTMVVM_SINGLETON

public:
    Q_INVOKABLE explicit MainViewModel(QObject *parent = nullptr);
    ~MainViewModel();
};

class MainTabItemViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString filePath READ filePath CONSTANT)

    QTMVVM_CONTAINER_VM(MainViewModel)
//    QTMVVM_INJECT_PROP(FileSystemModel*, fileSystemModel, _fileSystemModel)
    Q_PROPERTY(FileSystemModel* fileSystemModel READ fileSystemModel NOTIFY fileSystemChanged)

public:
    Q_INVOKABLE explicit MainTabItemViewModel(QObject *parent = nullptr);
    ~MainTabItemViewModel() override;

    QString title() const;
    QString filePath();

Q_SIGNALS:
    void titleChanged(QString title);
    void fileSystemChanged();

protected:
    void onInit(const QVariantHash &params) override;

public:

    Q_INVOKABLE FileSystemModel *fileSystemModel() const;
    Q_INVOKABLE QModelIndex getRootPathIndex(){
        return _fileSystemModel->getRootPathIndex();
    }
    Q_INVOKABLE QString getCurDirectory() const;
private:
    QString _title;
    FileSystemModel *_fileSystemModel;
};

Q_DECLARE_METATYPE(MainViewModel*)

#endif // MAINVIEWMODEL_H
