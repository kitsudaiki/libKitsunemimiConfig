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
class ConfigHandler_Test;

enum ConfigType
{
    UNDEFINED_TYPE,
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

    // register config-options
    bool registerString(const std::string &group,
                        const std::string &key,
                        const std::string &defaultValue);
    bool registerInteger(const std::string &group,
                         const std::string &key,
                         const long defaultValue);
    bool registerFloat(const std::string &group,
                       const std::string &key,
                       const double defaultValue);
    bool registerBoolean(const std::string &group,
                         const std::string &key,
                         const bool defaultValue);
    bool registerStringArray(const std::string &group,
                             const std::string &key,
                             const std::vector<std::string> &defaultValue);

    // getter
    const std::string getString(const std::string &group,
                                const std::string &key,
                                bool &success);
    long getInteger(const std::string &group,
                    const std::string &key,
                    bool &success);
    double getFloat(const std::string &group,
                    const std::string &key,
                    bool &success);
    bool getBoolean(const std::string &group,
                    const std::string &key,
                    bool &success);
    const std::vector<std::string> getStringArray(const std::string &group,
                                                  const std::string &key,
                                                  bool &success);


private:
    friend ConfigHandler_Test;

    bool checkType(const std::string &group,
                   const std::string &key,
                   const ConfigType type);
    bool isRegistered(const std::string &group,
                      const std::string &key);
    bool registerType(const std::string &group,
                      const std::string &key,
                      const ConfigType type);
    ConfigType getRegisteredType(const std::string &group,
                                 const std::string &key);

    std::string m_configFilePath = "";
    Ini::IniItem* m_iniItem = nullptr;
    std::map<std::string, std::map<std::string, ConfigType>> m_registeredConfigs;
};

}
}

#endif // CONFIG_HANDLER_H
