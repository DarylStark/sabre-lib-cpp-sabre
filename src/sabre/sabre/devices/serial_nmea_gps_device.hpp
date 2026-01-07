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
        sabre::hal::Uart::Ptr _uartPtr;
        sabre::hal::Uart::Ptr _outputUartPtr;
        sabre::parsers::NmeaValidator _nmeaValidator;
        sabre::parsers::NmeaParser _nmeaParser;

    public:
        SerialNmeaGpsDevice();
        SerialNmeaGpsDevice(Uart::Ptr uartPtr);

        /**
         * @brief Virtual destructor.
         */
        virtual ~SerialNmeaGpsDevice() = default;

        void setUartPtr(Uart::Ptr uartPtr);
        void setOutputUartPtr(Uart::Ptr uartPtr);

        sabre::models::geo::Position getLastPosition() const override;
        bool isValidPosition() const override;
        bool readData() override;
    };
} // namespace sabre::devices