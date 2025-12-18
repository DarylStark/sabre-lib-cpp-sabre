#pragma once

#include "gpio.hpp"

namespace sabre::hal
{
    /**
     * @brief Abstract class for output GPIO pins.
     *
     * This class defines the interface for output GPIO pins. It provides
     * methods to set the GPIO pin to high or low level, or to a specific level.
     */
    class OutputGPIO : public GPIO
    {
    public:
        using Ptr = OutputGPIO *;
        using SharedPtr = std::shared_ptr<OutputGPIO>;
        using UniquePtr = std::unique_ptr<OutputGPIO>;

        /**
         * @brief Set the GPIO pin to high level.
         */
        virtual void set_high() = 0;

        /**
         * @brief Set the GPIO pin to low level.
         */
        virtual void set_low() = 0;

        /**
         * @brief Set the GPIO to a specific level.
         *
         * @param level The level to set the GPIO pin to. If true, sets to high;
         */
        virtual void set_level(bool level) = 0;
    };
}; // namespace sabre::hal