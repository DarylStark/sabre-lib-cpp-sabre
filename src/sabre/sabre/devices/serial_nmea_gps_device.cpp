#include "serial_nmea_gps_device.hpp"

namespace Sabre::Devices
{
    SerialNmeaGpsDevice::SerialNmeaGpsDevice()
        : _uart(nullptr), _output_uart(nullptr)
    {
    }

    SerialNmeaGpsDevice::SerialNmeaGpsDevice(Sabre::UARTPtr uart)
        : _uart(uart), _output_uart(nullptr)
    {
    }

    void SerialNmeaGpsDevice::set_uart_ptr(Sabre::UARTPtr uart)
    {
        _uart = uart;
    }

    void SerialNmeaGpsDevice::set_output_uart_ptr(Sabre::UARTPtr uart)
    {
        _output_uart = uart;
    }

    Sabre::Models::Position SerialNmeaGpsDevice::get_last_position() const
    {
        return _nmea_parser.get_last_position();
    }

    bool SerialNmeaGpsDevice::is_valid_position() const
    {
        return _nmea_parser.get_last_position().is_valid();
    }

    bool SerialNmeaGpsDevice::read()
    {
        if (!_uart)
            return false;

        std::string x = _uart->read_bytes(1, 50);
        if (!x.empty())
        {
            if (_output_uart)
                for (const auto &byte : x)
                    _output_uart->write_byte(byte);

            for (const auto &c : x)
            {
                _nmea_validator.add_character(c);
                if (_nmea_validator.is_accepted())
                {
                    _nmea_parser.add_scentence(_nmea_validator.get_buffer());
                    _nmea_validator.reset();
                }
                else if (_nmea_validator.is_error())
                {
                    _nmea_validator.reset();
                    _nmea_validator.add_character(c);
                }
            }
            return true;
        }
        return false;
    }
} // namespace Sabre::Devices