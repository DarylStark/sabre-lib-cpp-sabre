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
        uint32_t _upperboundUart;

        std::unordered_map<uint32_t, sabre::hal::Serial::UniquePtr>
            _uartResources;
        std::unordered_map<uint32_t, sabre::hal::Serial::UniquePtr>
            _usbCdcResources;

    public:
        using Ptr = SerialResourceManager *;
        using SharedPtr = std::shared_ptr<SerialResourceManager>;
        using UniquePtr = std::unique_ptr<SerialResourceManager>;

        SerialResourceManager(Factory &factory,
                              uint32_t upperboundUart) noexcept;
        void configureUart(uint32_t uartNumber, int32_t baudRate,
                           const sabre::hal::Gpio &txPin,
                           const sabre::hal::Gpio &rxPin, size_t bufferSize);
        sabre::hal::Serial &getUart(uint32_t uartNumber) const;

        void configureUsbCdc(uint32_t index, size_t bufferSize);
        sabre::hal::Serial &getUsbCdc(uint32_t index) const;
    };
} // namespace sabre::core