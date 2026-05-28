#include "sabre_test_mocks/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/hal/serial.hpp>
#include <sabre/io/serial_output_stream_buffer.hpp>
#include <string>

TEST(SerialStreamBuf, UseAsOStreamObject)
{
    sabre::impl::sabre_test_mocks::TestUART uart;
    sabre::io::SerialStreamBuf buffer(&uart, 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << std::flush;
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(uart._buf, "Testtext");
}

TEST(SerialStreamBuf, OverflowBuffer)
{
    sabre::impl::sabre_test_mocks::TestUART u;
    sabre::io::SerialStreamBuf buffer(&u, 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << std::flush;
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u._buf, "Testtext123456");
}