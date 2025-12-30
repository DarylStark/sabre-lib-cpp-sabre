#pragma once

#include "gpio.hpp"
#include <functional>
#include <memory>

namespace sabre::hal
{
    using ISRHandler = std::function<void(int)>;

    /**
     * @brief Structure to hold the configuration for an ISR handler.
     *
     * This structure contains the handler function and the GPIO pin number
     * associated with the interrupt.
     */
    struct ISRConfig
    {
        using Ptr = ISRConfig *;
        using SharedPtr = std::shared_ptr<ISRConfig>;
        using UniquePtr = std::unique_ptr<ISRConfig>;

        ISRHandler handler;
        int gpio;
    };

    /**
     * @brief Enumeration for the trigger types of an ISR.
     *
     * This enumeration defines the different types of triggers that can be used
     * for an interrupt service routine (ISR).
     */
    enum class ISRTrigger : int
    {
        RISING,
        FALLING,
        BOTH,
        LOW,
        HIGH
    };

    /**
     * @brief Base class for input GPIO operations.
     *
     * This class provides an interface for input GPIO operations, including
     * reading levels, setting pull-up/pull-down resistors, and handling
     * interrupts.
     */
    class InputGpio : public Gpio
    {
    public:
        using Ptr = InputGpio *;
        using SharedPtr = std::shared_ptr<InputGpio>;
        using UniquePtr = std::unique_ptr<InputGpio>;

    protected:
        bool _inverseLevel = false;
        virtual bool _getLevel() const = 0;

    public:
        /**
         * @brief Default constructor for InputGpio.
         *
         * This constructor initializes the InputGpio object with default
         * settings.
         */
        virtual bool getLevel() const;

        /**
         * @brief Sets the level inversion for the GPIO pin.
         *
         * This method allows the user to set whether the GPIO pin's level is
         * inverted. If set to true, a logical high will be interpreted as low,
         * and vice versa.
         *
         * @param level A boolean value indicating whether to invert the level.
         *              Default is false, meaning no inversion.
         */
        virtual void setInverseLevel(bool level = false);

        /**
         * @brief Gets the current level inversion setting.
         *
         * This method returns the current setting for level inversion. If
         * inversion is enabled, it will return true; otherwise, it will return
         * false.
         *
         * @return A boolean indicating whether the level is inverted.
         */
        virtual bool getInverseLevel() const;

        /**
         * @brief Enable pull up resistor for the GPIO pin.
         */
        virtual void enablePullup() = 0;

        /**
         * @brief Enable pull down resistor for the GPIO pin.
         */
        virtual void enablePulldown() = 0;

        /**
         * @brief Disable pull up resistor for the GPIO pin.
         */
        virtual void disablePullup() = 0;

        /**
         * @brief Disable pull down resistor for the GPIO pin.
         */
        virtual void disablePulldown() = 0;

        /**
         * @brief Add an interrupt handler for the GPIO pin.
         *
         * This method allows the user to register an interrupt service routine
         * (ISR) handler for the GPIO pin. The handler will be called when the
         * specified trigger condition is met.
         *
         * @param handler The ISR handler function to be called on interrupt.
         * @param trigger The trigger condition for the interrupt.
         */
        virtual void addInterruptHandler(ISRHandler, ISRTrigger) = 0;
    };
}; // namespace sabre::hal