#include "net.hpp"

namespace sabre::impl::sabre_test_mocks
{
    void StMQTTClient::connect(const std::string &hostname,
                               const std::string &clientId,
                               const std::string &username,
                               const std::string &password)
    {
        _is_connected = true;
        _is_started = true;
    }

    void StMQTTClient::disconnect()
    {
        _is_connected = false;
    }

    void StMQTTClient::stop()
    {
        _is_started = false;
    }

    bool StMQTTClient::isConnected() const noexcept
    {
        return _is_connected;
    }

    void StMQTTClient::publish(const std::string &topic,
                               const std::string &message,
                               sabre::net::MqttQos qos,
                               sabre::net::MqttRetain retain)
    {
        _published_messages.emplace_back(topic, message, qos, retain);
    }

    void StWifiStation::initialize() {}

    void StWifiStation::connect(const std::string &ssid,
                                const std::string &password)
    {
    }

    void StWifiStation::disconnect() {}

    void StWifiStation::stop() {}

    void StWifiStation::deinitialize() {}

    bool StWifiStation::isConnected() const
    {
        return true;
    }

    bool StWifiStation::hasIPv4Address() const
    {
        return true;
    }

    void StWifiSoftAp::init() {}

    void StWifiSoftAp::start(const std::string &ssid,
                             const std::string &password)
    {
    }

    void StWifiSoftAp::stop() {}

    void StWifiSoftAp::deinitialize() {}
} // namespace sabre::impl::sabre_test_mocks