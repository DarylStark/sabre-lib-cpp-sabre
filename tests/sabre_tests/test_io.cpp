#include "sabre_test_mocks/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/hal/serial.hpp>
#include <sabre/io/serial_output_stream_buffer.hpp>
#include <string>

TEST(SerialStreamBuf, UseAsOStreamObject)
{
    std::unique_ptr<sabre::impl::sabre_test_mocks::TestUART> u =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::SerialStreamBuf buffer(std::move(u), 128);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "Testtext");
}

TEST(SerialStreamBuf, OverflowBuffer)
{
    std::unique_ptr<sabre::impl::sabre_test_mocks::TestUART> u =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    auto *u_ptr = u.get();
    sabre::io::SerialStreamBuf buffer(std::move(u), 10);

    auto oldbuf = std::cout.rdbuf(&buffer);
    std::cout << "Testtext123456" << std::flush;
    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(u_ptr->_buf, "3456");
}
