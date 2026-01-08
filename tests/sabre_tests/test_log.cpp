#include "sabre_test_mocks/hal.hpp"
#include "sabre_test_mocks/log.hpp"
#include <gtest/gtest.h>
#include <sabre/io/serial_output_stream_buffer.hpp>
#include <sabre/log/log_handlers.hpp>
#include <sabre/log/logging.hpp>

#include <iostream>

TEST(Logging, DebugLogging)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);
    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "Testlogger",
                             "Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, InfoLogging)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::INFO);
    sabre::log::Logging::addHandler(handler);
    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "Testlogger",
                             "Testmessage");
    sabre::log::Logging::log(sabre::log::LoggingLevel::DEBUG,
                             "Testlogger_debug", "Testmessage_debug");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, RetrieveLevel)
{
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(sabre::log::Logging::getLevel(), sabre::log::LoggingLevel::INFO);

    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::WARNING);
    ASSERT_EQ(sabre::log::Logging::getLevel(),
              sabre::log::LoggingLevel::WARNING);
}

TEST(Logging, Logger)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::INFO);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.log(sabre::log::LoggingLevel::INFO, "Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerDebug)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.debug("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::DEBUG);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerInfo)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.info("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::INFO);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerNotice)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.notice("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::NOTICE);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerWarning)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.warning("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::WARNING);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerError)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.error("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::ERROR);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerCritical)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.critical("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::CRITICAL);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerAlert)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.alert("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::ALERT);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
}

TEST(Logging, LoggerEmergency)
{
    std::shared_ptr<sabre::impl::sabre_test_mocks::TestHandler> handler =
        std::make_shared<sabre::impl::sabre_test_mocks::TestHandler>();
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::Logging::addHandler(handler);

    sabre::log::Logger logger("Testlogger");
    logger.emergency("Testmessage");

    ASSERT_EQ(handler->getLastLevel(), sabre::log::LoggingLevel::EMERGENCY);
    ASSERT_EQ(handler->getLastLoggerName(), "Testlogger");
    ASSERT_EQ(handler->getLastMessage(), "Testmessage");
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

TEST(OStreamLogHandler, Logging)
{
    std::unique_ptr<sabre::impl::sabre_test_mocks::TestUART> u =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::SerialStreamBuf buffer(std::move(u), 128);
    std::ostream stream(&buffer);

    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::OStreamLogHandler::SharedPtr handler =
        std::make_shared<sabre::log::OStreamLogHandler>(stream);

    sabre::log::Logging::addHandler(handler);

    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "TestLogger",
                             "Testmessage");

    sabre::log::Logging::removeHandler(handler);

    ASSERT_TRUE(u_ptr->_buf.contains("TestLogger"));
    ASSERT_TRUE(u_ptr->_buf.contains("Testmessage"));
}

TEST(LogBufferHandler, Logging)
{
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::LogBufferHandler::SharedPtr handler =
        std::make_shared<sabre::log::LogBufferHandler>(1);

    sabre::log::Logging::addHandler(handler);

    sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "TestLogger",
                             "Testmessage");

    ASSERT_TRUE(handler->getBuffer()[0].contains("TestLogger"));
}

TEST(LogBufferHandler, Overflow)
{
    sabre::log::Logging::setLevel(sabre::log::LoggingLevel::DEBUG);
    sabre::log::LogBufferHandler::SharedPtr handler =
        std::make_shared<sabre::log::LogBufferHandler>(2);

    sabre::log::Logging::addHandler(handler);

    for (uint32_t i = 0; i < 5; ++i)
        sabre::log::Logging::log(sabre::log::LoggingLevel::INFO, "TestLogger",
                                 "Testmessage");
    ASSERT_TRUE(handler->getBuffer().size() == 2);
}
