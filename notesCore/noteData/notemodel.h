#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractItemModel>
#include "saveFileData/savefile.h"
#include "notemodeldata.h"

class NoteModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    explicit NoteModel(QObject *parent = nullptr);
    ~NoteModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    void setNoteModelData(QSharedPointer<NoteModelData> data)
    {
        _noteModelData = data;
    }

private:
    QSharedPointer<NoteModelData> _noteModelData;
};

#endif // NOTEMODEL_H
