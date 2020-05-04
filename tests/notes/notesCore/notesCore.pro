TEMPLATE = subdirs

SUBDIRS += \
        notesapp


prepareRecursiveTarget(run-tests)
QMAKE_EXTRA_TARGETS += run-tests
