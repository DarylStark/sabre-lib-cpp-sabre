#include "network_resource_manager.hpp"

namespace sabre::core
{
    NetworkResourceManager::NetworkResourceManager(
        Factory &factory, sabre::log::LogManager &logManager)
        : _factory(factory), _logManager(logManager)
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

    sabre::net::MqttClient &
    NetworkResourceManager::getMqttClient(const std::string &identifier)
    {
        if (_mqttClients.find(identifier) == _mqttClients.end())
        {
            _mqttClients[identifier] = _factory.createMqttClient();
            _mqttClients[identifier]->getLogHelper().createLogger(
                _logManager, "MqttClient_" + identifier);
        }
        return *_mqttClients[identifier];
    }

    sabre::net::HttpServer &
    NetworkResourceManager::getHttpServer(const std::string &identifier)
    {
        if (_httpServers.find(identifier) == _httpServers.end())
        {
            _httpServers[identifier] = _factory.createHttpServer();
            _httpServers[identifier]->getLogHelper().createLogger(
                _logManager, "HttpServer_" + identifier);
        }
        return *_httpServers[identifier];
    }
} // namespace sabre::core