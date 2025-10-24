#ifndef SABRE_UART_H
#define SABRE_UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t
#include <memory>

namespace sabre
{
    /**
     * @brief Abstract base class for UART communication.
     *
     * This class defines the interface for UART communication, providing
     * methods to write a byte and flush the output buffer. It is intended to be
     * implemented by specific UART communication classes.
     */
    class UART
    {
    public:
        /**
         * @brief Initialize the UART device.
         *
         * This method is used to initialize the UART device, setting up any
         * necessary resources and configuration. It should be called before
         * any communication operations are performed.
         */
        virtual void initialize() = 0;

        /**
         * @brief Write a byte to the UART device.
         *
         * This method is used to send a single byte of data over the UART
         * interface.
         *
         * @param data The byte of data to be sent.
         *
         * @return Returns 0 on success, or a negative error code on failure.
         */
        virtual int write_byte(char data) const = 0;

        /**
         * @brief Flush the output buffer of the UART device.
         *
         * This method is used to ensure that all data in the output buffer is
         * sent to the UART device. It is typically called after writing
         * multiple bytes to ensure that they are transmitted.
         */
        virtual void flush() = 0;

        /**
         * @brief Deinitialize the UART device.
         *
         * This method is used to deinitialize the UART device, releasing any
         * resources and cleaning up. It should be called when the UART device
         * is no longer needed.
         */
        virtual void deinitialize() = 0;
    };
    using UARTPtr = UART *;
    using UARTUniquePtr = std::unique_ptr<UART>;
} // namespace sabre

#endif /* SABRE_UART_H */