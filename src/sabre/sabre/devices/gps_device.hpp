#pragma once

#include "../parsers/gps.hpp"

namespace sabre::devices
{
    class GpsDevice
    {
    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~GpsDevice() = default;

        virtual sabre::models::geo::Position getLastPosition() const = 0;
        virtual bool isValidPosition() const = 0;
        virtual bool readData() = 0;
    };
} // namespace sabre::devices