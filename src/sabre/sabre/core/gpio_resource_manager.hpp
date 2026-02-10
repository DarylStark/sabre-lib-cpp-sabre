#pragma once
#include "../hal/gpio.hpp"
#include "../hal/input_gpio.hpp"
#include "../hal/output_gpio.hpp"
#include "./factory.hpp"
#include <unordered_map>
#include <variant>

namespace sabre::core
{
    class GpioResourceManager
    {
    public:
        using ResourceVariant = std::variant<sabre::hal::InputGpio::UniquePtr,
                                             sabre::hal::OutputGpio::UniquePtr,
                                             sabre::hal::Gpio::UniquePtr>;

    private:
        int32_t _upperboundGpio;
        Factory &_factory;

        std::unordered_map<int32_t, ResourceVariant> _resources;

        template <typename T>
        bool _isType(int32_t pin) const;
        template <typename T, typename FactoryFunc>
        T &_getOrCreateGpio(int32_t pin, FactoryFunc factoryFunc);

        bool _isFreePin(int32_t pin) const;
        bool _isValidGpio(int32_t pin) const;

    public:
        using Ptr = GpioResourceManager *;
        using SharedPtr = std::shared_ptr<GpioResourceManager>;
        using UniquePtr = std::unique_ptr<GpioResourceManager>;

        GpioResourceManager(Factory &factory, int32_t upperboundGpio);
        sabre::hal::InputGpio &getInputGpio(int32_t pin);
        sabre::hal::OutputGpio &getOutputGpio(int32_t pin);
        sabre::hal::Gpio &getGpio(int32_t pin);
    };
} // namespace sabre::core