#pragma once

#include "../hal/serial.hpp"
#include "../parsers/nmea_validator.hpp"
#include "./gps_device.hpp"

namespace sabre::devices
{
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        sabre::hal::Serial::Ptr _uartPtr;
        sabre::hal::Serial::Ptr _outputUartPtr;
        sabre::parsers::NmeaValidator _nmeaValidator;
        sabre::parsers::NmeaParser _nmeaParser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(sabre::hal::Serial::Ptr uartPtr);

        /**
         * @brief Virtual destructor.
         */
        virtual ~SerialNmeaGpsDevice() = default;

        void setUartPtr(sabre::hal::Serial::Ptr uartPtr);
        void setOutputUartPtr(sabre::hal::Serial::Ptr uartPtr);

        sabre::models::geo::Position getLastPosition() const noexcept override;
        bool isValidPosition() const noexcept override;
        bool readData() override;
    };
} // namespace sabre::devices