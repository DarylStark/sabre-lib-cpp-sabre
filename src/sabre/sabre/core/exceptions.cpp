#include "exceptions.hpp"

namespace sabre::core
{
    SabreException::SabreException(const std::string &message) noexcept
        : std::runtime_error(message)
    {
    }

    ResourceManagerException::ResourceManagerException(
        const std::string &msg) noexcept
        : SabreException(msg)
    {
    }

    GpioInUseException::GpioInUseException(const std::string &msg) noexcept
        : ResourceManagerException(msg)
    {
    }

    GpioUnavailableException::GpioUnavailableException() noexcept
        : ResourceManagerException("GPIO unavailable")
    {
    }

    ApiError::ApiError(const std::string &msg) noexcept : SabreException(msg) {}

    ApiError::ApiError() noexcept : SabreException("Unknown API error") {}
} // namespace sabre::core
