#pragma once

#include "../types/types.hpp"
#include <cstddef> // For size_t
#include <cstdint> // For uint32_t
#include <memory>

namespace sabre::hal
{
    using UartNumber = uint32_t;
    using UsbIndex = uint32_t;
    using BaudRate = uint32_t;

    /**
     * @brief Abstract base class for Serial communication.
     *
     * This class defines the interface for Serial communication (UART, USB CDC,
     * etc.), providing methods to write a byte and flush the output buffer. It
     * is intended to be implemented by specific Serial communication classes.
     */
    class Serial
    {
    public:
        using Ptr = Serial *;
        using SharedPtr = std::shared_ptr<Serial>;
        using UniquePtr = std::unique_ptr<Serial>;

        /**
         * @brief Virtual destructor.
         */
        virtual ~Serial() noexcept = default;

        /**
         * @brief Initialize the Serial device.
         *
         * This method is used to initialize the Serial device, setting up any
         * necessary resources and configuration. It should be called before
         * any communication operations are performed.
         */
        virtual void initialize() = 0;

        /**
         * @brief Write a byte to the Serial device.
         *
         * This method is used to send a single byte of data over the Serial
         * interface.
         *
         * @param data The byte of data to be sent.
         *
         * @return Returns 0 on success, or a negative error code on failure.
         */
        virtual int writeByte(char data) const = 0;

        /**
         * @brief Read input data from the Serial device.
         *
         * This method is used to read incoming data from the Serial interface.
         * If no data is available within the specified timeout, an empty string
         * is returned. If only partial data is available during the timeout
         * period, it will be returned.
         *
         * @param maxBytes The maximum number of bytes to read.
         * @param timeoutMs The timeout in milliseconds.
         *
         * @return A string containing the received data.
         */
        virtual std::string readBytes(size_t maxBytes,
                                      sabre::types::MsTime timeoutInMs) = 0;

        /**
         * @brief Flush the output buffer of the Serial device.
         *
         * This method is used to ensure that all data in the output buffer is
         * sent to the Serial device. It is typically called after writing
         * multiple bytes to ensure that they are transmitted.
         */
        virtual void flush() = 0;

        /**
         * @brief Deinitialize the Serial device.
         *
         * This method is used to deinitialize the Serial device, releasing any
         * resources and cleaning up. It should be called when the Serial device
         * is no longer needed.
         */
        virtual void deinitialize() = 0;
    };
} // namespace sabre::hal