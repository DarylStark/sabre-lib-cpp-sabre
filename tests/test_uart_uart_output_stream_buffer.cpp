#include "sabre_testing/uart/uart.hpp"
#include <gtest/gtest.h>
#include <sabre/uart/uart.hpp>
#include <sabre/uart/uart_output_stream_buffer.hpp>
#include <string>

TEST(UARTStreamBuf, UseAsOStreamObject)
{
    std::shared_ptr<sabre::testing::TestUART> u =
        std::make_shared<sabre::testing::TestUART>();
    sabre::UARTStreamBuf buffer(u, 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u->_buf, "Testtext");
}

TEST(UARTStreamBuf, OverflowBuffer)
{
    std::shared_ptr<sabre::testing::TestUART> u =
        std::make_shared<sabre::testing::TestUART>();
    sabre::UARTStreamBuf buffer(u, 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u->_buf, "3456");
}