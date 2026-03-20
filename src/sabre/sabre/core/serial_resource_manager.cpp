#include "serial_resource_manager.hpp"
#include "exceptions.hpp"

namespace sabre::core
{
    SerialResourceManager::SerialResourceManager(
        Factory &factory, sabre::hal::UartNumber upperboundUart,
        sabre::log::LogManager &logManager) noexcept
        : _logManager(logManager), _factory(factory),
          _upperboundUart(upperboundUart)
    {
    }

    void SerialResourceManager::configureUart(sabre::hal::UartNumber uartNumber,
                                              sabre::hal::BaudRate baudRate,
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
        uart->getLogHelper().createLogger(_logManager,
                                          "Uart_" + std::to_string(uartNumber));
        _uartResources[uartNumber] = std::move(uart);
    }

    sabre::hal::Serial &
    SerialResourceManager::getUart(sabre::hal::UartNumber uartNumber) const
    {
        auto it = _uartResources.find(uartNumber);
        if (it == _uartResources.end())
        {
            throw UartNotConfiguredException(
                "UART not configured. Please configure it "
                "first using the configureUart method.");
        }
        return *(it->second);
    }

    sabre::io::SerialStreamBuf &
    SerialResourceManager::getSerialStreamBufForUart(
        sabre::hal::UartNumber index)
    {
        if (_uartSerialStreamBuffers.find(index) ==
            _uartSerialStreamBuffers.end())
        {
            sabre::hal::Serial &uart = getUart(index);
            _uartSerialStreamBuffers[index] =
                std::make_unique<sabre::io::SerialStreamBuf>(&uart);
        }
        return *_uartSerialStreamBuffers[index];
    }

    std::ostream SerialResourceManager::getOutputStreamForUart(
        sabre::hal::UartNumber uartNumber)
    {
        auto &serial = getSerialStreamBufForUart(uartNumber);
        return std::ostream(&serial);
    }

    void SerialResourceManager::configureUsbCdc(sabre::hal::UsbIndex index,
                                                size_t bufferSize)
    {
        if (_usbCdcResources.find(index) != _usbCdcResources.end())
        {
            throw std::runtime_error("USB CDC already configured");
        }

        auto usbCdc = _factory.createUsbCdc(index, bufferSize);
        usbCdc->getLogHelper().createLogger(_logManager,
                                            "UsbCdc_" + std::to_string(index));
        _usbCdcResources[index] = std::move(usbCdc);
    }

    sabre::hal::Serial &
    SerialResourceManager::getUsbCdc(sabre::hal::UsbIndex index) const
    {
        auto it = _usbCdcResources.find(index);
        if (it == _usbCdcResources.end())
        {
            throw UsbCdcNotConfiguredException(
                "USB CDC not configured. Please configure it "
                "first using the configureUsbCdc method.");
        }
        return *(it->second);
    }

    sabre::io::SerialStreamBuf &
    SerialResourceManager::getSerialStreamBufForUsbCdc(
        sabre::hal::UsbIndex index)
    {
        if (_usbSerialStreamBuffers.find(index) ==
            _usbSerialStreamBuffers.end())
        {
            sabre::hal::Serial &usbCdc = getUsbCdc(index);
            _usbSerialStreamBuffers[index] =
                std::make_unique<sabre::io::SerialStreamBuf>(&usbCdc);
        }
        return *_usbSerialStreamBuffers[index];
    }

    std::ostream
    SerialResourceManager::getOutputStreamForUsbCdc(sabre::hal::UsbIndex index)
    {
        auto &serial = getSerialStreamBufForUsbCdc(index);
        return std::ostream(&serial);
    }
} // namespace sabre::core