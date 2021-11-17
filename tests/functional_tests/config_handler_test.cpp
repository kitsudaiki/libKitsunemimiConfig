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
    runTest();
}

/**
 * @brief runTest
 */
void
ConfigHandler_Test::runTest()
{
    ErrorContainer error;
    Kitsunemimi::writeFile(m_testFilePath, getTestString(), error, true);

    // init config
    TEST_EQUAL(Kitsunemimi::Config::initConfig(m_testFilePath, error), true);

    REGISTER_STRING_CONFIG("DEFAULT", "string_val", error, "");
    REGISTER_INT_CONFIG("DEFAULT", "int_val", error, 42);
    REGISTER_INT_CONFIG("DEFAULT", "another_int_val", error, 42);

    bool success = false;
    TEST_EQUAL(GET_STRING_CONFIG("DEFAULT", "string_val", success), "asdf.asdf");
    TEST_EQUAL(success, true);
    TEST_EQUAL(GET_INT_CONFIG("DEFAULT", "int_val", success), 2);
    TEST_EQUAL(success, true);
    TEST_EQUAL(GET_INT_CONFIG("DEFAULT", "another_int_val", success), 42);
    TEST_EQUAL(success, true);
    TEST_EQUAL(GET_STRING_CONFIG("DEFAULT", "fail", success), "");
    TEST_EQUAL(success, false);

    Kitsunemimi::deleteFileOrDir(m_testFilePath, error);

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
