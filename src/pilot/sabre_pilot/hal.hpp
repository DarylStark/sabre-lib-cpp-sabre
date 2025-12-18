#pragma once

#include "../simulator/device.hpp"
#include <sabre/hal/uart.hpp>

namespace sabre::impl::pilot
{
    class Uart : public sabre::hal::Uart
    {
    private:
        Device *_device;
        uint32_t _uart_number;
        size_t _buffer_size;

    public:
        Uart(Device *device, uint32_t number, size_t buffer_size);
        void initialize() override;
        int writeByte(char data) const override;
        std::string readBytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush() override;
        void deinitialize() override;
    };

    class Gpio : public sabre::hal::Gpio
    {
    public:
        void reset() override;
    };

    class InputGpio : public sabre::hal::InputGpio
    {
    private:
        Device *_device;
        uint32_t _pin;

    protected:
        bool _getLevel() const override;

    public:
        InputGpio(Device *device, uint32_t pin);

        void reset() override;
        void enablePullup() override;
        void enablePulldown() override;
        void disablePullup() override;
        void disablePulldown() override;
        void addInterruptHandler(sabre::hal::ISRHandler,
                                 sabre::hal::ISRTrigger) override;
    };

    class OutputGpio : public sabre::hal::OutputGpio
    {
    private:
        Device *__device;
        uint32_t _pin;

    public:
        OutputGpio(Device *device, uint32_t pin);
        void reset() override;
        void setHigh() override;
        void setLow() override;
        void setLevel(bool level) override;
    };
} // namespace sabre::impl::pilot