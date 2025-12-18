#pragma once

#include <memory>

namespace sabre::hal
{
    /**
     * @brief Base class for GPIO operations.
     *
     * This class provides a base interface for GPIO operations. It can be
     * extended to implement specific GPIO functionalities.
     */
    class GPIO
    {
    public:
        using Ptr = GPIO *;
        using SharedPtr = std::shared_ptr<GPIO>;
        using UniquePtr = std::unique_ptr<GPIO>;

    protected:
        bool _inverse_level = false;

    public:
        /**
         * @brief Default constructor for GPIO.
         *
         * This constructor initializes the GPIO object with default settings.
         */
        virtual void reset() = 0;
    };

}; // namespace sabre::hal