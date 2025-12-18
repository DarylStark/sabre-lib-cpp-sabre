#pragma once

#include "../parsers/gps.hpp"

namespace sabre::devices
{
    class GpsDevice
    {
    public:
        virtual sabre::models::Position get_last_position() const = 0;
        virtual bool is_valid_position() const = 0;
        virtual bool read() = 0;
    };
} // namespace sabre::devices