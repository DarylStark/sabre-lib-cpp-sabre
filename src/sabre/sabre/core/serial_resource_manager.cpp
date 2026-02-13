#include "serial_resource_manager.hpp"

namespace sabre::core
{
    SerialResourceManager::SerialResourceManager(
        Factory &factory, uint32_t upperboundUart) noexcept
        : _factory(factory), _upperboundUart(upperboundUart)
    {
    }

    void SerialResourceManager::configureUart(uint32_t uartNumber,
                                              int32_t baudRate,
                                              const sabre::hal::Gpio &txPin,
                                              const sabre::hal::Gpio &rxPin,
                                              size_t bufferSize)
    {
        if (uartNumber >= _upperboundUart)
        {
            throw std::out_of_range("UART number exceeds upper bound");
        }

        if (_uartResources.find(uartNumber) != _uartResources.end())
        {
            throw std::runtime_error("UART already configured");
        }

        auto uart = _factory.createUartObject(uartNumber, baudRate,
                                              txPin.getPinNumber(),
                                              rxPin.getPinNumber(), bufferSize);
        _uartResources[uartNumber] = std::move(uart);
    }

    sabre::hal::Serial &
    SerialResourceManager::getUart(uint32_t uartNumber) const
    {
        auto it = _uartResources.find(uartNumber);
        if (it == _uartResources.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("UART not configured. Please configure it "
                                     "first using the configureUart method.");
        }
        return *(it->second);
    }

    void SerialResourceManager::configureUsbCdc(uint32_t index,
                                                size_t bufferSize)
    {
        if (_usbCdcResources.find(index) != _usbCdcResources.end())
        {
            throw std::runtime_error("USB CDC already configured");
        }

        auto usbCdc = _factory.createUsbCdc(index, bufferSize);
        _usbCdcResources[index] = std::move(usbCdc);
    }

    sabre::hal::Serial &SerialResourceManager::getUsbCdc(uint32_t index) const
    {
        auto it = _usbCdcResources.find(index);
        if (it == _usbCdcResources.end())
        {
            // TODO: Custom exception
            throw std::runtime_error(
                "USB CDC not configured. Please configure it "
                "first using the configureUsbCdc method.");
        }
        return *(it->second);
    }
} // namespace sabre::core