#include "exceptions.hpp"

namespace Sabre
{
    SabreException::SabreException(const std::string &message)
        : std::runtime_error(message)
    {
    }

    APIError::APIError(const std::string &msg) : SabreException(msg) {}

    APIError::APIError() : SabreException("Unknown API error") {}
} // namespace Sabre
