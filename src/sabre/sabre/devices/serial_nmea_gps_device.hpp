#pragma once

#include "../parsers/nmea_validator.hpp"
#include "../uart/uart.hpp"
#include "./gps_device.hpp"

namespace Sabre::Devices
{
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        Sabre::UARTPtr _uart;
        Sabre::UARTPtr _output_uart;
        Sabre::Parsers::NMEAValidator _nmea_validator;
        Sabre::Parsers::NMEA_Parser _nmea_parser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(Sabre::UARTPtr uart);

        void set_uart_ptr(Sabre::UARTPtr uart);
        void set_output_uart_ptr(Sabre::UARTPtr uart);

        Sabre::Models::Position get_last_position() const override;
        bool is_valid_position() const override;
        bool read() override;
    };
} // namespace Sabre::Devices