#pragma once

#include "../parsers/gps.hpp"

namespace Sabre::Devices
{
    class GpsDevice
    {
    public:
        virtual Sabre::Models::Position get_last_position() const = 0;
        virtual bool is_valid_position() const = 0;
        virtual bool read() = 0;
    };
} // namespace Sabre::Devices