#pragma once

#include "../log/logging.hpp"
#include <memory>

namespace sabre::hal
{
    using PinNumber = int32_t;
    /**
     * @brief Base class for Gpio operations.
     *
     * This class provides a base interface for Gpio operations. It can be
     * extended to implement specific Gpio functionalities.
     */
    class Gpio
    {
    private:
        PinNumber _pinNumber = 0;
        sabre::log::LogHelper _log_helper;

    public:
        using Ptr = Gpio *;
        using SharedPtr = std::shared_ptr<Gpio>;
        using UniquePtr = std::unique_ptr<Gpio>;

    public:
        Gpio() noexcept = default;
        Gpio(PinNumber pinNumber) noexcept;
        PinNumber getPinNumber() const noexcept;
        sabre::log::LogHelper &getLogHelper();

        /**
         * @brief Virtual destructor.
         */
        virtual ~Gpio() noexcept = default;

        /**
         * @brief Default constructor for GPIO.
         *
         * This constructor initializes the GPIO object with default settings.
         */
        virtual void reset() = 0;
    };

}; // namespace sabre::hal