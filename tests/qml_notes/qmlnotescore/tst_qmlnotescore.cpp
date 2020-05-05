/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt OPC UA module.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtQuickTest/quicktest.h>
#include <QObject>
#include <QProcess>
#include <QQmlContext>
#include <QQmlEngine>
#include <QTcpServer>
#include <QTcpSocket>

#include <QSignalSpy>

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <notesapp.h>
#include <mainviewmodel.h>

#include <drawerviewmodel.h>
#include "noteData/notetabitemviewmodel.h"
#include "quickpresenter.h"
#include "clipboard.h"
#include <QQmlContext>
#include "dirfiledelegate.h"
#include "common.h"

QTMVVM_REGISTER_CORE_APP(notesApp)

using namespace notes;

class TestCppClass : public QObject
{
    Q_OBJECT

public:
    TestCppClass (QObject* parent = nullptr) : QObject(parent) {
    }



signals:


public slots:
    void startConnection() {

    }
};

class SetupClass : public QObject
{
    Q_OBJECT
public:
    SetupClass() {
    }
    ~SetupClass() {
    }

public slots:

    void applicationAvailable() {
        QTest::qWait(2500);
    }

    void qmlEngineAvailable(QQmlEngine *engine) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        // If you want to support file dialogs on platforms other then android, use a QApplication instead (and add QT += widgets to the pro file)
//        QGuiApplication app(argc, argv);
        char url[] = "com.cross.notes";

    //    QtMvvm::ServiceRegistry::instance()->registerObject<FileSystemModel>(QtMvvm::ServiceRegistry::DestroyOnAppDestroy, true);
    //    QtMvvm::ServiceRegistry::instance()->registerObject<ConfigModel>(QtMvvm::ServiceRegistry::DestroyOnAppDestroy, true);

        QtMvvm::QuickPresenter::getInputViewFactory(); //Workaround for QTBUG-69963
        qmlRegisterUncreatableType<MainViewModel>(url, 1, 1, "MainViewModel", QStringLiteral("MainViewModel cannot be created!"));
        qmlRegisterUncreatableType<MainTabItemViewModel>(url, 1, 1, "MainTabItemViewModel", QStringLiteral("MainTabItemViewModel cannot be created!"));
        qmlRegisterUncreatableType<DrawerViewModel>(url, 1, 1, "DrawerViewModel", QStringLiteral("DrawerViewModel cannot be created"));
        qmlRegisterUncreatableType<NoteTabItemViewModel>(url, 1, 1, "NoteTabItemViewModel", QStringLiteral("NoteTabItemViewModel cannot be created"));

        qmlRegisterType<Clipboard>(url,1,0,"Clipboard");

        engine->addImportPath((QStringLiteral("../qml")));
        engine->rootContext()->setContextProperty(QLatin1String("dirFileDelegate"), DirFileDelegate::instance());
//        engine->load(QUrl(QStringLiteral("qrc:/App.qml")));

    //    g_qmlEngine = &engine;

        qmlRegisterType<TestCppClass>("App", 1, 0, "TestCppClass");

//        CoreApp::instance()show<MainTabItemViewModel>({
//                                       {QStringLiteral("title"), QStringLiteral("Root Tab")}
//                                   });
//        CoreApp::instance()show<DrawerViewModel>();
    }
    void cleanupTestCase() {
//        if (m_serverProcess.state() == QProcess::Running) {
//            m_serverProcess.kill();
//            m_serverProcess.waitForFinished(2000);
//        }
    }
private:
//    QProcess m_serverProcess;
//    QString m_testServerPath;
//    QString m_opcuaDiscoveryUrl;
};

QUICK_TEST_MAIN_WITH_SETUP(qmlnotescore, SetupClass)

#include "tst_qmlnotescore.moc"
