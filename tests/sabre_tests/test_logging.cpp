#include <gtest/gtest.h>
#include <sabre/log/logging.hpp>
#include <sabre_test_mocks/log.hpp>

using namespace sabre::log;
using sabre::impl::sabre_test_mocks::TestHandler;

TEST(LoggingTest, Defaults)
{
    Logging l;
    ASSERT_EQ(l.getLevel(), LoggingLevel::INFO);
    ASSERT_EQ(l.getHandlerCount(), 0);
}

class LoggingTest : public ::testing::TestWithParam<LoggingLevel>
{
};

TEST_P(LoggingTest, SetLevel)
{
    Logging l;

    LoggingLevel level = GetParam();

    l.setLevel(level);
    ASSERT_EQ(l.getLevel(), level);
}

INSTANTIATE_TEST_SUITE_P(
    LoggingLevels, LoggingTest,
    ::testing::Values(LoggingLevel::NOTSET, LoggingLevel::EMERGENCY,
                      LoggingLevel::ALERT, LoggingLevel::CRITICAL,
                      LoggingLevel::ERROR, LoggingLevel::WARNING,
                      LoggingLevel::NOTICE, LoggingLevel::INFO,
                      LoggingLevel::DEBUG));

TEST(LoggingTest, LogWithHandlerName)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    Logging l;
    l.addHandler("testLogger", std::make_unique<TestHandler>(
                                   lastLevel, lastLoggerName, lastMessage));
    l.log(LoggingLevel::ERROR, "TestLogger", "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "TestLogger");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST(LoggingTest, LogWithoutHandlerName)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    Logging l;
    l.addHandler("testLogger", std::make_unique<TestHandler>(
                                   lastLevel, lastLoggerName, lastMessage));
    l.log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST(LoggingTest, AddHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    Logging l;
    l.addHandler("testLogger_1", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_2", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_3", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));

    ASSERT_EQ(l.getHandlerCount(), 3);
}

TEST(LoggingTest, RemoveExistingHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    Logging l;
    l.addHandler("testLogger_1", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_2", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_3", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));

    l.removeHandler("testLogger_2");
    ASSERT_EQ(l.getHandlerCount(), 2);
}

TEST(LoggingTest, RemoveNonExistingHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    Logging l;
    l.addHandler("testLogger_1", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_2", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testLogger_3", std::make_unique<TestHandler>(
                                     lastLevel, lastLoggerName, lastMessage));

    l.removeHandler("testLogger_4");
    ASSERT_EQ(l.getHandlerCount(), 3);
}