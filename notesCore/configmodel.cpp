#include "configmodel.h"

ConfigModel *ConfigModel::_instance = nullptr;
QString ConfigModelData::data2QString()
{
    QString ret;
    for(CONFIG_DATA::iterator it = _configData.begin(); it != _configData.end(); it++)
    {
        ret += it.key();
        ret.arg(':');
        ret += it.value();
        ret.arg('\n');
    }
    return ret;
}

ConfigModel::ConfigModel(QObject *parent)
{
    updateCurDirectory(QLatin1String("C:"));
}

const QLatin1String &ConfigModel::getValue(const QLatin1String &key)
{
    return _configsMap[key];
}

//update current directory
void ConfigModel::updateCurDirectory(const QLatin1String &curDir)
{
    _configsMap[QLatin1String("CUR_DIR")] = curDir;
}

//update current file
void ConfigModel::updateCurFile(const QLatin1String &curFile)
{
    _configsMap[QLatin1String("CUR_FILE")] = curFile;
}

ConfigModel * ConfigModel::instance()
{
    if(_instance)
    {
        return _instance;
    }

    _instance = new ConfigModel();
    return _instance;
}
