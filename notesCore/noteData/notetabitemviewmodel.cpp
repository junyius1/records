#include "notetabitemviewmodel.h"
#include "message.h"
#include <QtCore/QDebug>
#include "notemodel.h"
#include "noteData/notedatapool.h"
//#include "noteData/notemodeldata.h"


void NoteTabItemViewModel::addData(const QString &data)
{
    _noteModel->getNoteModelData()->addData(data);
    _noteModel->reset();
}

NoteTabItemViewModel::NoteTabItemViewModel(QObject *parent) :
    ViewModel(parent),
    _title(tr("No Title")),
    _noteModel(nullptr)
{}

NoteTabItemViewModel::~NoteTabItemViewModel()
{
    qInfo(Q_FUNC_INFO);
    delete _noteModel;
}

NoteModel *NoteTabItemViewModel::noteModel() const
{
    return _noteModel;
}

QString NoteTabItemViewModel::title() const
{
    return _title;
}

void NoteTabItemViewModel::onInit(const QVariantHash &params)
{
    _title = params.value(QStringLiteral("title"), _title).toString();
    openNote(params.value(QStringLiteral("filePath")).toString(), QStringLiteral("")/*params.value(QStringLiteral("keyword")).toString()*/);
    emit titleChanged(_title);
}

void NoteTabItemViewModel::openNote(const QString &filePath, const QString &keyword)
{
    const QString path = filePath + keyword;
    _noteModel = new NoteModel;
    QSharedPointer<NoteModelData> &p = NoteDataPool::instance()->getNoteModelData(path);
    if(p.isNull())
    {
        p.reset(new XmlStringModelData(filePath, keyword));
        const QSharedPointer<SaveFile> saveFile = p->getSaveFile();
        saveFile->setSaveFileData(p);
        connect(saveFile.data(), &SaveFile::onReadFileOK, this, &NoteTabItemViewModel::onReadFileOK);
        _noteModel->setNoteModelData(p);
        p->read();
    } else{
        _noteModel->setNoteModelData(p);
    }
}

void NoteTabItemViewModel::reset()
{
    _noteModel->reset();
}

QString NoteTabItemViewModel::filePath()
{
    return _noteModel->getNoteModelData()->getSaveFile()->getPath();
}

void NoteTabItemViewModel::onReadFileOK()
{
    _noteModel->reset();
    qDebug() << "onReadFileOK()";
}

void NoteTabItemViewModel::setCodec(const QString &codecName)
{
    _noteModel->getNoteModelData()->clear();
    _noteModel->getNoteModelData()->read(codecName);
}

const QString NoteTabItemViewModel::getCodec()
{
   return _noteModel->getNoteModelData()->getCodec();
}
