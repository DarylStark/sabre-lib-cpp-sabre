#include "sabre_testing/clients/mqtt.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(MQTTTopic, PublishingExplicitValues)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    Sabre::MQTTTopicSharedPtr topic2 = client.get_topic("sabre/testing/topic2");

    topic1->publish("Test message", Sabre::MQTTQoS::FIRE_AND_FORGET,
                    Sabre::MQTTRetain::RETAIN);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.topic, "sabre/testing/topic1");
    ASSERT_EQ(last_message_1.message, "Test message");
    ASSERT_EQ(last_message_1.qos, Sabre::MQTTQoS::FIRE_AND_FORGET);
    ASSERT_EQ(last_message_1.retain, Sabre::MQTTRetain::RETAIN);
    client._published_messages.pop_back();

    topic2->publish("Second test message", Sabre::MQTTQoS::EXACTLY_ONCE,
                    Sabre::MQTTRetain::DONT_RETAIN);
    const auto &last_message_2 = client._published_messages.back();
    ASSERT_EQ(last_message_2.topic, "sabre/testing/topic2");
    ASSERT_EQ(last_message_2.message, "Second test message");
    ASSERT_EQ(last_message_2.qos, Sabre::MQTTQoS::EXACTLY_ONCE);
    ASSERT_EQ(last_message_2.retain, Sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultQoS)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, Sabre::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefault)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(Sabre::MQTTQoS::EXACTLY_ONCE);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, Sabre::MQTTQoS::EXACTLY_ONCE);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultChangedDefaultToInvalid)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_qos(Sabre::MQTTQoS::UNDEFINED);

    topic1->publish("Test message");

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.qos, Sabre::MQTTQoS::FIRE_AND_FORGET);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetain)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");

    topic1->publish("Test message", Sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, Sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefault)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(Sabre::MQTTRetain::RETAIN);

    topic1->publish("Test message", Sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, Sabre::MQTTRetain::RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, PublishingDefaultRetainChangedDefaultInvalid)
{
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    topic1->set_default_retain(Sabre::MQTTRetain::UNDEFINED);

    topic1->publish("Test message", Sabre::MQTTQoS::AT_LEAST_ONCE);

    const auto &last_message_1 = client._published_messages.back();
    ASSERT_EQ(last_message_1.retain, Sabre::MQTTRetain::DONT_RETAIN);
    client._published_messages.pop_back();
}

TEST(MQTTTopic, ReceiveForSubscription)
{
    int callcount = 0;
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    Sabre::MQTTCallback callback = [&callcount](const Sabre::MQTTEvent)
    { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic1", "test",
                             Sabre::MQTTQoS::AT_LEAST_ONCE,
                             Sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, DontReceiveForNoneSubscription)
{
    int callcount = 0;
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTTopicSharedPtr topic1 = client.get_topic("sabre/testing/topic1");
    Sabre::MQTTCallback callback = [&callcount](const Sabre::MQTTEvent)
    { ++callcount; };

    topic1->subscribe(callback);

    client.process_received({"sabre/testing/topic2", "test",
                             Sabre::MQTTQoS::AT_LEAST_ONCE,
                             Sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 0);
}

TEST(MQTTTopic, ReceiveUnsubscribedToDefaultHandler)
{
    int callcount = 0;
    Sabre::Testing::MQTTClient client;
    Sabre::MQTTCallback default_handler = [&callcount](const Sabre::MQTTEvent)
    { ++callcount; };
    client.set_default_handler(default_handler);

    client.process_received({"unspecified/topic", "test",
                             Sabre::MQTTQoS::AT_LEAST_ONCE,
                             Sabre::MQTTRetain::RETAIN});

    ASSERT_EQ(callcount, 1);
}

TEST(MQTTTopic, NoDefaultHandlerSet)
{
    Sabre::Testing::MQTTClient client;
    ASSERT_NO_THROW(client.process_received({"unspecified/topic", "test",
                                             Sabre::MQTTQoS::AT_LEAST_ONCE,
                                             Sabre::MQTTRetain::RETAIN}););
}