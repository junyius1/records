TEMPLATE = subdirs

SUBDIRS += \
        notesCore \
        notesQuick \
        src \
        tests

notesQuick.depends += notesCore src

DISTFILES += .qmake.conf \
        sync.profile
