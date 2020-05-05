TEMPLATE = app

QT += testlib mvvmcore qml
CONFIG += qmltestcase console
CONFIG -= app_bundle

TARGET = tst_qmlnotescore

SOURCES += \
        tst_qmlnotescore.cpp

DISTFILES += \
        tst_qmlnotescore.qml

importFiles.path = .
DEPLOYMENT += importFiles

win32:msvc:CONFIG(debug, debug|release): CONFIG += disable_testrun
include(../testrun.pri)
