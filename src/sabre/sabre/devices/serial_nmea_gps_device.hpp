#pragma once

#include "../parsers/nmea_validator.hpp"
#include "../uart/uart.hpp"
#include "./gps_device.hpp"

namespace sabre::devices
{
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        sabre::UARTPtr _uart;
        sabre::UARTPtr _output_uart;
        sabre::parsers::NMEAValidator _nmea_validator;
        sabre::parsers::NMEA_Parser _nmea_parser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(sabre::UARTPtr uart);

        void set_uart_ptr(sabre::UARTPtr uart);
        void set_output_uart_ptr(sabre::UARTPtr uart);

        sabre::models::Position get_last_position() const override;
        bool is_valid_position() const override;
        bool read() override;
    };
} // namespace sabre::devices