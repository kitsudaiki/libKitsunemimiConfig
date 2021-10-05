/**
 *  @file       config_handler_test.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include "config_handler_test.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiCommon/files/text_file.h>
#include <libKitsunemimiCommon/common_methods/file_methods.h>

namespace Kitsunemimi
{
namespace Config
{

ConfigHandler_Test::ConfigHandler_Test()
    : Kitsunemimi::CompareTestHelper("ConfigHandler_Test")
{
    initTestCase();

    readConfig_test();

    // private methods
    registerType_test();
    isRegistered_test();
    getRegisteredType_test();
    checkType_test();

    // public methods
    registerString_test();
    registerInteger_test();
    registerFloat_test();
    registerBoolean_test();
    registerStringArray_test();
    getString_test();
    getInteger_test();
    getFloat_test();
    getBoolean_test();
    getStringArray_test();

    cleanupTestCase();
}

/**
 * initTestCase
 */
void
ConfigHandler_Test::initTestCase()
{
    std::string errorMessage;
    Kitsunemimi::writeFile(m_testFilePath,
                           getTestString(),
                           errorMessage,
                           true);
}

/**
 * @brief readConfig_test
 */
void
ConfigHandler_Test::readConfig_test()
{
    ConfigHandler configHandler;

    TEST_EQUAL(configHandler.initConfig("/tmp/asönganergupuneruigndf.ini"), false);
    TEST_EQUAL(configHandler.initConfig(m_testFilePath), true);
}

/**
 * @brief registerType_test
 */
void
ConfigHandler_Test::registerType_test()
{
    ConfigHandler configHandler;

    TEST_EQUAL(configHandler.registerType("groupName", "key1", ConfigHandler::ConfigType::STRING_TYPE), true);
    TEST_EQUAL(configHandler.registerType("groupName", "key2", ConfigHandler::ConfigType::STRING_TYPE), true);
    TEST_EQUAL(configHandler.registerType("groupName", "key1", ConfigHandler::ConfigType::STRING_TYPE), false);
}

/**
 * @brief isRegistered_test
 */
void
ConfigHandler_Test::isRegistered_test()
{
    ConfigHandler configHandler;

    configHandler.registerType("groupName", "key1", ConfigHandler::ConfigType::STRING_TYPE);

    TEST_EQUAL(configHandler.isRegistered("groupName", "key1"), true);
    TEST_EQUAL(configHandler.isRegistered("groupName", "key2"), false);
}

/**
 * @brief getRegisteredType_test
 */
void
ConfigHandler_Test::getRegisteredType_test()
{
    ConfigHandler configHandler;

    configHandler.registerType("groupName", "key1", ConfigHandler::ConfigType::STRING_TYPE);
    configHandler.registerType("groupName", "key2", ConfigHandler::ConfigType::INT_TYPE);

    TEST_EQUAL(configHandler.getRegisteredType("groupName", "key1"), ConfigHandler::ConfigType::STRING_TYPE);
    TEST_EQUAL(configHandler.getRegisteredType("groupName", "key2"), ConfigHandler::ConfigType::INT_TYPE);
}

/**
 * @brief checkType_test
 */
void
ConfigHandler_Test::checkType_test()
{
    ConfigHandler configHandler;

    configHandler.initConfig(m_testFilePath);

    TEST_EQUAL(configHandler.checkType("DEFAULT", "string_val", ConfigHandler::ConfigType::INT_TYPE), false);
    TEST_EQUAL(configHandler.checkType("DEFAULT", "string_val", ConfigHandler::ConfigType::STRING_TYPE), true);
    TEST_EQUAL(configHandler.checkType("asdf", "string_val", ConfigHandler::ConfigType::STRING_TYPE), true);
}

/**
 * @brief registerString_test
 */
void
ConfigHandler_Test::registerString_test()
{
    ConfigHandler configHandler;

    configHandler.initConfig(m_testFilePath);

    configHandler.registerString("DEFAULT", "int_val", "default");
    configHandler.registerString("DEFAULT", "itemName", "default");
    configHandler.registerString("DEFAULT", "string_val", "default");
    configHandler.registerString("DEFAULT", "string_val", "default");
}

/**
 * @brief registerInteger_test
 */
void
ConfigHandler_Test::registerInteger_test()
{
    ConfigHandler configHandler;

    configHandler.initConfig(m_testFilePath);

    configHandler.registerInteger("DEFAULT", "string_val", 42);
    configHandler.registerInteger("DEFAULT", "itemName", 42);
    configHandler.registerInteger("DEFAULT", "int_val", 42);
    configHandler.registerInteger("DEFAULT", "int_val", 42);
}

/**
 * @brief registerFloat_test
 */
void
ConfigHandler_Test::registerFloat_test()
{
    ConfigHandler configHandler;

    configHandler.initConfig(m_testFilePath);

    configHandler.registerFloat("DEFAULT", "string_val", 42.0);
    configHandler.registerFloat("DEFAULT", "itemName", 42.0);
    configHandler.registerFloat("DEFAULT", "float_val", 42.0);
    configHandler.registerFloat("DEFAULT", "float_val", 42.0);
}

/**
 * @brief registerBoolean_test
 */
void
ConfigHandler_Test::registerBoolean_test()
{
    ConfigHandler configHandler;

    configHandler.initConfig(m_testFilePath);

    configHandler.registerBoolean("DEFAULT", "string_val", true);
    configHandler.registerBoolean("DEFAULT", "itemName", true);
    configHandler.registerBoolean("DEFAULT", "bool_value", true);
    configHandler.registerBoolean("DEFAULT", "bool_value", true);
}

/**
 * @brief registerStringArray_test
 */
void
ConfigHandler_Test::registerStringArray_test()
{
    ConfigHandler configHandler;
    std::vector<std::string> defaultValue;

    configHandler.initConfig(m_testFilePath);
    defaultValue.push_back("test");

    configHandler.registerStringArray("DEFAULT", "string_val", defaultValue);
    configHandler.registerStringArray("DEFAULT", "itemName", defaultValue);
    configHandler.registerStringArray("DEFAULT", "string_list", defaultValue);
    configHandler.registerStringArray("DEFAULT", "string_list", defaultValue);
}

/**
 * @brief getString_test
 */
void
ConfigHandler_Test::getString_test()
{
    ConfigHandler configHandler;
    bool success = false;

    configHandler.initConfig(m_testFilePath);

    // test if unregistered
    TEST_EQUAL(configHandler.getString("DEFAULT", "string_val", success), "");
    TEST_EQUAL(success, false);

    configHandler.registerString("DEFAULT", "string_val", "xyz");

    // successful test
    TEST_EQUAL(configHandler.getString("DEFAULT", "string_val", success), "asdf.asdf");
    TEST_EQUAL(success, true);

    // test false type
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "string_val", success), 0);
    TEST_EQUAL(success, false);

    configHandler.registerString("DEFAULT", "string_val2", "xyz");

    // test default
    TEST_EQUAL(configHandler.getString("DEFAULT", "string_val2", success), "xyz");
    TEST_EQUAL(success, true);
}

/**
 * @brief getInteger_test
 */
void
ConfigHandler_Test::getInteger_test()
{
    ConfigHandler configHandler;
    bool success = false;

    configHandler.initConfig(m_testFilePath);

    // test if unregistered
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "int_val", success), 0);
    TEST_EQUAL(success, false);

    configHandler.registerInteger("DEFAULT", "int_val", 42);

    // successful test
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "int_val", success), 2);
    TEST_EQUAL(success, true);

    // test false type
    TEST_EQUAL(configHandler.getString("DEFAULT", "int_val", success), "");
    TEST_EQUAL(success, false);

    configHandler.registerInteger("DEFAULT", "int_val2", 42);

    // test default
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "int_val2", success), 42);
    TEST_EQUAL(success, true);
}

/**
 * @brief getFloat_test
 */
void
ConfigHandler_Test::getFloat_test()
{
    ConfigHandler configHandler;
    bool success = false;

    configHandler.initConfig(m_testFilePath);

    // test if unregistered
    TEST_EQUAL(configHandler.getFloat("DEFAULT", "float_val", success), 0.0);
    TEST_EQUAL(success, false);

    configHandler.registerFloat("DEFAULT", "float_val", 42.0);

    // successful test
    TEST_EQUAL(configHandler.getFloat("DEFAULT", "float_val", success), 123.0);
    TEST_EQUAL(success, true);

    // test false type
    TEST_EQUAL(configHandler.getString("DEFAULT", "string_val", success), "");
    TEST_EQUAL(success, false);

    configHandler.registerFloat("DEFAULT", "float_val2", 42.0);

    // test default
    TEST_EQUAL(configHandler.getFloat("DEFAULT", "float_val2", success), 42.0);
    TEST_EQUAL(success, true);
}

/**
 * @brief getBoolean_test
 */
void
ConfigHandler_Test::getBoolean_test()
{
    ConfigHandler configHandler;
    bool success = false;

    configHandler.initConfig(m_testFilePath);

    // test if unregistered
    TEST_EQUAL(configHandler.getBoolean("DEFAULT", "bool_value", success), false);
    TEST_EQUAL(success, false);

    configHandler.registerBoolean("DEFAULT", "bool_value", false);

    // successful test
    TEST_EQUAL(configHandler.getBoolean("DEFAULT", "bool_value", success), true);
    TEST_EQUAL(success, true);

    // test false type
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "string_val", success), 0);
    TEST_EQUAL(success, false);

    configHandler.registerBoolean("DEFAULT", "bool_value2", true);

    // test default
    TEST_EQUAL(configHandler.getBoolean("DEFAULT", "bool_value2", success), true);
    TEST_EQUAL(success, true);
}

/**
 * @brief getStringArray_test
 */
void
ConfigHandler_Test::getStringArray_test()
{
    ConfigHandler configHandler;
    bool success = false;
    std::vector<std::string> defaultValue;
    std::vector<std::string> ret;

    configHandler.initConfig(m_testFilePath);
    defaultValue.push_back("test");

    // test if unregistered
    ret = configHandler.getStringArray("DEFAULT", "string_list", success);
    TEST_EQUAL(ret.size(), 0);
    TEST_EQUAL(success, false);

    configHandler.registerStringArray("DEFAULT", "string_list", defaultValue);

    // successful test
    ret = configHandler.getStringArray("DEFAULT", "string_list", success);
    TEST_EQUAL(ret.size(), 3);
    TEST_EQUAL(success, true);

    // test false type
    TEST_EQUAL(configHandler.getInteger("DEFAULT", "string_val", success), 0);
    TEST_EQUAL(success, false);

    configHandler.registerStringArray("DEFAULT", "string_list2", defaultValue);

    // test default
    ret = configHandler.getStringArray("DEFAULT", "string_list2", success);
    TEST_EQUAL(ret.size(), 1);
    TEST_EQUAL(success, true);
}

/**
 * cleanupTestCase
 */
void
ConfigHandler_Test::cleanupTestCase()
{
    std::string errorMessage = "";
    Kitsunemimi::deleteFileOrDir(m_testFilePath, errorMessage);
}

/**
 * @brief ConfigHandler_Test::getTestString
 * @return
 */
const std::string
ConfigHandler_Test::getTestString()
{
    const std::string testString(
                "[DEFAULT]\n"
                "string_val = asdf.asdf\n"
                "int_val = 2\n"
                "float_val = 123.0\n"
                "string_list = a,b,c\n"
                "bool_value = true\n"
                "\n");
    return testString;
}

}
}
