#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <iostream>
#include <vector>
#include <map>

namespace Kitsunemimi
{
class DataItem;
namespace Ini {
class IniItem;
}
namespace Config
{

enum ConfigType
{
    STRING_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
    BOOL_TYPE,
    STRING_ARRAY_TYPE
};

class ConfigHandler
{
public:
    ConfigHandler();
    ~ConfigHandler();

    bool readConfig(const std::string &configFilePath);

    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const char* &defaultValue);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const std::string &defaultValue);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const long defaultValue);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const double defaultValue);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const bool defaultValue);
    bool registerConfig(const std::string &group,
                        const std::string &key,
                        const ConfigType type,
                        const std::vector<std::string> &defaultValue);

private:
    bool checkType(const std::string &group,
                   const std::string &key,
                   const ConfigType type);
    bool isRegistered(const std::string &group,
                      const std::string &key);
    bool registerType(const std::string &group,
                      const std::string &key,
                      const ConfigType type);

    std::string m_configFilePath = "";
    Ini::IniItem* m_iniItem = nullptr;
    std::map<std::string, std::map<std::string, ConfigType>> m_registeredConfigs;
};

}
}

#endif // CONFIG_HANDLER_H
