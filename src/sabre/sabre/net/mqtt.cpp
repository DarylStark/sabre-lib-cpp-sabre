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
            qos = _defaultQos;
        if (retain == MqttRetain::UNDEFINED)
            retain = _defaultRetain;

        _client.publish(_topic, message, qos, retain);
    }

    void MqttTopic::subscribe(MqttCallback fn, MqttQos qos)
    {
        _client.subscribe(_topic, fn, qos);
    }

    void MqttTopic::setDefaultQos(MqttQos qos)
    {
        if (qos == MqttQos::UNDEFINED)
            return;
        _defaultQos = qos;
    }

    void MqttTopic::setDefaultRetain(MqttRetain retain)
    {
        if (retain == MqttRetain::UNDEFINED)
            return;
        _defaultRetain = retain;
    }

    void MqttClient::subscribe(const std::string &topic, MqttCallback fn,
                               MqttQos qos)
    {
        if (qos == MqttQos::UNDEFINED)
            qos = MqttQos::EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }

    MqttTopic::UniquePtr MqttClient::getTopic(const std::string &topic_name)
    {
        return std::make_unique<MqttTopic>(*this, topic_name);
    }

    void MqttClient::processReceived(MqttEvent event)
    {
        if (_subscriptions.find(event.topic) != _subscriptions.end())
            _subscriptions[event.topic](event);
        else if (_defaultHandler != nullptr)
            _defaultHandler(event);
    }

    void MqttClient::setDefaultHandler(MqttCallback handler)
    {
        _defaultHandler = handler;
    }

} // namespace sabre::net