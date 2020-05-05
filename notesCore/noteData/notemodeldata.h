#ifndef NOTEMODELDATA_H
#define NOTEMODELDATA_H

#include "saveFileData/savefile.h"

class NoteModelData : public ISaveFileData
{
protected:
    QList<QVariant> _noteData;
    QSharedPointer<SaveFile> _saveNoteData;

public:
    const QString &getCodec()
    {
        return _saveNoteData->getCodec();
    }
    void clear()
    {
        _noteData.clear();
    }
    void addData(const QString &data)
    {
        _noteData.push_back(data);
        _saveNoteData->save();
    }
    NoteModelData(const QString &filePath, const QString &keyword);

    void read(const QString codecName=QLatin1String("UTF-8"))
    {
        _saveNoteData->read(codecName);
    }

    const QList<QVariant> &getCNoteData()
    {
        return _noteData;
    }
    QList<QVariant> &getNoteData()
    {
        return _noteData;
    }
    QSharedPointer<SaveFile> getSaveFile()
    {
        return _saveNoteData;
    }
    ~NoteModelData() override;
};

class LineStringModelData : public NoteModelData
{
public:
    LineStringModelData(const QString &filePath, const QString &keyword):NoteModelData(filePath, keyword)
    {
    }

    void data2QVariant(QVariant &variant) override;
    void qVariant2Data(const QVariant &variant) override;

    ~LineStringModelData() override {}

};

class KWStringModelData : public NoteModelData
{
public:
    KWStringModelData(const QString &filePath, const QString &keyword):NoteModelData(filePath, keyword)
    {
    }

    void data2QVariant(QVariant &variant) override;
    void qVariant2Data(const QVariant &variant) override;

    ~KWStringModelData() override {}

};

#endif // NOTEMODELDATA_H
