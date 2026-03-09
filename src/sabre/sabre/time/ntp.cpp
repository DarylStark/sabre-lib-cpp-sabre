#include "ntp.hpp"

namespace sabre::time
{
    sabre::log::LogHelper &NtpClient::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::time