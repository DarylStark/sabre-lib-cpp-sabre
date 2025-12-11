#include "sabre_testing/factory.hpp"
#include <gtest/gtest.h>

TEST(Factory, UARTOutputStreamBuffer)
{
    Sabre::Testing::Factory f;
    Sabre::UARTStreamBufUniquePtr buffer =
        f.create_uart_output_stream_buffer(1, 9600, 1, 2, 10);
    std::ostream str(buffer.get());
    ASSERT_NO_THROW(str << "test" << std::endl);
    ASSERT_NE(buffer, nullptr);
}

TEST(Factory, UARTOutputStreamBufferFailingUARTFactoryMethod)
{
    Sabre::Testing::Factory f(true);
    Sabre::UARTStreamBufUniquePtr buffer =
        f.create_uart_output_stream_buffer(1, 9600, 1, 2, 10);
    ASSERT_EQ(buffer, nullptr);
}