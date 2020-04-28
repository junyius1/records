#ifndef NOTEMODELDATA_H
#define NOTEMODELDATA_H

#include "saveFileData/savefile.h"

class NoteModelData : public ISaveFileData
{
protected:
    QList<QVariant> _noteData;
    QSharedPointer<SaveFile> _saveNoteData;

public:
    void clear()
    {
        _noteData.clear();
    }
    NoteModelData(const QString &filePath, const QString &keyword)
    {
        _saveNoteData.reset(new SaveFile(filePath, keyword));
    }

    void read(const QString codecName=QLatin1String(""))
    {
        _saveNoteData->read(_saveNoteData, codecName);
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
    ~NoteModelData() override {
        _saveNoteData.clear();
    }
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

class XmlStringModelData : public NoteModelData
{
public:
    XmlStringModelData(const QString &filePath, const QString &keyword):NoteModelData(filePath, keyword)
    {
    }

    void data2QVariant(QVariant &variant) override;
    void qVariant2Data(const QVariant &variant) override;

    ~XmlStringModelData() override {}

};

#endif // NOTEMODELDATA_H
