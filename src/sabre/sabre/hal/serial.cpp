#include "serial.hpp"

namespace sabre::hal
{
    sabre::log::LogHelper &Serial::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::hal