#include "sabre_test_mocks/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/io/uart_output_stream_buffer.hpp>
#include <sabre/log/log_handlers.hpp>

#include <iostream>

TEST(OStreamLogHandler, Logging)
{
    std::unique_ptr<sabre::impl::sabre_test_mocks::TestUART> u =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::UartStreamBuf buffer(std::move(u), 128);
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