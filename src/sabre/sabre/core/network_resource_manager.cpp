#include "network_resource_manager.hpp"

namespace sabre::core
{
    NetworkResourceManager::NetworkResourceManager(
        Factory &factory, sabre::log::LogManager &logManger)
        : _factory(factory), _logManager(logManger)
    {
    }

    sabre::net::WifiSoftAp &NetworkResourceManager::getWifiSoftAp()
    {
        if (!_wifi_soft_ap)
        {
            _wifi_soft_ap = _factory.createWifiSoftAp();
            _wifi_soft_ap->getLogHelper().createLogger(_logManager,
                                                       "WifiSoftAp");
        }
        return *_wifi_soft_ap;
    }

    sabre::net::WifiStation &NetworkResourceManager::getWifiStation()
    {
        if (!_wifi_station)
        {
            _wifi_station = _factory.createWifiStation();
            _wifi_station->getLogHelper().createLogger(_logManager,
                                                       "WifiStation");
        }
        return *_wifi_station;
    }
} // namespace sabre::core