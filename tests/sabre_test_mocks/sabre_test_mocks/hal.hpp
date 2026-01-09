#pragma once

#include <sabre/hal/input_gpio.hpp>
#include <sabre/hal/output_gpio.hpp>
#include <sabre/hal/serial.hpp>
#include <string>

namespace sabre::impl::sabre_test_mocks
{
    using sabre::hal::ISRHandler;
    using sabre::hal::ISRTrigger;

    class StInputGpio : public sabre::hal::InputGpio
    {
    protected:
        bool _getLevel() const override;

    public:
        void enablePullup() override;
        void enablePulldown() override;
        void disablePullup() override;
        void disablePulldown() override;
        void addInterruptHandler(ISRHandler, ISRTrigger) override;
        void reset() override;

        bool level = true;
    };

    class StOutputGpio : public sabre::hal::OutputGpio
    {
    public:
        void setLevel(bool level) override;
        void setHigh() override;
        void setLow() override;
        void reset() override;
    };

    class TestUART : public sabre::hal::Serial
    {
    public:
        void initialize();
        int writeByte(char data) const;
        std::string readBytes(size_t maxBytes, uint32_t timeoutMs) override;
        void flush();
        void deinitialize();

        mutable std::string _buf;
    };
} // namespace sabre::impl::sabre_test_mocks