#include "sabre_testing/clients/mqtt.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(MQTTTopic, PublishingExplicitValues)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MQTTTopic::SharedPtr topic2 =
        client.get_topic("sabre/testing/topic2");

    topic1->publish("Test message", sabre::net::MQTTQoS::FIRE_AND_FORGET,
                    sabre::net::MQTTRetain::RETAIN);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.topic, "sabre/testing/topic1");
    ASSERT_EQ(last_message_1.message, "Test message");
    ASSERT_EQ(last_message_1.qos, sabre::net::MQTTQoS::FIRE_AND_FORGET);
    ASSERT_EQ(last_message_1.retain, sabre::net::MQTTRetain::RETAIN);
    client._published_messages.pop_back();

    topic2->publish("Second test message", sabre::net::MQTTQoS::EXACTLY_ONCE,
                    sabre::net::MQTTRetain::DONT_RETAIN);
    const auto &last_message_2 = client._published_messages.back();
    ASSERT_EQ(last_message_2.topic, "sabre/testing/topic2");
    ASSERT_EQ(last_message_2.message, "Second test message");
    ASSERT_EQ(last_message_2.qos, sabre::net::MQTTQoS::EXACTLY_ONCE);
    ASSERT_EQ(last_message_2.retain, sabre::net::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultQoS)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefault)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::net::MQTTQoS::EXACTLY_ONCE);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MQTTQoS::EXACTLY_ONCE);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefaultToInvalid)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::net::MQTTQoS::UNDEFINED);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::net::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetain)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message", sabre::net::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefault)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::net::MQTTRetain::RETAIN);

    topic1->publish("Test message", sabre::net::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MQTTRetain::RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefaultInvalid)
{
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::net::MQTTRetain::UNDEFINED);

    topic1->publish("Test message", sabre::net::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::net::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, ReceiveForSubscription)
{
    int callcount = 0;
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MQTTCallback callback =
        [&callcount](const sabre::net::MQTTEvent) { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic1", "test",
                             sabre::net::MQTTQoS::AT_LEAST_ONCE,
                             sabre::net::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, DontReceiveForNoneSubscription)
{
    int callcount = 0;
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTTopic::SharedPtr topic1 =
        client.get_topic("sabre/testing/topic1");
    sabre::net::MQTTCallback callback =
        [&callcount](const sabre::net::MQTTEvent) { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic2", "test",
                             sabre::net::MQTTQoS::AT_LEAST_ONCE,
                             sabre::net::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 0);
}

TEST(MQTTTopic, ReceiveUnsubscribedToDefaultHandler)
{
    int callcount = 0;
    sabre::impl::sabre_testing::MQTTClient client;
    sabre::net::MQTTCallback default_handler =
        [&callcount](const sabre::net::MQTTEvent) { ++callcount; };
    client.set_default_handler(default_handler);

    client.process_received({"unspecified/topic", "test",
                             sabre::net::MQTTQoS::AT_LEAST_ONCE,
                             sabre::net::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, NoDefaultHandlerSet)
{
    sabre::impl::sabre_testing::MQTTClient client;
    ASSERT_NO_THROW(client.process_received({"unspecified/topic", "test",
                                             sabre::net::MQTTQoS::AT_LEAST_ONCE,
                                             sabre::net::MQTTRetain::RETAIN}););
}