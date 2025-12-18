#include "net.hpp"

namespace sabre::impl::sabre_testing
{
    void StMQTTClient::connect(const std::string &hostname,
                               const std::string &client_id,
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

    bool StMQTTClient::is_connected() const
    {
        return _is_connected;
    }

    void StMQTTClient::publish(const std::string &topic,
                               const std::string &message, MqttQos qos,
                               MqttRetain retain)
    {
        _published_messages.emplace_back(topic, message, qos, retain);
    }
} // namespace sabre::impl::sabre_testing