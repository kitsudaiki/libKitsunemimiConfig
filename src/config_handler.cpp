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
 * @param groupName
 * @param itemName
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerString(const std::string &groupName,
                              const std::string &itemName,
                              const std::string &defaultValue)
{
    std::string tempGroupName = groupName;
    if(tempGroupName == "") {
        tempGroupName = "DEFAULT";
    }

    if(checkType(tempGroupName, itemName, ConfigType::STRING_TYPE) == false) {
        return false;
    }
    if(registerType(tempGroupName, itemName, ConfigType::STRING_TYPE) == false) {
        return false;
    }

    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief ConfigHandler::registerConfig
 * @param groupName
 * @param itemName
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerInteger(const std::string &groupName,
                               const std::string &itemName,
                               const long defaultValue)
{
    std::string tempGroupName = groupName;
    if(tempGroupName == "") {
        tempGroupName = "DEFAULT";
    }

    if(checkType(tempGroupName, itemName, ConfigType::INT_TYPE) == false) {
        return false;
    }
    if(registerType(tempGroupName, itemName, ConfigType::INT_TYPE) == false) {
        return false;
    }

    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief ConfigHandler::registerConfig
 * @param groupName
 * @param itemName
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerFloat(const std::string &groupName,
                             const std::string &itemName,
                             const double defaultValue)
{
    std::string tempGroupName = groupName;
    if(tempGroupName == "") {
        tempGroupName = "DEFAULT";
    }

    if(checkType(tempGroupName, itemName, ConfigType::FLOAT_TYPE) == false) {
        return false;
    }
    if(registerType(tempGroupName, itemName, ConfigType::FLOAT_TYPE) == false) {
        return false;
    }

    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief ConfigHandler::registerConfig
 * @param groupName
 * @param itemName
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerBoolean(const std::string &groupName,
                               const std::string &itemName,
                               const bool defaultValue)
{
    std::string tempGroupName = groupName;
    if(tempGroupName == "") {
        tempGroupName = "DEFAULT";
    }

    if(checkType(tempGroupName, itemName, ConfigType::BOOL_TYPE) == false) {
        return false;
    }
    if(registerType(tempGroupName, itemName, ConfigType::BOOL_TYPE) == false) {
        return false;
    }

    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief ConfigHandler::registerConfig
 * @param groupName
 * @param itemName
 * @param defaultValue
 * @return
 */
bool
ConfigHandler::registerStringArray(const std::string &groupName,
                                   const std::string &itemName,
                                   const std::vector<std::string> &defaultValue)
{
    std::string tempGroupName = groupName;
    if(tempGroupName == "") {
        tempGroupName = "DEFAULT";
    }

    if(checkType(tempGroupName, itemName, ConfigType::STRING_ARRAY_TYPE) == false) {
        return false;
    }
    if(registerType(tempGroupName, itemName, ConfigType::STRING_ARRAY_TYPE) == false) {
        return false;
    }

    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief ConfigHandler::getString
 * @param groupName
 * @param itemName
 * @param success
 * @return
 */
const std::string
ConfigHandler::getString(const std::string &groupName,
                         const std::string &itemName,
                         bool &success)
{
    success = true;
    if(getRegisteredType(groupName, itemName) != ConfigType::STRING_TYPE)
    {
        success = false;
        return "";
    }

    return m_iniItem->get(groupName, itemName)->toValue()->getString();
}

/**
 * @brief ConfigHandler::getInteger
 * @param groupName
 * @param itemName
 * @param success
 * @return
 */
long
ConfigHandler::getInteger(const std::string &groupName,
                          const std::string &itemName,
                          bool &success)
{
    success = true;
    if(getRegisteredType(groupName, itemName) != ConfigType::INT_TYPE)
    {
        success = false;
        return 0l;
    }

    return m_iniItem->get(groupName, itemName)->toValue()->getLong();
}

/**
 * @brief ConfigHandler::getFloat
 * @param groupName
 * @param itemName
 * @param success
 * @return
 */
double
ConfigHandler::getFloat(const std::string &groupName,
                        const std::string &itemName,
                        bool &success)
{
    success = true;
    if(getRegisteredType(groupName, itemName) != ConfigType::FLOAT_TYPE)
    {
        success = false;
        return 0.0;
    }

    return m_iniItem->get(groupName, itemName)->toValue()->getDouble();
}

/**
 * @brief ConfigHandler::getBoolean
 * @param groupName
 * @param itemName
 * @param success
 * @return
 */
bool
ConfigHandler::getBoolean(const std::string &groupName,
                          const std::string &itemName,
                          bool &success)
{
    success = true;
    if(getRegisteredType(groupName, itemName) != ConfigType::BOOL_TYPE)
    {
        success = false;
        return false;
    }

    return m_iniItem->get(groupName, itemName)->toValue()->getBool();
}

/**
 * @brief ConfigHandler::getStringArray
 * @param groupName
 * @param itemName
 * @param success
 * @return
 */
const std::vector<std::string>
ConfigHandler::getStringArray(const std::string &groupName,
                              const std::string &itemName,
                              bool &success)
{
    std::vector<std::string> result;
    success = true;

    if(getRegisteredType(groupName, itemName) != ConfigType::STRING_ARRAY_TYPE)
    {
        success = false;
        return result;
    }

    DataArray* array = m_iniItem->get(groupName, itemName)->toArray();
    for(uint32_t i = 0; i < array->size(); i++)
    {
        result.push_back(array->get(i)->toValue()->getString());
    }

    return result;
}

/**
 * @brief ConfigHandler::checkType
 * @param groupName
 * @param itemName
 * @param type
 * @return
 */
bool
ConfigHandler::checkType(const std::string &groupName,
                         const std::string &itemName,
                         const ConfigType type)
{
    DataItem* currentItem = m_iniItem->get(groupName, itemName);
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
 * @param groupName
 * @param itemName
 * @return
 */
bool
ConfigHandler::isRegistered(const std::string &groupName,
                            const std::string &itemName)
{
    if(getRegisteredType(groupName, itemName) == ConfigType::UNDEFINED_TYPE) {
        return false;
    }

    return true;
}

/**
 * @brief ConfigHandler::registerType
 * @param groupName
 * @param itemName
 * @param type
 * @return
 */
bool
ConfigHandler::registerType(const std::string &groupName,
                            const std::string &itemName,
                            const ConfigType type)
{
    // precheck if already exist
    if(isRegistered(groupName, itemName) == true) {
        return false;
    }

    std::map<std::string, std::map<std::string, ConfigType>>::iterator outerIt;

    // add groupName, if not exist
    outerIt = m_registeredConfigs.find(groupName);
    if(outerIt == m_registeredConfigs.end())
    {
        std::map<std::string, ConfigType> newEntry;
        m_registeredConfigs.insert(
                    std::pair<std::string, std::map<std::string, ConfigType>>(groupName, newEntry));
    }

    // add new value
    outerIt = m_registeredConfigs.find(groupName);
    if(outerIt != m_registeredConfigs.end())
    {
        outerIt->second.insert(std::pair<std::string, ConfigType>(itemName, type));
    }

    return true;
}

/**
 * @brief ConfigHandler::getRegisteredType
 * @param groupName
 * @param itemName
 * @return
 */
ConfigType
ConfigHandler::getRegisteredType(const std::string &groupName,
                                 const std::string &itemName)
{
    std::map<std::string, std::map<std::string, ConfigType>>::const_iterator outerIt;
    outerIt = m_registeredConfigs.find(groupName);

    if(outerIt != m_registeredConfigs.end())
    {
        std::map<std::string, ConfigType>::const_iterator innerIt;
        innerIt = outerIt->second.find(itemName);

        if(innerIt != outerIt->second.end())
        {
            return innerIt->second;
        }
    }

    return UNDEFINED_TYPE;
}

}
}
