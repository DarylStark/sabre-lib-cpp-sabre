#include "sabre_testing/uart/uart.h"
#include <gtest/gtest.h>
#include <sabre/uart/uart.h>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <string>

TEST(UARTStreamBuf, UseAsOStreamObject)
{
    std::shared_ptr<sabre::testing::TestUART> u =
        std::make_shared<sabre::testing::TestUART>();
    sabre::UARTStreamBuf buffer(u, 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u->_buf.compare("Testtext"), 0);
}

TEST(UARTStreamBuf, OverflowBuffer)
{
    std::shared_ptr<sabre::testing::TestUART> u =
        std::make_shared<sabre::testing::TestUART>();
    sabre::UARTStreamBuf buffer(u, 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u->_buf.compare("3456"), 0);
}