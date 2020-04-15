#include "notemodel.h"

NoteModel *NoteModel::_instance = nullptr;
QString NoteModelData::data2QString()
{
    return _noteData.join('\n');
}

void NoteModelData::qString2Data(const QString &str)
{
    _noteData = str.split('\n');
}

NoteModel::NoteModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

NoteModel::~NoteModel()
{
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    return _noteModelData && !parent.isValid() ? _noteModelData->getCNoteData().size() : 0;
}

int NoteModel::columnCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? ColumnCount : 0;
}

QModelIndex NoteModel::index(int row, int column, const QModelIndex &parent) const
{
    return _noteModelData && !parent.isValid()
            && row >= 0 && row < _noteModelData->getCNoteData().size()
            && column >= 0 && column < ColumnCount
        ? createIndex(row, column)
        : QModelIndex();
}

QModelIndex NoteModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)

    return QModelIndex();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole && _noteModelData) {
        QVariant value = _noteModelData->getCNoteData().at(index.row());
        if (!value.isValid() && index.column() == Title) {
            return value;
        }

        return value;
    }
    return QVariant();
}

bool NoteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(_noteModelData){
        _noteModelData->getNoteData()[index.row()] = value.toString();
        emit dataChanged(index, index);
        return true;
    } return false;
}

NoteModel * NoteModel::instance()
{
    if(_instance)
    {
        return _instance;
    }

    _instance = new NoteModel();
    return _instance;
}
