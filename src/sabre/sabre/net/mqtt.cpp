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

    void MqttTopic::subscribe(const MqttCallback &fn, MqttQos qos)
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

    void MqttClient::subscribe(const std::string &topic, const MqttCallback &fn,
                               MqttQos qos)
    {
        if (qos == MqttQos::UNDEFINED)
            qos = MqttQos:: // NOLINT(clang-analyzer-deadcode.DeadStores)
                EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }

    MqttTopic::UniquePtr MqttClient::getTopic(const std::string &topicName)
    {
        return std::make_unique<MqttTopic>(*this, topicName);
    }

    void MqttClient::processReceived(const MqttEvent &event)
    {
        if (_subscriptions.find(event.topic) != _subscriptions.end())
            _subscriptions[event.topic](event);
        else if (_defaultHandler != nullptr)
            _defaultHandler(event);
    }

    void MqttClient::setDefaultHandler(const MqttCallback &handler)
    {
        _defaultHandler = handler;
    }

} // namespace sabre::net