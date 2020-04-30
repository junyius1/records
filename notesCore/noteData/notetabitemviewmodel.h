#ifndef NOTETABITEMVIEWMODEL_H
#define NOTETABITEMVIEWMODEL_H

#include "viewmodel.h"
#include "notemodel.h"


//note tab
class NoteTabItemViewModel : public QtMvvm::ViewModel
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(NoteModel* noteModel READ noteModel CONSTANT)

    QTMVVM_CONTAINER_VM(MainViewModel)

public:
    Q_INVOKABLE explicit NoteTabItemViewModel(QObject *parent = nullptr);
    ~NoteTabItemViewModel() override;

    QString title() const;

Q_SIGNALS:
    void titleChanged(QString title);

protected:
    void onInit(const QVariantHash &params) override;
    void openNote(const QString &filePath, const QString &keyword);

public Q_SLOTS:

    void onReadFileOK();
public:
    //note item list
    Q_INVOKABLE NoteModel *noteModel() const;
    Q_INVOKABLE void setCodec(const QString &codecName);
    Q_INVOKABLE const QString getCodec();
    Q_INVOKABLE void addData(const QString &data);
    Q_INVOKABLE void reset();
private:
    QString _title;
    NoteModel *_noteModel;
};

#endif // NOTETABITEMVIEWMODEL_H
