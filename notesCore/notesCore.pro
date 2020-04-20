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
    noteData/notedatapool.h \
    noteData/notemodel.h \
    noteData/notemodeldata.h \
    noteData/notetabitemviewmodel.h \
        notesapp.h \
        mainviewmodel.h \
        drawerviewmodel.h \
        clipboard.h \
        common.h \
    saveFileData/savefile.h \
    saveFileData/savefiledata.h \
    saveFileData/savefilepool.h

SOURCES += \
    configmodel.cpp \
    filesystemmodel.cpp \
    noteData/notedatapool.cpp \
    noteData/notemodel.cpp \
    noteData/notemodeldata.cpp \
    noteData/notetabitemviewmodel.cpp \
        notesapp.cpp \
        mainviewmodel.cpp \
        drawerviewmodel.cpp \
        clipboard.cpp \
        common.cpp \
    saveFileData/savefile.cpp \
    saveFileData/savefilepool.cpp

TRANSLATIONS += notes_core_de.ts \
        notes_core_template.ts

DISTFILES += $$TRANSLATIONS
notesCore.depends += src
