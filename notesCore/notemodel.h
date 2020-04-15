#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractItemModel>
#include "saveFileData/savefile.h"

class NoteModelData : public ISaveFileData
{
public:
    NoteModelData()
    {
        QSharedPointer<ISaveFileData> p(this);
        _saveNoteData.setSaveFileData(p);
    }
    QString data2QString() override;
    void qString2Data(const QString &str) override;
    QStringList _noteData;
    SaveFile _saveNoteData;
    ~NoteModelData() override {}
    const QStringList &getCNoteData()
    {
        return _noteData;
    }
    QStringList &getNoteData()
    {
        return _noteData;
    }
};

class NoteModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    static NoteModel * instance();

    explicit NoteModel(QObject *parent = nullptr);
    ~NoteModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;

private:
    static NoteModel *_instance;
    QSharedPointer<NoteModelData> _noteModelData;
};

#endif // NOTEMODEL_H
