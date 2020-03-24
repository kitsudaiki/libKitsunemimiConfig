#include <libKitsunemimiConfig/config_handler.h>

#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiPersistence/files/text_file.h>
#include <libKitsunemimiPersistence/logger/logger.h>
#include <libKitsunemimiIni/ini_item.h>

namespace Kitsunemimi
{
namespace Config
{

/**
 * @brief ConfigHandler::ConfigHandler
 */
ConfigHandler::ConfigHandler() {}

/**
 * @brief ConfigHandler::~ConfigHandler
 */
ConfigHandler::~ConfigHandler()
{
    delete m_iniItem;
}

/**
 * @brief ConfigHandler::readConfig
 * @param configFilePath
 * @param errorMessage
 * @return
 */
bool ConfigHandler::readConfig(const std::string &configFilePath)
{
    std::string errorMessage = "";

    // read file
    m_configFilePath = configFilePath;
    const std::pair<bool, std::string> ret = Persistence::readFile(m_configFilePath, errorMessage);
    if(ret.first == false)
    {
        LOG_ERROR("Error while reding config-file " + configFilePath);
        LOG_ERROR("   " + errorMessage);
        return false;
    }

    // parse file content
    m_iniItem = new Ini::IniItem();
    bool result = m_iniItem->parse(ret.second, errorMessage);
    if(result == false)
    {
        LOG_ERROR("Error while reding config-file " + configFilePath);
        LOG_ERROR("   " + errorMessage);
        return false;
    }

    return true;
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type)
{
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, std::string(""));
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const char *&defaultValue)
{
    if(type != ConfigType::STRING_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const std::string &defaultValue)
{
    if(type != ConfigType::STRING_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const long defaultValue)
{
    if(type != ConfigType::INT_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const double defaultValue)
{
    if(type != ConfigType::FLOAT_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const bool defaultValue)
{
    if(type != ConfigType::BOOL_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::registerConfig
 * @param group
 * @param key
 * @param type
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerConfig(const std::string &group,
                              const std::string &key,
                              const ConfigType type,
                              const std::vector<std::string> &defaultValue)
{
    if(type != ConfigType::STRING_ARRAY_TYPE) {
        return false;
    }
    if(checkType(group, key, type) == false) {
        return false;
    }
    if(registerType(group, key, type) == false) {
        return false;
    }
    return m_iniItem->set(group, key, defaultValue);
}

/**
 * @brief ConfigHandler::checkType
 * @param group
 * @param key
 * @param type
 * @return
 */
bool
ConfigHandler::checkType(const std::string &group,
                         const std::string &key,
                         const ConfigType type)
{
    DataItem* currentItem = m_iniItem->get(group, key);
    if(currentItem == nullptr) {
        return true;
    }

    if(currentItem->getType() == DataItem::ARRAY_TYPE
            && type == ConfigType::STRING_ARRAY_TYPE)
    {
        return true;
    }

    if(currentItem->getType() == DataItem::VALUE_TYPE)
    {
        DataValue* value = currentItem->toValue();

        if(value->getValueType() == DataValue::STRING_TYPE
                && type == ConfigType::STRING_TYPE)
        {
            return true;
        }

        if(value->getValueType() == DataValue::INT_TYPE
                && type == ConfigType::INT_TYPE)
        {
            return true;
        }

        if(value->getValueType() == DataValue::FLOAT_TYPE
                && type == ConfigType::FLOAT_TYPE)
        {
            return true;
        }

        if(value->getValueType() == DataValue::BOOL_TYPE
                && type == ConfigType::BOOL_TYPE)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief ConfigHandler::isRegistered
 * @param group
 * @param key
 * @return
 */
bool
ConfigHandler::isRegistered(const std::string &group,
                            const std::string &key)
{
    std::map<std::string, std::map<std::string, ConfigType>>::const_iterator outerIt;
    outerIt = m_registeredConfigs.find(group);

    if(outerIt != m_registeredConfigs.end())
    {
        std::map<std::string, ConfigType>::const_iterator innerIt;
        innerIt = outerIt->second.find(key);

        if(innerIt != outerIt->second.end())
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief ConfigHandler::registerType
 * @param group
 * @param key
 * @param type
 * @return
 */
bool
ConfigHandler::registerType(const std::string &group,
                            const std::string &key,
                            const ConfigType type)
{
    // precheck if already exist
    if(isRegistered(group, key) == true) {
        return false;
    }

    std::map<std::string, std::map<std::string, ConfigType>>::iterator outerIt;

    // add group, if not exist
    outerIt = m_registeredConfigs.find(group);
    if(outerIt == m_registeredConfigs.end())
    {
        std::map<std::string, ConfigType> newEntry;
        m_registeredConfigs.insert(
                    std::pair<std::string, std::map<std::string, ConfigType>>(group, newEntry));
    }

    // add new value
    outerIt = m_registeredConfigs.find(group);
    if(outerIt != m_registeredConfigs.end())
    {
        outerIt->second.insert(std::pair<std::string, ConfigType>(key, type));
    }

    return true;
}

}
}
