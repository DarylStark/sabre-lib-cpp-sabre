#include "exceptions.hpp"

namespace sabre::core
{
    SabreException::SabreException(const std::string &message)
        : std::runtime_error(message)
    {
    }

    ResourceManagerException::ResourceManagerException(const std::string &msg)
        : SabreException(msg)
    {
    }

    GpioInUseException::GpioInUseException(const std::string &msg)
        : ResourceManagerException(msg)
    {
    }

    GpioUnavailableException::GpioUnavailableException()
        : ResourceManagerException("GPIO unavailable")
    {
    }

    LogHandlerNotAvailableException::LogHandlerNotAvailableException(
        const std::string &msg)
        : SabreException(msg)
    {
    }

    ApiError::ApiError(const std::string &msg) : SabreException(msg) {}

    ApiError::ApiError() : SabreException("Unknown API error") {}
} // namespace sabre::core
