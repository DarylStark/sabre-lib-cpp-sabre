#include "mqtt.hpp"

namespace Sabre::Testing
{
    void MQTTClient::connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password)
    {
        _is_connected = true;
        _is_started = true;
    }

    void MQTTClient::disconnect()
    {
        _is_connected = false;
    }

    void MQTTClient::stop()
    {
        _is_started = false;
    }

    bool MQTTClient::is_connected() const
    {
        return _is_connected;
    }

    void MQTTClient::publish(const std::string &topic,
                             const std::string &message, MQTTQoS qos,
                             MQTTRetain retain)
    {
        _published_messages.emplace_back(topic, message, qos, retain);
    }
} // namespace Sabre::Testing