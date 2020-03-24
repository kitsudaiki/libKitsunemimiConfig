#include <libKitsunemimiConfig/config_handler.h>

#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiPersistence/files/text_file.h>
#include <libKitsunemimiIni/ini_item.h>

namespace Kitsunemimi
{
namespace Config
{

/**
 * @brief ConfigHandler::ConfigHandler
 */
ConfigHandler::ConfigHandler()
{

}

/**
 * @brief ConfigHandler::readConfig
 * @param configFilePath
 * @param errorMessage
 * @return
 */
bool ConfigHandler::readConfig(const std::string &configFilePath,
                               std::string &errorMessage)
{
    // read file
    m_configFilePath = configFilePath;
    const std::pair<bool, std::string> ret = Persistence::readFile(m_configFilePath, errorMessage);
    if(ret.first == false) {
        return false;
    }

    // parse file content
    m_iniItem = new Ini::IniItem();
    bool result = m_iniItem->parse(ret.second, errorMessage);
    if(result == false) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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
    if(checkType(group, key, type)) {
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

}
}
