#include "notetabitemviewmodel.h"
#include "message.h"
#include <QtCore/QDebug>
#include "notemodel.h"
#include "noteData/notedatapool.h"
#include <QDir>


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
    bool isNew = params.value(QStringLiteral("isNew"), false).toBool();
    if(isNew)
    {
        QString filePath = params.value(QStringLiteral("filePath")).toString();

        int i =0;
        QString fileName;
        while(true)
        {
            fileName = QString(QLatin1String("/NEWNOTE%1.kw")).arg(i);
            QFile file( filePath + fileName );
            if(file.exists()) i++;
            else {
                file.open( QIODevice::WriteOnly );
                file.close();
                _title = fileName.mid(1);
                break;
            }
        }
        openNote(filePath+fileName, fileName);
    } else{
        _title = params.value(QStringLiteral("title"), _title).toString();
        openNote(params.value(QStringLiteral("filePath")).toString(), params.value(QStringLiteral("keyword")).toString());
    }
    emit titleChanged(_title);
}

void NoteTabItemViewModel::openNote(const QString &filePath, const QString &keyword)
{
    const QString path = filePath;
    _noteModel = new NoteModel;
    QSharedPointer<NoteModelData> &p = NoteDataPool::instance()->getNoteModelData(path);
    if(p.isNull())
    {
        p.reset(NoteDataPool::createNoteModelData(filePath, keyword));
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
