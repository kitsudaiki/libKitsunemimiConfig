/**
 *  @file       config_handler_test.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef CONFIG_HANDLER_TEST_H
#define CONFIG_HANDLER_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

class ConfigHandler_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    ConfigHandler_Test();

private:
    void initTestCase();

    void readConfig_test();

    // private methods
    void registerType_test();
    void isRegistered_test();
    void getRegisteredType_test();
    void checkType_test();

    // public methods
    void registerString_test();
    void registerInteger_test();
    void registerFloat_test();
    void registerBoolean_test();
    void registerStringArray_test();
    void getString_test();
    void getInteger_test();
    void getFloat_test();
    void getBoolean_test();
    void getStringArray_test();

    void cleanupTestCase();

    const std::string getTestString();

    std::string m_testFilePath = "/tmp/ConfigHandler_Test.ini";
};

} // namespace Kitsunemimi

#endif // CONFIG_HANDLER_TEST_H
