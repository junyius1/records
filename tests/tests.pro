TEMPLATE = subdirs

CONFIG += no_docs_target

SUBDIRS += auto notes qml_notes

prepareRecursiveTarget(run-tests)
QMAKE_EXTRA_TARGETS += run-tests
