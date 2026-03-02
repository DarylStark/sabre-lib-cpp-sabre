#include <gtest/gtest.h>
#include <sabre/core/exceptions.hpp>
#include <sabre/log/logging.hpp>
#include <sabre_test_mocks/log.hpp>

using namespace sabre::log;
using sabre::impl::sabre_test_mocks::TestHandler;

TEST(LogManagerTest, Defaults)
{
    LogManager l;
    ASSERT_EQ(l.getLevel(), LoggingLevel::INFO);
    ASSERT_EQ(l.getHandlerCount(), 0);
}

class LogManagerTest : public ::testing::TestWithParam<LoggingLevel>
{
};

TEST_P(LogManagerTest, SetLevel)
{
    LogManager l;

    LoggingLevel level = GetParam();

    l.setLevel(level);
    ASSERT_EQ(l.getLevel(), level);
}

INSTANTIATE_TEST_SUITE_P(
    LoggingLevels, LogManagerTest,
    ::testing::Values(LoggingLevel::NOTSET, LoggingLevel::EMERGENCY,
                      LoggingLevel::ALERT, LoggingLevel::CRITICAL,
                      LoggingLevel::ERROR, LoggingLevel::WARNING,
                      LoggingLevel::NOTICE, LoggingLevel::INFO,
                      LoggingLevel::DEBUG));

TEST(LogManagerTest, LogWithHandlerName)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testLogger", std::make_unique<TestHandler>(
                                   lastLevel, lastLoggerName, lastMessage));
    l.log(LoggingLevel::ERROR, "TestLogger", "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "TestLogger");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST(LogManagerTest, LogWithoutHandlerName)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testLogger", std::make_unique<TestHandler>(
                                   lastLevel, lastLoggerName, lastMessage));
    l.log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST(LogManagerTest, AddHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testHandler_1", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_2", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_3", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));

    ASSERT_EQ(l.getHandlerCount(), 3);
}

TEST(LogManagerTest, RemoveExistingHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testHandler_1", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_2", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_3", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));

    l.removeHandler("testHandler_2");
    ASSERT_EQ(l.getHandlerCount(), 2);
}

TEST(LogManagerTest, RemoveNonExistingHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testHandler_1", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_2", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));
    l.addHandler("testHandler_3", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));

    l.removeHandler("testHandler_4");
    ASSERT_EQ(l.getHandlerCount(), 3);
}

TEST(LogManagerTest, RetrievingLogHandlers)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testHandler_1", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));

    ASSERT_NO_THROW(auto &handler = l.getHandler("testHandler_1"));
}

TEST(LogManagerTest, RetrievingIncorrectHandler)
{
    LogManager l;
    ASSERT_THROW(auto &handler = l.getHandler("non_existing_handler"),
                 sabre::core::LogHandlerNotAvailableException);
}

TEST(LogManagerTest, LoggerFunctionality)
{
    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    LogManager l;
    l.addHandler("testHandler_1", std::make_unique<TestHandler>(
                                      lastLevel, lastLoggerName, lastMessage));

    auto logger = l.getLogger("TestLogger1");

    logger.log(LoggingLevel::INFO, "Testmessage_1");
    ASSERT_EQ(lastLevel, LoggingLevel::INFO);
    ASSERT_EQ(lastMessage, "Testmessage_1");
    ASSERT_EQ(lastLoggerName, "TestLogger1");
}

TEST(LogManagerTest, LoggerFunctionalityTwoLoggers)
{
    LoggingLevel lastLevel_1 = LoggingLevel::DEBUG;
    LoggingLevel lastLevel_2 = LoggingLevel::DEBUG;
    std::string lastLoggerName_1;
    std::string lastLoggerName_2;
    std::string lastMessage_1;
    std::string lastMessage_2;

    LogManager l1;
    LogManager l2;
    l1.addHandler("testHandler_1",
                  std::make_unique<TestHandler>(lastLevel_1, lastLoggerName_1,
                                                lastMessage_1));
    l2.addHandler("testHandler_2",
                  std::make_unique<TestHandler>(lastLevel_2, lastLoggerName_2,
                                                lastMessage_2));

    auto logger_1 = l1.getLogger("TestLogger1");
    auto logger_2 = l2.getLogger("TestLogger2");

    logger_1.log(LoggingLevel::INFO, "Testmessage_1");
    ASSERT_EQ(lastLevel_1, LoggingLevel::INFO);
    ASSERT_EQ(lastMessage_1, "Testmessage_1");
    ASSERT_EQ(lastLoggerName_1, "TestLogger1");
    ASSERT_EQ(lastLevel_2, LoggingLevel::DEBUG);
    ASSERT_EQ(lastMessage_2, "");
    ASSERT_EQ(lastLoggerName_2, "");

    lastLevel_1 = LoggingLevel::DEBUG;
    lastMessage_1 = "";
    lastLoggerName_1 = "";

    logger_2.log(LoggingLevel::INFO, "Testmessage_2");
    ASSERT_EQ(lastLevel_1, LoggingLevel::DEBUG);
    ASSERT_EQ(lastMessage_1, "");
    ASSERT_EQ(lastLoggerName_1, "");
    ASSERT_EQ(lastLevel_2, LoggingLevel::INFO);
    ASSERT_EQ(lastMessage_2, "Testmessage_2");
    ASSERT_EQ(lastLoggerName_2, "TestLogger2");
}