TEMPLATE = subdirs

SUBDIRS += \
        qmlnotescore


prepareRecursiveTarget(run-tests)
QMAKE_EXTRA_TARGETS += run-tests
