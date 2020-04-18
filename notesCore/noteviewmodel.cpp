#include "noteviewmodel.h"
#include "message.h"
#include <QtCore/QDebug>
#include "notemodel.h"

NoteViewModel::NoteViewModel(QObject *parent) :
    ViewModel(parent)
{}

NoteViewModel::~NoteViewModel()
{
    qInfo(Q_FUNC_INFO);
}

//add one tab
void NoteViewModel::addTab()
{
    QtMvvm::getInput<QString>(tr("New Tab"), tr("Enter a tab title:"), this, [this](QString res, bool ok) {
        if(ok) {
            show<NoteTabItemViewModel>({
                                       {QStringLiteral("title"), res}
                                   });
        }
    });
}

//添加笔记本的一项记录
//void NotesTabItemViewModel::addData(const QString &data)
//{
//    _noteModel->addData(data);
//}

NoteTabItemViewModel::NoteTabItemViewModel(QObject *parent) :
    ViewModel(parent),
    _title(tr("No Title")),
    _noteModel(NoteModel::instance())
{}

NoteTabItemViewModel::~NoteTabItemViewModel()
{
    qInfo(Q_FUNC_INFO);
}

QString NoteTabItemViewModel::title() const
{
    return _title;
}

void NoteTabItemViewModel::onInit(const QVariantHash &params)
{
    _title = params.value(QStringLiteral("title"), _title).toString();
    emit titleChanged(_title);
}
