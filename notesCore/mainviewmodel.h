#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "viewmodel.h"
#include <QtCore/QStringListModel>
#include "filesystemmodel.h"

//notes（记事本）的viewmodel
class MainViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

//    QTMVVM_SINGLETON

public:
    Q_INVOKABLE explicit MainViewModel(QObject *parent = nullptr);
    ~MainViewModel();

public Q_SLOTS:
    void addTab();
};

//notes（记事本）的tab 的viewmodel（暂时只有一个tab）
class MainTabItemViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

    QTMVVM_CONTAINER_VM(MainViewModel)
//    QTMVVM_INJECT_PROP(FileSystemModel*, fileSystemModel, _fileSystemModel)
    Q_PROPERTY(FileSystemModel* fileSystemModel READ fileSystemModel NOTIFY fileSystemChanged)

public:
    Q_INVOKABLE explicit MainTabItemViewModel(QObject *parent = nullptr);
    ~MainTabItemViewModel() override;

    QString title() const;

Q_SIGNALS:
    void titleChanged(QString title);
    void fileSystemChanged();

protected:
    void onInit(const QVariantHash &params) override;

public Q_SLOTS:
    //note（记事本）触发添加对话框后点击确定触发添加item
//    void addData(const QString &data);
    //这个是note（记事本）的文件列表
    FileSystemModel *fileSystemModel() const;
    QModelIndex getRootPathIndex(){
        return _fileSystemModel->getRootPathIndex();
    }
private:
    QString _title;
    FileSystemModel *_fileSystemModel;
};

Q_DECLARE_METATYPE(MainViewModel*)

#endif // MAINVIEWMODEL_H
