#include "sabre_testing/uart/uart.hpp"
#include <gtest/gtest.h>
#include <sabre/logging/log_handlers.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>

#include <iostream>

TEST(OStreamLogHandler, Logging)
{
    std::unique_ptr<Sabre::Testing::TestUART> u =
        std::make_unique<Sabre::Testing::TestUART>();
    auto *u_ptr = u.get();
    Sabre::UARTStreamBuf buffer(std::move(u), 128);
    std::ostream stream(&buffer);

    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::OStreamLogHandlerSharedPtr handler =
        std::make_shared<Sabre::OStreamLogHandler>(stream);

    Sabre::Logging::add_handler(handler);

    Sabre::Logging::log(Sabre::LoggingLevel::INFO, "TestLogger", "Testmessage");

    Sabre::Logging::remove_handler(handler);

    ASSERT_TRUE(u_ptr->_buf.contains("TestLogger"));
    ASSERT_TRUE(u_ptr->_buf.contains("Testmessage"));
}

TEST(LogBufferHandler, Logging)
{
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::LogBufferHandlerSharedPtr handler =
        std::make_shared<Sabre::LogBufferHandler>(1);

    Sabre::Logging::add_handler(handler);

    Sabre::Logging::log(Sabre::LoggingLevel::INFO, "TestLogger", "Testmessage");

    ASSERT_TRUE(handler->get_buffer()[0].contains("TestLogger"));
}

TEST(LogBufferHandler, Overflow)
{
    Sabre::Logging::set_level(Sabre::LoggingLevel::DEBUG);
    Sabre::LogBufferHandlerSharedPtr handler =
        std::make_shared<Sabre::LogBufferHandler>(2);

    Sabre::Logging::add_handler(handler);

    for (uint32_t i = 0; i < 5; ++i)
        Sabre::Logging::log(Sabre::LoggingLevel::INFO, "TestLogger",
                            "Testmessage");
    ASSERT_TRUE(handler->get_buffer().size() == 2);
}