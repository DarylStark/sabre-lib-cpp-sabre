#include "sabre_testing/clients/mqtt.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(MQTTTopic, PublishingExplicitValues)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    sabre::MQTTTopicSharedPtr topic2 = client.get_topic("sabre/testing/topic2");

    topic1->publish("Test message", sabre::MQTTQoS::FIRE_AND_FORGET,
                    sabre::MQTTRetain::RETAIN);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.topic, "sabre/testing/topic1");
    ASSERT_EQ(last_message_1.message, "Test message");
    ASSERT_EQ(last_message_1.qos, sabre::MQTTQoS::FIRE_AND_FORGET);
    ASSERT_EQ(last_message_1.retain, sabre::MQTTRetain::RETAIN);
    client._published_messages.pop_back();

    topic2->publish("Second test message", sabre::MQTTQoS::EXACTLY_ONCE,
                    sabre::MQTTRetain::DONT_RETAIN);
    const auto &last_message_2 = client._published_messages.back();
    ASSERT_EQ(last_message_2.topic, "sabre/testing/topic2");
    ASSERT_EQ(last_message_2.message, "Second test message");
    ASSERT_EQ(last_message_2.qos, sabre::MQTTQoS::EXACTLY_ONCE);
    ASSERT_EQ(last_message_2.retain, sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultQoS)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefault)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::MQTTQoS::EXACTLY_ONCE);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::MQTTQoS::EXACTLY_ONCE);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefaultToInvalid)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(sabre::MQTTQoS::UNDEFINED);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, sabre::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetain)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message", sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefault)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::MQTTRetain::RETAIN);

    topic1->publish("Test message", sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::MQTTRetain::RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefaultInvalid)
{
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(sabre::MQTTRetain::UNDEFINED);

    topic1->publish("Test message", sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, ReceiveForSubscription)
{
    int callcount = 0;
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    sabre::MQTTCallback callback = [&callcount](const sabre::MQTTEvent)
    { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic1", "test",
                             sabre::MQTTQoS::AT_LEAST_ONCE,
                             sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, DontReceiveForNoneSubscription)
{
    int callcount = 0;
    sabre::Testing::MQTTClient client;
    sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    sabre::MQTTCallback callback = [&callcount](const sabre::MQTTEvent)
    { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic2", "test",
                             sabre::MQTTQoS::AT_LEAST_ONCE,
                             sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 0);
}

TEST(MQTTTopic, ReceiveUnsubscribedToDefaultHandler)
{
    int callcount = 0;
    sabre::Testing::MQTTClient client;
    sabre::MQTTCallback default_handler = [&callcount](const sabre::MQTTEvent)
    { ++callcount; };
    client.set_default_handler(default_handler);

    client.process_received({"unspecified/topic", "test",
                             sabre::MQTTQoS::AT_LEAST_ONCE,
                             sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, NoDefaultHandlerSet)
{
    sabre::Testing::MQTTClient client;
    ASSERT_NO_THROW(client.process_received({"unspecified/topic", "test",
                                             sabre::MQTTQoS::AT_LEAST_ONCE,
                                             sabre::MQTTRetain::RETAIN}););
}