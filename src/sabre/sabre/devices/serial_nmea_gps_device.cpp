#include "serial_nmea_gps_device.hpp"

namespace sabre::devices
{
    SerialNmeaGpsDevice::SerialNmeaGpsDevice()
        : _uartPtr(nullptr), _outputUartPtr(nullptr)
    {
    }

    SerialNmeaGpsDevice::SerialNmeaGpsDevice(Uart::Ptr uartPtr)
        : _uartPtr(uartPtr), _outputUartPtr(nullptr)
    {
    }

    void SerialNmeaGpsDevice::setUartPtr(Uart::Ptr uartPtr)
    {
        _uartPtr = uartPtr;
    }

    void SerialNmeaGpsDevice::setOutputUartPtr(Uart::Ptr uartPtr)
    {
        _outputUartPtr = uartPtr;
    }

    sabre::models::geo::Position SerialNmeaGpsDevice::getLastPosition() const
    {
        return _nmeaParser.getLastPosition();
    }

    bool SerialNmeaGpsDevice::isValidPosition() const
    {
        return _nmeaParser.getLastPosition().isValid();
    }

    bool SerialNmeaGpsDevice::readData()
    {
        if (!_uartPtr)
            return false;

        std::string x = _uartPtr->readBytes(1, 50);
        if (!x.empty())
        {
            if (_outputUartPtr)
                for (const auto &byte : x)
                    _outputUartPtr->writeByte(byte);

            for (const auto &c : x)
            {
                _nmeaValidator.addCharacter(c);
                if (_nmeaValidator.isAccepted())
                {
                    _nmeaParser.addSentence(_nmeaValidator.getBuffer());
                    _nmeaValidator.reset();
                }
                else if (_nmeaValidator.isError())
                {
                    _nmeaValidator.reset();
                    _nmeaValidator.addCharacter(c);
                }
            }
            return true;
        }
        return false;
    }
} // namespace sabre::devices