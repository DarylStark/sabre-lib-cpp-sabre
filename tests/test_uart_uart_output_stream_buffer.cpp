#include "sabre_testing/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/hal/uart.hpp>
#include <sabre/io/uart_output_stream_buffer.hpp>
#include <string>

TEST(UARTStreamBuf, UseAsOStreamObject)
{
    std::unique_ptr<sabre::impl::sabre_testing::TestUART> u =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::UARTStreamBuf buffer(std::move(u), 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "Testtext");
}

TEST(UARTStreamBuf, OverflowBuffer)
{
    std::unique_ptr<sabre::impl::sabre_testing::TestUART> u =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::UARTStreamBuf buffer(std::move(u), 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "3456");
}