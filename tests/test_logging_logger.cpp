#include "sabre_testing/logging/test_handler.hpp"
#include <gtest/gtest.h>
#include <sabre/logging/logging.hpp>

TEST(Logging, DebugLogging)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);
    Sabre::Logging::log(Sabre::LoggingLevel::INFO, "Testlogger", "Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, InfoLogging)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::INFO);
    Sabre::Logging::add_handler(handler);
    Sabre::Logging::log(Sabre::LoggingLevel::INFO, "Testlogger", "Testmessage");
    Sabre::Logging::log(Sabre::LoggingLevel::DEBUG, "Testlogger_debug",
                        "Testmessage_debug");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, RetrieveLevel)
{
    Sabre::Logging::set_level(Sabre::LoggingLevel::INFO);
    ASSERT_EQ(Sabre::Logging::get_level(), Sabre::LoggingLevel::INFO);

    Sabre::Logging::set_level(Sabre::LoggingLevel::WARNING);
    ASSERT_EQ(Sabre::Logging::get_level(), Sabre::LoggingLevel::WARNING);
}

TEST(Logging, Logger)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::INFO);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.log(Sabre::LoggingLevel::INFO, "Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerDebug)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.debug("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::DEBUG);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerInfo)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.info("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerNotice)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.notice("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::NOTICE);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerWarning)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.warning("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::WARNING);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerError)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.error("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::ERROR);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerCritical)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.critical("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::CRITICAL);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerAlert)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.alert("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::ALERT);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerEmergency)
{
    std::shared_ptr<Sabre::Testing::TestHandler> handler =
        std::make_shared<Sabre::Testing::TestHandler>();
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::Logging::add_handler(handler);

    Sabre::Logger logger("Testlogger");
    logger.emergency("Testmessage");

    ASSERT_EQ(handler->get_last_level(), Sabre::LoggingLevel::EMERGENCY);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggingLevelToString_Unknown)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::NOTSET), "UNKNOWN");
}

TEST(Logging, LoggingLevelToString_Emergency)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::EMERGENCY), "EMERGENCY");
}

TEST(Logging, LoggingLevelToString_Alert)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::ALERT), "ALERT");
}

TEST(Logging, LoggingLevelToString_Critical)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::CRITICAL), "CRITICAL");
}

TEST(Logging, LoggingLevelToString_Error)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::ERROR), "ERROR");
}

TEST(Logging, LoggingLevelToString_Warning)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::WARNING), "WARNING");
}

TEST(Logging, LoggingLevelToString_Notice)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::NOTICE), "NOTICE");
}

TEST(Logging, LoggingLevelToString_Info)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::INFO), "INFO");
}

TEST(Logging, LoggingLevelToString_Debug)
{
    using namespace Sabre;
    ASSERT_EQ(LoggingLevelToString(LoggingLevel::DEBUG), "DEBUG");
}