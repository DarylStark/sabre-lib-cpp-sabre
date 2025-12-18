#include "mqtt.hpp"

namespace sabre::net
{
    MqttTopic::MqttTopic(MqttClient &client, const std::string &topic)
        : _client(client), _topic(topic)
    {
    }

    void MqttTopic::publish(const std::string &message, MqttQos qos,
                            MqttRetain retain)
    {
        if (qos == MqttQos::UNDEFINED)
            qos = _default_qos;
        if (retain == MqttRetain::UNDEFINED)
            retain = _default_retain;

        _client.publish(_topic, message, qos, retain);
    }

    void MqttTopic::subscribe(MqttCallback fn, MqttQos qos)
    {
        _client.subscribe(_topic, fn, qos);
    }

    void MqttTopic::set_default_qos(MqttQos qos)
    {
        if (qos == MqttQos::UNDEFINED)
            return;
        _default_qos = qos;
    }

    void MqttTopic::set_default_retain(MqttRetain retain)
    {
        if (retain == MqttRetain::UNDEFINED)
            return;
        _default_retain = retain;
    }

    void MqttClient::subscribe(const std::string &topic, MqttCallback fn,
                               MqttQos qos)
    {
        if (qos == MqttQos::UNDEFINED)
            qos = MqttQos::EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }

    MqttTopic::UniquePtr MqttClient::get_topic(const std::string &topic_name)
    {
        return std::make_unique<MqttTopic>(*this, topic_name);
    }

    void MqttClient::process_received(MqttEvent event)
    {
        if (_subscriptions.find(event.topic) != _subscriptions.end())
            _subscriptions[event.topic](event);
        else if (_default_handler != nullptr)
            _default_handler(event);
    }

    void MqttClient::set_default_handler(MqttCallback handler)
    {
        _default_handler = handler;
    }

} // namespace sabre::net