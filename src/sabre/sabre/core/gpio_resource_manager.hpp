#pragma once
#include "../hal/input_gpio.hpp"
#include "../hal/output_gpio.hpp"
#include "./factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class GpioResourceManager
    {
    private:
        using InputGpioMap = std::unordered_map<uint32_t, InputGpio::SharedPtr>;
        using OutputGpioMap =
            std::unordered_map<int32_t, OutputGpio::SharedPtr>;

        uint32_t _max_gpios;
        Factory &_factory;
        InputGpioMap _input_gpios;
        OutputGpioMap _output_gpios;

        enum class GpioType
        {
            None,
            Input,
            Output
        };

        GpioType _pinInUse(int32_t pin) const;

    public:
        GpioResourceManager(Factory &factory, int32_t max_gpios);
        InputGpio &getInputGpio(int32_t pin);
        OutputGpio &getOutputGpio(int32_t pin);
    };
} // namespace sabre::core