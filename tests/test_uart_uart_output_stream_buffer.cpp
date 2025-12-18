#include "sabre_testing/uart/uart.hpp"
#include <gtest/gtest.h>
#include <sabre/uart/uart.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>
#include <string>

TEST(UARTStreamBuf, UseAsOStreamObject)
{
    std::unique_ptr<sabre::Testing::TestUART> u =
        std::make_unique<sabre::Testing::TestUART>();
    auto *u_ptr = u.get();
    sabre::UARTStreamBuf buffer(std::move(u), 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "Testtext");
}

TEST(UARTStreamBuf, OverflowBuffer)
{
    std::unique_ptr<sabre::Testing::TestUART> u =
        std::make_unique<sabre::Testing::TestUART>();
    auto *u_ptr = u.get();
    sabre::UARTStreamBuf buffer(std::move(u), 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "3456");
}