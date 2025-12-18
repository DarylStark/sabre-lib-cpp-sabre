#pragma once

#include <sabre/hal/input_gpio.hpp>
#include <sabre/hal/uart.hpp>
#include <string>

namespace sabre::impl::sabre_testing
{
    using sabre::hal::ISRHandler;
    using sabre::hal::ISRTrigger;

    class InputGPIO : public sabre::hal::InputGPIO
    {
    protected:
        bool _get_level() const override;

    public:
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(ISRHandler, ISRTrigger) override;
        void reset() override;

        bool level = true;
    };

    class TestUART : public sabre::hal::UART
    {
    public:
        void initialize();
        int write_byte(char data) const;
        std::string read_bytes(size_t max_bytes, uint32_t timeout_ms) override;
        void flush();
        void deinitialize();

        mutable std::string _buf;
    };
} // namespace sabre::impl::sabre_testing