#pragma once

#include <memory>

namespace sabre::hal
{
    /**
     * @brief Base class for Gpio operations.
     *
     * This class provides a base interface for Gpio operations. It can be
     * extended to implement specific Gpio functionalities.
     */
    class Gpio
    {
    private:
        int32_t _pinNumber = 0;

    public:
        using Ptr = Gpio *;
        using SharedPtr = std::shared_ptr<Gpio>;
        using UniquePtr = std::unique_ptr<Gpio>;

    public:
        Gpio() noexcept = default;
        Gpio(int32_t pinNumber) noexcept;
        int32_t getPinNumber() const noexcept;

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