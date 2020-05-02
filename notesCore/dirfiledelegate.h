#ifndef DIRFILEDELEGATE_H
#define DIRFILEDELEGATE_H

#include <QString>
#include <QObject>

class DirFileDelegate :public QObject
{
    Q_OBJECT
private:
    QString _cachePath;
    enum OperatorType
    {
        CUT=0,
        COPY,
        CUT_DIR,
        COPY_DIR,
    };
    OperatorType _operatorType;

private:
    void copyDir(const QString &startPath, const QString &endPath);
    void __copyDir(const QString &startPath, const QString &endPath);
    void removeDir(const QString &fromPath);

public:
    DirFileDelegate(QObject *parent=nullptr);
    Q_INVOKABLE void startCopy(QString fromPath, bool isDir);
    Q_INVOKABLE void startCut(QString fromPath, bool isDir);
    Q_INVOKABLE void endPaste(QString endPath);
    Q_INVOKABLE void remove(QString fromPath, bool isDir);
    Q_INVOKABLE bool canPaste();

    static DirFileDelegate * instance();

private:
    static DirFileDelegate *_instance;
};

#endif // DIRFILEDELEGATE_H
