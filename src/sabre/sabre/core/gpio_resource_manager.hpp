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

        int32_t _upperboundGpio;
        Factory &_factory;
        InputGpioMap _inputGpios;
        OutputGpioMap _outputGpios;

        enum class GpioType
        {
            None,
            Input,
            Output
        };

        bool _isValidGpio(int32_t pin) const;
        GpioType _pinInUse(int32_t pin) const;

    public:
        using Ptr = GpioResourceManager *;
        using SharedPtr = std::shared_ptr<GpioResourceManager>;
        using UniquePtr = std::unique_ptr<GpioResourceManager>;

        GpioResourceManager(Factory &factory, int32_t upperboundGpio);
        InputGpio &getInputGpio(int32_t pin);
        OutputGpio &getOutputGpio(int32_t pin);
    };
} // namespace sabre::core