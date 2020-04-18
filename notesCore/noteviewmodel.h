#ifndef NOTESVIEWMODEL_H
#define NOTESVIEWMODEL_H

#include "viewmodel.h"
#include <QStandardItemModel>
#include "notemodel.h"

//note view model
class NoteViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    QTMVVM_SINGLETON

public:
    Q_INVOKABLE explicit NoteViewModel(QObject *parent = nullptr);
    ~NoteViewModel();

public Q_SLOTS:
    void addTab();
};

//note tab
class NoteTabItemViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QStandardItemModel* noteModel READ noteModel CONSTANT)

    QTMVVM_CONTAINER_VM(NoteViewModel)

public:
    Q_INVOKABLE explicit NoteTabItemViewModel(QObject *parent = nullptr);
    ~NoteTabItemViewModel() override;

    QString title() const;

Q_SIGNALS:
    void titleChanged(QString title);

protected:
    void onInit(const QVariantHash &params) override;

public Q_SLOTS:

//    void addData(const QString &data);
    //note item list
    QStandardItemModel *noteModel() const;

private:
    QString _title;
    NoteModel *_noteModel;
};

Q_DECLARE_METATYPE(NoteViewModel*)

#endif // NOTESVIEWMODEL_H
