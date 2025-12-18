#pragma once

#include "../hal/uart.hpp"
#include "../parsers/nmea_validator.hpp"
#include "./gps_device.hpp"

namespace sabre::devices
{
    using sabre::hal::Uart;
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        sabre::hal::Uart::Ptr _uart;
        sabre::hal::Uart::Ptr _output_uart;
        sabre::parsers::NmeaValidator _nmea_validator;
        sabre::parsers::NmeaParser _nmea_parser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(Uart::Ptr uart);

        void set_uart_ptr(Uart::Ptr uart);
        void set_output_uart_ptr(Uart::Ptr uart);

        sabre::models::geo::Position get_last_position() const override;
        bool is_valid_position() const override;
        bool read() override;
    };
} // namespace sabre::devices