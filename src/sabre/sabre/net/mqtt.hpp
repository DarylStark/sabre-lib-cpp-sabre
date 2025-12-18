#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace sabre::net
{
    /**
     * @brief Enumeration for the QoS levels of a MQTT message.
     *
     * - `UNDEFINED` no QoS set. Normally used for defaults.
     *
     * - `FIRE_AND_FORGET` QoS level
     *
     * - `AT_LEAST_ONCE` QoS level 1
     *
     * - `EXACTLY_ONCE` QoS level 2
     */
    enum class MqttQos
    {
        UNDEFINED = -1,
        FIRE_AND_FORGET = 0,
        AT_LEAST_ONCE = 1,
        EXACTLY_ONCE = 2
    };

    /**
     * @brief Enumeration for the retaining of MQTT message.
     */
    enum class MqttRetain
    {
        UNDEFINED = -1,
        DONT_RETAIN = 0,
        RETAIN = 1
    };

    /**
     * @brief Object for a MQTTEvent
     */
    struct MqttEvent
    {
        using Ptr = MqttEvent *;
        using SharedPtr = std::shared_ptr<MqttEvent>;
        using UniquePtr = std::unique_ptr<MqttEvent>;

        std::string topic;
        std::string data;
        MqttQos qos;
        MqttRetain retain;
    };

    class MqttClient;

    using MqttCallback = std::function<void(const MqttEvent &)>;

    /**
     * @brief Class that represents a MQTT topic.
     *
     * This class can be used to subscribe to a topic or send messages to a
     * topic.
     */
    class MqttTopic
    {
    public:
        using Ptr = MqttTopic *;
        using SharedPtr = std::shared_ptr<MqttTopic>;
        using UniquePtr = std::unique_ptr<MqttTopic>;

    protected:
        MqttClient &_client;
        std::string _topic;
        MqttQos _default_qos = MqttQos::FIRE_AND_FORGET;
        MqttRetain _default_retain = MqttRetain::DONT_RETAIN;

    public:
        /**
         * @brief Constructor; creates the object.
         *
         * @param client the MQTT client to use.
         * @param topic the MQTT topic for this object.
         */
        MqttTopic(MqttClient &client, const std::string &topic);

        /**
         * @brief Publish a message to the topic.
         *
         * @param message the message to publish.
         * @param qos the QoS for the message.
         * @param retain if the broker should retain the message for new
         * subscriptions. If set the `UNDEFINED`, it will be set to
         * `FIRE_AND_FORGET`.
         */
        virtual void publish(const std::string &message,
                             MqttQos qos = MqttQos::UNDEFINED,
                             MqttRetain retain = MqttRetain::UNDEFINED);

        /**
         * @brief Subscribe to the MQTT topic.
         *
         * @param fn the callback for the subscription.
         * @param qos the QoS for the subscription. If set the `UNDEFINED`, it
         * will be set to `FIRE_AND_FORGET`.
         */
        virtual void subscribe(MqttCallback fn,
                               MqttQos qos = MqttQos::UNDEFINED);

        /**
         * @brief Set the default QoS for outgoing messages.
         *
         * @param qos the default QoS for the outgoing messages. If set the
         * `UNDEFINED`, it will be set to `FIRE_AND_FORGET`.
         */
        void set_default_qos(MqttQos qos);

        /**
         * @brief Set the default retain value for outgoing messages.
         *
         * @param retain the default retain value for the outgoing messages. If
         * set the `UNDEFINED`, it will be set to `DONT_RETAIN`.
         */
        void set_default_retain(MqttRetain retain);
    };

    /**
     * @brief Class for a MQTT client
     *
     * This class should be overriden by implementation to implement the correct
     * API functionality to talk to MQTT brokers.
     */
    class MqttClient
    {
    public:
        using Ptr = MqttClient *;
        using SharedPtr = std::shared_ptr<MqttClient>;
        using UniquePtr = std::unique_ptr<MqttClient>;

    private:
        std::unordered_map<std::string, MqttCallback> _subscriptions;
        MqttCallback _default_handler;

    public:
        /**
         * @brief Connect to a specific MQTT broker.
         *
         * @param hostname the hostname for the MQTT broker.
         * @param client_id the client_id for the connection.
         * @param username the username for the connection.
         * @param password the password for the connection.
         */
        virtual void connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password) = 0;

        /**
         * @brief Disconnect the client.
         */
        virtual void disconnect() = 0;

        /**
         * @brief Stop the MQTT client.
         */
        virtual void stop() = 0;

        /**
         * @brief Return if the client is connected.
         *
         * @return `true` if it is connected, otherwise `false`.
         */
        virtual bool is_connected() const = 0;

        /**
         * @brief Publish a message to a topic.
         *
         * @param topic the MQTT topic to publish to.
         * @param message the message to publish.
         * @param qos the QoS for the message.
         * @param retain if the broker should retain the message for new
         * subscriptions. If set the `UNDEFINED`, it will be set to
         * `FIRE_AND_FORGET`.
         */
        virtual void publish(const std::string &topic,
                             const std::string &message, MqttQos qos,
                             MqttRetain retain) = 0;

        /**
         * @brief Subscribe to the MQTT topic.
         *
         * @param topic the MQTT topic to subscribe to.
         * @param fn the callback for the subscription.
         * @param qos the QoS for the subscription. If set the `UNDEFINED`, it
         * will be set to `FIRE_AND_FORGET`.
         */
        virtual void subscribe(const std::string &topic, MqttCallback fn,
                               MqttQos qos = MqttQos::UNDEFINED);

        /**
         * @brief Set a default handler for receiving message.
         *
         * This will be used when the client receives a message that is not
         * explicitly subscribed to. This will also be called when the client
         * subscribes to a wildcard topic (`my_topic/#/etc` for instance.)
         *
         * @param handler the callback for the subscription.
         */
        virtual void set_default_handler(MqttCallback handler);

        /**
         * @brief Method to process a received message.
         *
         * @param event the event that is raised.
         */
        void process_received(MqttEvent event);

        /**
         * @brief Get a Topic object from this client for a MQTT topic.
         *
         * @param topic_name the topic for the MQTTTopic object.
         *
         * @return A `MQTTTopic::UniquePtr` unique pointer to a `MQTTTopic`
         * object.
         */
        MqttTopic::UniquePtr get_topic(const std::string &topic_name);
    };
}; // namespace sabre::net