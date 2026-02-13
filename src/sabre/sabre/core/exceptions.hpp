#pragma once

#include <stdexcept>
#include <string>

namespace sabre::core
{
    /**
     * @brief Base class for all Sabre exceptions.
     *
     * This class is used as a base for all exceptions that are thrown by the
     * Sabre library. It inherits from `std::runtime_error` to provide a
     * standard way to handle exceptions in C++.
     */
    class SabreException : public std::runtime_error
    {
    public:
        /**
         * @brief Default constructor for SabreException.
         *
         * This constructor initializes the exception with a default message.
         */
        explicit SabreException(const std::string &message) noexcept;
    };

    class ResourceManagerException : public SabreException
    {
    public:
        explicit ResourceManagerException(const std::string &message) noexcept;
    };

    class GpioInUseException : public ResourceManagerException
    {
    public:
        explicit GpioInUseException(const std::string &message) noexcept;
    };

    class GpioUnavailableException : public ResourceManagerException
    {
    public:
        explicit GpioUnavailableException() noexcept;
    };

    /**
     * @brief Exception thrown by implementation on API errors.
     *
     * This exception is thrown when an operation is attempted on a API that
     * failed.
     */
    class ApiError : public SabreException
    {
    protected:
        /**
         * @brief Constructor for ApiError with a custom message.
         *
         * This constructor initializes the exception with a specific error
         * message. This is meant for derived classes to provide more
         * context-specific error messages. It should not be used to initialize
         * ApiError instances directly.
         *
         * @param msg The error message to be associated with the exception.
         */
        explicit ApiError(const std::string &msg) noexcept;

    public:
        /**
         * @brief Default constructor for ApiError.
         *
         * This constructor initializes the exception with a default message
         * indicating an unknown API error.
         */
        explicit ApiError() noexcept;
    };
} // namespace sabre::core