#include "sabre_testing/logging/test_handler.hpp"
#include <gtest/gtest.h>
#include <sabre/log/logging.hpp>

TEST(Logging, DebugLogging)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);
    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "Testlogger",
                             "Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, InfoLogging)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::INFO);
    sabre::log::Logging::add_handler(handler);
    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "Testlogger",
                             "Testmessage");
    sabre::log::Logging::log(sabre::log::LoggingLevel::DEBUG,
                             "Testlogger_debug", "Testmessage_debug");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, RetrieveLevel)
{
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(sabre::log::Logging::get_level(), sabre::log::LoggingLevel::INFO);

    sabre::log::Logging::set_level(sabre::log::LoggingLevel::WARNING);
    ASSERT_EQ(sabre::log::Logging::get_level(),
              sabre::log::LoggingLevel::WARNING);
}

TEST(Logging, Logger)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::INFO);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.log(sabre::log::LoggingLevel::INFO, "Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerDebug)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.debug("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::DEBUG);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerInfo)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.info("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerNotice)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.notice("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::NOTICE);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerWarning)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.warning("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::WARNING);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerError)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.error("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::ERROR);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerCritical)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.critical("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::CRITICAL);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerAlert)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.alert("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::ALERT);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggerEmergency)
{
    std::shared_ptr<sabre::impl::sabre_testing::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_testing::TestHandler>();
    sabre::log::Logging::set_level(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::add_handler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.emergency("Testmessage");

    ASSERT_EQ(handler->get_last_level(), sabre::log::LoggingLevel::EMERGENCY);
    ASSERT_EQ(handler->get_last_logger_name(), "Testlogger");
    ASSERT_EQ(handler->get_last_message(), "Testmessage");
}

TEST(Logging, LoggingLevelToString_Unknown)
{
    using namespace sabre;
    ASSERT_EQ(
        sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::NOTSET),
        "UNKNOWN");
}

TEST(Logging, LoggingLevelToString_Emergency)
{
    using namespace sabre;
    ASSERT_EQ(
        sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::EMERGENCY),
        "EMERGENCY");
}

TEST(Logging, LoggingLevelToString_Alert)
{
    using namespace sabre;
    ASSERT_EQ(sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::ALERT),
              "ALERT");
}

TEST(Logging, LoggingLevelToString_Critical)
{
    using namespace sabre;
    ASSERT_EQ(
        sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::CRITICAL),
        "CRITICAL");
}

TEST(Logging, LoggingLevelToString_Error)
{
    using namespace sabre;
    ASSERT_EQ(sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::ERROR),
              "ERROR");
}

TEST(Logging, LoggingLevelToString_Warning)
{
    using namespace sabre;
    ASSERT_EQ(
        sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::WARNING),
        "WARNING");
}

TEST(Logging, LoggingLevelToString_Notice)
{
    using namespace sabre;
    ASSERT_EQ(
        sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::NOTICE),
        "NOTICE");
}

TEST(Logging, LoggingLevelToString_Info)
{
    using namespace sabre;
    ASSERT_EQ(sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::INFO),
              "INFO");
}

TEST(Logging, LoggingLevelToString_Debug)
{
    using namespace sabre;
    ASSERT_EQ(sabre::log::LoggingLevelToString(sabre::log::LoggingLevel::DEBUG),
              "DEBUG");
}