TEMPLATE = lib

# Creating a static library is typically more efficient. You can still create a shared library if you want to
CONFIG += c++14 static

QT += widgets concurrent

TARGET = notesCore

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../src/mvvmcore

HEADERS += \
    common.h \
    configmodel.h \
    filesystemmodel.h \
    notemodel.h \
        notesapp.h \
        mainviewmodel.h \
        drawerviewmodel.h \
        clipboard.h \
        #initdb.h \
        common.h \
    noteviewmodel.h \
    saveFileData/savefile.h \
    saveFileData/savefiledata.h \
    saveFileData/savefilepool.h

SOURCES += \
    configmodel.cpp \
    filesystemmodel.cpp \
    notemodel.cpp \
        notesapp.cpp \
        mainviewmodel.cpp \
        drawerviewmodel.cpp \
        clipboard.cpp \
        #initdb.cpp \
        noteviewmodel.cpp \
        common.cpp \
    saveFileData/savefile.cpp \
    saveFileData/savefilepool.cpp

TRANSLATIONS += notes_core_de.ts \
        notes_core_template.ts

DISTFILES += $$TRANSLATIONS
notesCore.depends += src
