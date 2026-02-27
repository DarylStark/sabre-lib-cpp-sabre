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
        sabre::hal::PinNumber _upperboundGpio;
        Factory &_factory;

        std::unordered_map<sabre::hal::PinNumber, ResourceVariant> _resources;

        template <typename T>
        bool _isType(sabre::hal::PinNumber) const;
        template <typename T, typename FactoryFunc>
        T &_getOrCreateGpio(sabre::hal::PinNumber pin, FactoryFunc factoryFunc);

        bool _isFreePin(sabre::hal::PinNumber pin) const noexcept;
        bool _isValidGpio(sabre::hal::PinNumber pin) const noexcept;

    public:
        using Ptr = GpioResourceManager *;
        using SharedPtr = std::shared_ptr<GpioResourceManager>;
        using UniquePtr = std::unique_ptr<GpioResourceManager>;

        GpioResourceManager(Factory &factory,
                            sabre::hal::PinNumber upperboundGpio) noexcept;
        sabre::hal::InputGpio &getInputGpio(sabre::hal::PinNumber pin);
        sabre::hal::OutputGpio &getOutputGpio(sabre::hal::PinNumber pin);
        sabre::hal::Gpio &getGpio(sabre::hal::PinNumber pin);
    };
} // namespace sabre::core