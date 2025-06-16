#ifndef _SABRE_TESTING_UART_H_
#define _SABRE_TESTING_UART_H_

#include <sabre/uart/uart.h>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <string>

namespace sabre::testing
{
    class TestUART : public sabre::UART
    {
    public:
        int write_byte(char data) const;
        void flush();

        mutable std::string _buf;
    };
} // namespace sabre::testing

#endif // _SABRE_TESTING_UART_H_