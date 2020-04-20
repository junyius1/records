#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QObject>
#include <QMap>
#include "saveFileData/savefile.h"

class ConfigModelData : public ISaveFileData
{
public:
    typedef QHash<QLatin1String, QLatin1String> CONFIG_DATA;
    ConfigModelData()
    {
        QSharedPointer<ISaveFileData> p(this);
        _saveNoteData->setSaveFileData(p);
    }
    void data2QVariant(QVariant &variant) override;
    CONFIG_DATA _configData;
    QSharedPointer<SaveFile> _saveNoteData;
    ~ConfigModelData() override {}
    const CONFIG_DATA &getCConfigData()
    {
        return _configData;
    }
    CONFIG_DATA &getConfigData()
    {
        return _configData;
    }
};

class ConfigModel : public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE explicit ConfigModel(QObject *parent = nullptr);

    static ConfigModel * instance();

    //conifgs表的内存结构
    const ConfigModelData::CONFIG_DATA &configsMap() const
    {
        return _configsMap;
    }

    ConfigModelData::CONFIG_DATA _configsMap;//配置key-value映射
    const QLatin1String &getValue(const QLatin1String &key);

    //update current directory
    void updateCurDirectory(const QLatin1String &curDir);

    //update current file
    void updateCurFile(const QLatin1String &curFile);

private:
    static ConfigModel *_instance;
};

#endif // CONFIGMODEL_H
