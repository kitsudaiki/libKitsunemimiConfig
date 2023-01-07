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
    void runTest();

    const std::string getTestString();

    std::string m_testFilePath = "/tmp/ConfigHandler_Test.ini";
};

} // namespace Kitsunemimi

#endif // CONFIG_HANDLER_TEST_H
