/**
 *  @file       config_handler.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <iostream>
#include <vector>
#include <map>

#define REGISTER_STRING_CONFIG Kitsunemimi::Config::registerString
#define REGISTER_INT_CONFIG Kitsunemimi::Config::registerInteger
#define REGISTER_FLOAT_CONFIG Kitsunemimi::Config::registerFloat
#define REGISTER_BOOL_CONFIG Kitsunemimi::Config::registerBoolean
#define REGISTER_STRING_ARRAY_CONFIG Kitsunemimi::Config::registerStringArray

#define GET_STRING_CONFIG Kitsunemimi::Config::getString
#define GET_INT_CONFIG Kitsunemimi::Config::getInteger
#define GET_FLOAT_CONFIG Kitsunemimi::Config::getFloat
#define GET_BOOL_CONFIG Kitsunemimi::Config::getBoolean
#define GET_STRING_ARRAY_CONFIG Kitsunemimi::Config::getStringArray

namespace Kitsunemimi
{
class DataItem;
namespace Ini {
class IniItem;
}
namespace Config
{
class ConfigHandler_Test;

bool initConfig(const std::string &configFilePath);
void resetConfig();

// register config-options
bool registerString(const std::string &groupName,
                    const std::string &itemName,
                    const std::string &defaultValue);
bool registerInteger(const std::string &groupName,
                     const std::string &itemName,
                     const long defaultValue);
bool registerFloat(const std::string &groupName,
                   const std::string &itemName,
                   const double defaultValue);
bool registerBoolean(const std::string &groupName,
                     const std::string &itemName,
                     const bool defaultValue);
bool registerStringArray(const std::string &groupName,
                         const std::string &itemName,
                         const std::vector<std::string> &defaultValue);

// getter
const std::string getString(const std::string &groupName,
                            const std::string &itemName,
                            bool &success);
long getInteger(const std::string &groupName,
                const std::string &itemName,
                bool &success);
double getFloat(const std::string &groupName,
                const std::string &itemName,
                bool &success);
bool getBoolean(const std::string &groupName,
                const std::string &itemName,
                bool &success);
const std::vector<std::string> getStringArray(const std::string &groupName,
                                              const std::string &itemName,
                                              bool &success);

//==================================================================================================

class ConfigHandler
{
public:
    ConfigHandler();
    ~ConfigHandler();

    bool initConfig(const std::string &configFilePath);

    // register config-options
    bool registerString(const std::string &groupName,
                        const std::string &itemName,
                        const std::string &defaultValue);
    bool registerInteger(const std::string &groupName,
                         const std::string &itemName,
                         const long defaultValue);
    bool registerFloat(const std::string &groupName,
                       const std::string &itemName,
                       const double defaultValue);
    bool registerBoolean(const std::string &groupName,
                         const std::string &itemName,
                         const bool defaultValue);
    bool registerStringArray(const std::string &groupName,
                             const std::string &itemName,
                             const std::vector<std::string> &defaultValue);

    // getter
    const std::string getString(const std::string &groupName,
                                const std::string &itemName,
                                bool &success);
    long getInteger(const std::string &groupName,
                    const std::string &itemName,
                    bool &success);
    double getFloat(const std::string &groupName,
                    const std::string &itemName,
                    bool &success);
    bool getBoolean(const std::string &groupName,
                    const std::string &itemName,
                    bool &success);
    const std::vector<std::string> getStringArray(const std::string &groupName,
                                                  const std::string &itemName,
                                                  bool &success);

    static Kitsunemimi::Config::ConfigHandler* m_config;

private:
    friend ConfigHandler_Test;

    enum ConfigType
    {
        UNDEFINED_TYPE,
        STRING_TYPE,
        INT_TYPE,
        FLOAT_TYPE,
        BOOL_TYPE,
        STRING_ARRAY_TYPE
    };

    bool checkType(const std::string &groupName,
                   const std::string &itemName,
                   const ConfigType type);
    bool isRegistered(const std::string &groupName,
                      const std::string &itemName);
    bool registerType(const std::string &groupName,
                      const std::string &itemName,
                      const ConfigType type);
    ConfigType getRegisteredType(const std::string &groupName,
                                 const std::string &itemName);

    std::string m_configFilePath = "";
    Ini::IniItem* m_iniItem = nullptr;
    std::map<std::string, std::map<std::string, ConfigType>> m_registeredConfigs;
};

}
}

#endif // CONFIG_HANDLER_H
