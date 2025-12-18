#include "sabre_testing/uart/uart.hpp"
#include <gtest/gtest.h>
#include <sabre/logging/log_handlers.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>

#include <iostream>

TEST(OStreamLogHandler, Logging)
{
    std::unique_ptr<sabre::Testing::TestUART> u =
        std::make_unique<sabre::Testing::TestUART>();
    auto *u_ptr = u.get();
    sabre::UARTStreamBuf buffer(std::move(u), 128);
    std::ostream stream(&buffer);

    sabre::Logging::set_level(sabre::LoggingLevel::DEBUG);
    sabre::OStreamLogHandlerSharedPtr handler =
        std::make_shared<sabre::OStreamLogHandler>(stream);

    sabre::Logging::add_handler(handler);

    sabre::Logging::log(sabre::LoggingLevel::INFO, "TestLogger", "Testmessage");

    sabre::Logging::remove_handler(handler);

    ASSERT_TRUE(u_ptr->_buf.contains("TestLogger"));
    ASSERT_TRUE(u_ptr->_buf.contains("Testmessage"));
}

TEST(LogBufferHandler, Logging)
{
    sabre::Logging::set_level(sabre::LoggingLevel::DEBUG);
    sabre::LogBufferHandlerSharedPtr handler =
        std::make_shared<sabre::LogBufferHandler>(1);

    sabre::Logging::add_handler(handler);

    sabre::Logging::log(sabre::LoggingLevel::INFO, "TestLogger", "Testmessage");

    ASSERT_TRUE(handler->get_buffer()[0].contains("TestLogger"));
}

TEST(LogBufferHandler, Overflow)
{
    sabre::Logging::set_level(sabre::LoggingLevel::DEBUG);
    sabre::LogBufferHandlerSharedPtr handler =
        std::make_shared<sabre::LogBufferHandler>(2);

    sabre::Logging::add_handler(handler);

    for (uint32_t i = 0; i < 5; ++i)
        sabre::Logging::log(sabre::LoggingLevel::INFO, "TestLogger",
                            "Testmessage");
    ASSERT_TRUE(handler->get_buffer().size() == 2);
}