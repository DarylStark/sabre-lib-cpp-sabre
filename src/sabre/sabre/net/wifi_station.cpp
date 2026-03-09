#include "wifi_station.hpp"

namespace sabre::net
{
    sabre::log::LogHelper &WifiStation::getLogHelper()
    {
        return _log_helper;
    }
} // namespace sabre::net