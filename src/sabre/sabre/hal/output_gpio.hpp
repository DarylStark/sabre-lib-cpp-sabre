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
    class OutputGpio : public Gpio
    {
    public:
        using Ptr = OutputGpio *;
        using SharedPtr = std::shared_ptr<OutputGpio>;
        using UniquePtr = std::unique_ptr<OutputGpio>;

        /**
         * @brief Set the GPIO pin to high level.
         */
        virtual void setHigh() = 0;

        /**
         * @brief Set the GPIO pin to low level.
         */
        virtual void setLow() = 0;

        /**
         * @brief Set the GPIO to a specific level.
         *
         * @param level The level to set the GPIO pin to. If true, sets to high;
         */
        virtual void setLevel(bool level) = 0;
    };
}; // namespace sabre::hal