#pragma once

#include <sabre/net/mqtt.hpp>
#include <vector>

namespace sabre::impl::sabre_testing
{
    using sabre::net::MQTTQoS;
    using sabre::net::MQTTRetain;

    struct MQTTMessage
    {
        std::string topic;
        std::string message;
        MQTTQoS qos;
        MQTTRetain retain;
    };

    class MQTTClient : public sabre::net::MQTTClient
    {
    private:
        bool _is_connected = false;
        bool _is_started = false;

    public:
        void connect(const std::string &hostname, const std::string &client_id,
                     const std::string &username, const std::string &password);
        void disconnect();
        void stop();
        bool is_connected() const;

        void publish(const std::string &topic, const std::string &message,
                     MQTTQoS qos, MQTTRetain retain);

        std::vector<MQTTMessage> _published_messages;
    };
} // namespace sabre::impl::sabre_testing