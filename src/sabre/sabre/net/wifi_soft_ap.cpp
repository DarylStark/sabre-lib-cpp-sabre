#include "wifi_soft_ap.hpp"

namespace sabre::net
{
    sabre::log::LogHelper &WifiSoftAp::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::net