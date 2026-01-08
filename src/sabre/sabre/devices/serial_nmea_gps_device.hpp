#pragma once

#include "../hal/serial.hpp"
#include "../parsers/nmea_validator.hpp"
#include "./gps_device.hpp"

namespace sabre::devices
{
    using sabre::hal::Serial;
    class SerialNmeaGpsDevice : public GpsDevice
    {
    private:
        sabre::hal::Serial::Ptr _uartPtr;
        sabre::hal::Serial::Ptr _outputUartPtr;
        sabre::parsers::NmeaValidator _nmeaValidator;
        sabre::parsers::NmeaParser _nmeaParser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(Serial::Ptr uartPtr);

        /**
         * @brief Virtual destructor.
         */
        virtual ~SerialNmeaGpsDevice() = default;

        void setUartPtr(Serial::Ptr uartPtr);
        void setOutputUartPtr(Serial::Ptr uartPtr);

        sabre::models::geo::Position getLastPosition() const override;
        bool isValidPosition() const override;
        bool readData() override;
    };
} // namespace sabre::devices