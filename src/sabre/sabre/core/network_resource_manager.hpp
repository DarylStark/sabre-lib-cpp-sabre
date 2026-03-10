#pragma once

#include "../net/mqtt.hpp"
#include "../net/wifi_soft_ap.hpp"
#include "../net/wifi_station.hpp"
#include "factory.hpp"
#include <unordered_map>

namespace sabre::core
{
    class NetworkResourceManager
    {
    private:
        Factory &_factory;
        sabre::log::LogManager &_logManager;

        // Local lazy resources
        sabre::net::WifiSoftAp::UniquePtr _wifi_soft_ap;
        sabre::net::WifiStation::UniquePtr _wifi_station;
        std::unordered_map<std::string, sabre::net::MqttClient::UniquePtr>
            _mqttClients;

    public:
        NetworkResourceManager(Factory &factory,
                               sabre::log::LogManager &logManager);
        // Lazy resources
        sabre::net::WifiSoftAp &getWifiSoftAp();
        sabre::net::WifiStation &getWifiStation();
        sabre::net::MqttClient &getMqttClient(const std::string &identifier);
    };
} // namespace sabre::core