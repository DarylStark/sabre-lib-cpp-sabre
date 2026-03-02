#pragma once

#include "../hal/serial.hpp"
#include "factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class SerialResourceManager
    {
    private:
        Factory &_factory;
        sabre::hal::UartNumber _upperboundUart;

        std::unordered_map<sabre::hal::UartNumber,
                           sabre::hal::Serial::UniquePtr>
            _uartResources;
        std::unordered_map<sabre::hal::UsbIndex, sabre::hal::Serial::UniquePtr>
            _usbCdcResources;

        sabre::log::LogManager &_logManager;

    public:
        using Ptr = SerialResourceManager *;
        using SharedPtr = std::shared_ptr<SerialResourceManager>;
        using UniquePtr = std::unique_ptr<SerialResourceManager>;

        SerialResourceManager(Factory &factory,
                              sabre::hal::UartNumber upperboundUart,
                              sabre::log::LogManager &logManager) noexcept;
        void configureUart(sabre::hal::UartNumber uartNumber,
                           sabre::hal::BaudRate baudRate,
                           const sabre::hal::Gpio &txPin,
                           const sabre::hal::Gpio &rxPin, size_t bufferSize);
        sabre::hal::Serial &getUart(sabre::hal::UartNumber uartNumber) const;

        void configureUsbCdc(sabre::hal::UsbIndex index, size_t bufferSize);
        sabre::hal::Serial &getUsbCdc(sabre::hal::UsbIndex index) const;
    };
} // namespace sabre::core