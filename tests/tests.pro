TEMPLATE = subdirs

CONFIG += no_docs_target

SUBDIRS += auto notes

prepareRecursiveTarget(run-tests)
QMAKE_EXTRA_TARGETS += run-tests
