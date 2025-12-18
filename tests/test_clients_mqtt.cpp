#include "sabre_testing/net.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(MQTTTopic, PublishingExplicitValues)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MqttTopic::SharedPtr topic2 =
        client.get_topic("sabre/testing/topic2");

    topic1->publish("Test message", sabre::net::MqttQos::FIRE_AND_FORGET,
                    sabre::net::MqttRetain::RETAIN);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.topic, "sabre/testing/topic1");
    ASSERT_EQ(last_message_1.message, "Test message");
    ASSERT_EQ(last_message_1.qos, sabre::net::MqttQos::FIRE_AND_FORGET);
    ASSERT_EQ(last_message_1.retain, sabre::net::MqttRetain::RETAIN);
    client._published_messages.pop_back();

    topic2->publish("Second test message", sabre::net::MqttQos::EXACTLY_ONCE,
                    sabre::net::MqttRetain::DONT_RETAIN);
    const auto &last_message_2 = client._published_messages.back();
    ASSERT_EQ(last_message_2.topic, "sabre/testing/topic2");
    ASSERT_EQ(last_message_2.message, "Second test message");
    ASSERT_EQ(last_message_2.qos, sabre::net::MqttQos::EXACTLY_ONCE);
    ASSERT_EQ(last_message_2.retain, sabre::net::MqttRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultQoS)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MqttQos::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefault)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::net::MqttQos::EXACTLY_ONCE);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MqttQos::EXACTLY_ONCE);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefaultToInvalid)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::net::MqttQos::UNDEFINED);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MqttQos::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetain)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message", sabre::net::MqttQos::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MqttRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefault)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::net::MqttRetain::RETAIN);

    topic1->publish("Test message", sabre::net::MqttQos::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MqttRetain::RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefaultInvalid)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::net::MqttRetain::UNDEFINED);

    topic1->publish("Test message", sabre::net::MqttQos::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MqttRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, ReceiveForSubscription)
{
    int callcount = 0;
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MqttCallback callback =
        [&callcount](const sabre::net::MqttEvent) { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic1", "test",
                             sabre::net::MqttQos::AT_LEAST_ONCE,
                             sabre::net::MqttRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, DontReceiveForNoneSubscription)
{
    int callcount = 0;
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MqttCallback callback =
        [&callcount](const sabre::net::MqttEvent) { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic2", "test",
                             sabre::net::MqttQos::AT_LEAST_ONCE,
                             sabre::net::MqttRetain::RETAIN});

    ASSERT_EQ(callcount, 0);
}

TEST(MQTTTopic, ReceiveUnsubscribedToDefaultHandler)
{
    int callcount = 0;
    sabre::impl::sabre_testing::StMQTTClient client;
    sabre::net::MqttCallback default_handler =
        [&callcount](const sabre::net::MqttEvent) { ++callcount; };
    client.set_default_handler(default_handler);

    client.process_received({"unspecified/topic", "test",
                             sabre::net::MqttQos::AT_LEAST_ONCE,
                             sabre::net::MqttRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, NoDefaultHandlerSet)
{
    sabre::impl::sabre_testing::StMQTTClient client;
    ASSERT_NO_THROW(client.process_received({"unspecified/topic", "test",
                                             sabre::net::MqttQos::AT_LEAST_ONCE,
                                             sabre::net::MqttRetain::RETAIN}););
}