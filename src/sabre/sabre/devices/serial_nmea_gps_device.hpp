#pragma once

#include "../hal/uart.hpp"
#include "../parsers/nmea_validator.hpp"
#include "./gps_device.hpp"

namespace sabre::devices
{
    using sabre::hal::UART;
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        sabre::hal::UART::Ptr _uart;
        sabre::hal::UART::Ptr _output_uart;
        sabre::parsers::NMEAValidator _nmea_validator;
        sabre::parsers::NMEA_Parser _nmea_parser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(UART::Ptr uart);

        void set_uart_ptr(UART::Ptr uart);
        void set_output_uart_ptr(UART::Ptr uart);

        sabre::models::Position get_last_position() const override;
        bool is_valid_position() const override;
        bool read() override;
    };
} // namespace sabre::devices