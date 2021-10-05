/**
 *  @file       config_handler.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiConfig/config_handler.h>

#include <libKitsunemimiCommon/common_items/data_items.h>
#include <libKitsunemimiCommon/files/text_file.h>
#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiIni/ini_item.h>

namespace Kitsunemimi
{
namespace Config
{

ConfigHandler* ConfigHandler::m_config = nullptr;

/**
 * @brief read a ini config-file
 *
 * @param configFilePath absolute path to the config-file to read
 *
 * @return false, if reading or parsing the file failed, else true
 */
bool
initConfig(const std::string &configFilePath)
{
    if(ConfigHandler::m_config != nullptr)
    {
        LOG_ERROR("config is already initialized.");
        return false;
    }

    ConfigHandler::m_config = new ConfigHandler();
    return ConfigHandler::m_config->initConfig(configFilePath);
}

/**
 * @brief reset configuration (primary to test different configs in one test)
 */
void
resetConfig()
{
    if(ConfigHandler::m_config != nullptr)
    {
        delete ConfigHandler::m_config;
        ConfigHandler::m_config = nullptr;
    }
}

/**
 * @brief register string config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
 */
bool
registerString(const std::string &groupName,
               const std::string &itemName,
               const std::string &defaultValue)
{
    if(ConfigHandler::m_config == nullptr) {
        return false;
    }

    return ConfigHandler::m_config->registerString(groupName, itemName, defaultValue);
}

/**
 * @brief register int/long config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
 */
bool
registerInteger(const std::string &groupName,
                const std::string &itemName,
                const long defaultValue)
{
    if(ConfigHandler::m_config == nullptr) {
        return false;
    }

    return ConfigHandler::m_config->registerInteger(groupName, itemName,  defaultValue);
}

/**
 * @brief register float/double config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
 */
bool
registerFloat(const std::string &groupName,
              const std::string &itemName,
              const double defaultValue)
{
    if(ConfigHandler::m_config == nullptr) {
        return false;
    }

    return ConfigHandler::m_config->registerFloat(groupName, itemName, defaultValue);
}

/**
 * @brief register bool config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
 */
bool
registerBoolean(const std::string &groupName,
                const std::string &itemName,
                const bool defaultValue)
{
    if(ConfigHandler::m_config == nullptr) {
        return false;
    }

    return ConfigHandler::m_config->registerBoolean(groupName, itemName, defaultValue);
}

/**
 * @brief register string-array config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
 */
bool
registerStringArray(const std::string &groupName,
                    const std::string &itemName,
                    const std::vector<std::string> &defaultValue)
{
    if(ConfigHandler::m_config == nullptr) {
        return false;
    }

    return ConfigHandler::m_config->registerStringArray(groupName, itemName, defaultValue);
}

/**
 * @brief get string-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return empty string, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::string
getString(const std::string &groupName,
          const std::string &itemName,
          bool &success)
{
    success = true;

    if(ConfigHandler::m_config == nullptr)
    {
        success = false;
        return "";
    }

    return ConfigHandler::m_config->getString(groupName, itemName, success);
}

/**
 * @brief get long-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return 0, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
long
getInteger(const std::string &groupName,
           const std::string &itemName,
           bool &success)
{
    success = true;

    if(ConfigHandler::m_config == nullptr)
    {
        success = false;
        return 0;
    }

    return ConfigHandler::m_config->getInteger(groupName, itemName, success);
}

/**
 * @brief get double-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return 0.0, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
double
getFloat(const std::string &groupName,
         const std::string &itemName,
         bool &success)
{
    success = true;

    if(ConfigHandler::m_config == nullptr)
    {
        success = false;
        return 0.0;
    }

    return ConfigHandler::m_config->getFloat(groupName, itemName, success);
}

/**
 * @brief get bool-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return false, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
bool
getBoolean(const std::string &groupName,
           const std::string &itemName,
           bool &success)
{
    success = true;

    if(ConfigHandler::m_config == nullptr)
    {
        success = false;
        return false;
    }

    return ConfigHandler::m_config->getBoolean(groupName, itemName, success);
}

/**
 * @brief get string-array-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return empty string-array, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::vector<std::string>
getStringArray(const std::string &groupName,
               const std::string &itemName,
               bool &success)
{
    std::vector<std::string> result;
    success = true;

    if(ConfigHandler::m_config == nullptr)
    {
        success = false;
        return result;
    }

    return ConfigHandler::m_config->getStringArray(groupName, itemName, success);
}

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
 * @brief read a ini config-file
 *
 * @param configFilePath absolute path to the config-file to read
 *
 * @return false, if reading or parsing the file failed, else true
 */
bool ConfigHandler::initConfig(const std::string &configFilePath)
{
    // read file
    m_configFilePath = configFilePath;
    std::string readErrorMessage = "";
    std::string fileContent = "";
    bool ret = readFile(fileContent, m_configFilePath, readErrorMessage);
    if(ret == false)
    {
        LOG_ERROR("Error while reding config-file " + configFilePath + "\n");
        LOG_ERROR("   " + readErrorMessage);
        return false;
    }

    // parse file content
    m_iniItem = new Ini::IniItem();
    std::string parseErrorMessage = "";
    bool result = m_iniItem->parse(fileContent, parseErrorMessage);
    if(result == false)
    {
        LOG_ERROR("Error while reding config-file " + configFilePath);
        LOG_ERROR("   " + parseErrorMessage);
        return false;
    }

    return true;
}

/**
 * @brief register string config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
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

    // check type against config-file
    if(checkType(tempGroupName, itemName, ConfigType::STRING_TYPE) == false) {
        return false;
    }

    // try to register type
    if(registerType(tempGroupName, itemName, ConfigType::STRING_TYPE) == false) {
        return false;
    }

    // set default-type, in case the nothing was already set
    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief register int/long config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
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

    // check type against config-file
    if(checkType(tempGroupName, itemName, ConfigType::INT_TYPE) == false) {
        return false;
    }

    // try to register type
    if(registerType(tempGroupName, itemName, ConfigType::INT_TYPE) == false) {
        return false;
    }

    // set default-type, in case the nothing was already set
    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief register float/double config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
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

    // check type against config-file
    if(checkType(tempGroupName, itemName, ConfigType::FLOAT_TYPE) == false) {
        return false;
    }

    // try to register type
    if(registerType(tempGroupName, itemName, ConfigType::FLOAT_TYPE) == false) {
        return false;
    }

    // set default-type, in case the nothing was already set
    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief register bool config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
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

    // check type against config-file
    if(checkType(tempGroupName, itemName, ConfigType::BOOL_TYPE) == false) {
        return false;
    }

    // try to register type
    if(registerType(tempGroupName, itemName, ConfigType::BOOL_TYPE) == false) {
        return false;
    }

    // set default-type, in case the nothing was already set
    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief register string-array config value
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param defaultValue default value, if nothing was set inside of the config
 *
 * @return false, if false type or item-name and group-name are already registered
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

    // check type against config-file
    if(checkType(tempGroupName, itemName, ConfigType::STRING_ARRAY_TYPE) == false) {
        return false;
    }

    // try to register type
    if(registerType(tempGroupName, itemName, ConfigType::STRING_ARRAY_TYPE) == false) {
        return false;
    }

    // set default-type, in case the nothing was already set
    m_iniItem->set(tempGroupName, itemName, defaultValue);

    return true;
}

/**
 * @brief get string-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return empty string, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::string
ConfigHandler::getString(const std::string &groupName,
                         const std::string &itemName,
                         bool &success)
{
    success = true;

    // compare with registered type
    if(getRegisteredType(groupName, itemName) != ConfigType::STRING_TYPE)
    {
        success = false;
        return "";
    }

    // get value from config
    return m_iniItem->get(groupName, itemName)->toValue()->getString();
}

/**
 * @brief get long-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return 0, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
long
ConfigHandler::getInteger(const std::string &groupName,
                          const std::string &itemName,
                          bool &success)
{
    success = true;

    // compare with registered type
    if(getRegisteredType(groupName, itemName) != ConfigType::INT_TYPE)
    {
        success = false;
        return 0l;
    }

    // get value from config
    return m_iniItem->get(groupName, itemName)->toValue()->getLong();
}

/**
 * @brief get double-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return 0.0, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
double
ConfigHandler::getFloat(const std::string &groupName,
                        const std::string &itemName,
                        bool &success)
{
    success = true;

    // compare with registered type
    if(getRegisteredType(groupName, itemName) != ConfigType::FLOAT_TYPE)
    {
        success = false;
        return 0.0;
    }

    // get value from config
    return m_iniItem->get(groupName, itemName)->toValue()->getDouble();
}

/**
 * @brief get bool-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return false, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
bool
ConfigHandler::getBoolean(const std::string &groupName,
                          const std::string &itemName,
                          bool &success)
{
    success = true;

    // compare with registered type
    if(getRegisteredType(groupName, itemName) != ConfigType::BOOL_TYPE)
    {
        success = false;
        return false;
    }

    // get value from config
    return m_iniItem->get(groupName, itemName)->toValue()->getBool();
}

/**
 * @brief get string-array-value from config
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param success reference to bool-value with the result. returns false if item-name and group-name
 *                are not registered, else true.
 *
 * @return empty string-array, if item-name and group-name are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::vector<std::string>
ConfigHandler::getStringArray(const std::string &groupName,
                              const std::string &itemName,
                              bool &success)
{
    std::vector<std::string> result;
    success = true;

    // compare with registered type
    if(getRegisteredType(groupName, itemName) != ConfigType::STRING_ARRAY_TYPE)
    {
        success = false;
        return result;
    }

    // get and transform result from the config-file
    DataArray* array = m_iniItem->get(groupName, itemName)->toArray();
    for(uint32_t i = 0; i < array->size(); i++)
    {
        result.push_back(array->get(i)->toValue()->getString());
    }

    return result;
}

/**
 * @brief check if defined type match with the type of the value within the config-file
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param type type-identifier
 *
 * @return true, if type match with the config-file, else false
 */
bool
ConfigHandler::checkType(const std::string &groupName,
                         const std::string &itemName,
                         const ConfigType type)
{
    // get value from config-file
    DataItem* currentItem = m_iniItem->get(groupName, itemName);

    // precheck
    if(currentItem == nullptr) {
        return true;
    }

    // check for array
    if(currentItem->getType() == DataItem::ARRAY_TYPE
            && type == ConfigType::STRING_ARRAY_TYPE)
    {
        return true;
    }

    // check value
    if(currentItem->getType() == DataItem::VALUE_TYPE)
    {
        DataValue* value = currentItem->toValue();

        // check string
        if(value->getValueType() == DataValue::STRING_TYPE
                && type == ConfigType::STRING_TYPE)
        {
            return true;
        }

        // check integer
        if(value->getValueType() == DataValue::INT_TYPE
                && type == ConfigType::INT_TYPE)
        {
            return true;
        }

        // check float
        if(value->getValueType() == DataValue::FLOAT_TYPE
                && type == ConfigType::FLOAT_TYPE)
        {
            return true;
        }

        // check boolean
        if(value->getValueType() == DataValue::BOOL_TYPE
                && type == ConfigType::BOOL_TYPE)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief check, if an item-name and group-name are already registered
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 *
 * @return true, if item-name and group-name is already registered, else false
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
 * @brief register type
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 * @param type type-identifier to register
 *
 * @return false, if item-name and group-name are already registered, else true
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
        outerIt->second.insert(std::make_pair(itemName, type));
    }

    return true;
}

/**
 * @brief get registered config-type
 *
 * @param groupName name of the group
 * @param itemName name of the item within the group
 *
 * @return undefined-type, if item-name and group-name are not registered, else the registered type
 */
ConfigHandler::ConfigType
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
