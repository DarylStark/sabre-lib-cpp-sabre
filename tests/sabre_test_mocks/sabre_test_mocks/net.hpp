#pragma once

#include <sabre/net/mqtt.hpp>
#include <vector>

namespace sabre::impl::sabre_test_mocks
{
    struct MQTTMessage
    {
        std::string topic;
        std::string message;
        sabre::net::MqttQos qos;
        sabre::net::MqttRetain retain;
    };

    class StMQTTClient : public sabre::net::MqttClient
    {
    private:
        bool _is_connected = false;
        bool _is_started = false;

    public:
        void connect(const std::string &hostname, const std::string &clientId,
                     const std::string &username, const std::string &password);
        void disconnect();
        void stop();
        bool isConnected() const;

        void publish(const std::string &topic, const std::string &message,
                     sabre::net::MqttQos qos, sabre::net::MqttRetain retain);

        std::vector<MQTTMessage> _published_messages;
    };
} // namespace sabre::impl::sabre_test_mocks