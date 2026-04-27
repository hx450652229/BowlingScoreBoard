#include "UdpProtocol.hpp"
#include <gtest/gtest.h>

using namespace Bowling::Network;

TEST(UdpProtocolTest, ParsesNumericPayload)
{
    const auto result = parseUdpMessage("10");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.message->type, UdpMessageType::Roll);
    EXPECT_EQ(result.message->pins, 10);
}

TEST(UdpProtocolTest, ParsesRollCommandPayload)
{
    const auto result = parseUdpMessage("ROLL 7");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.message->pins, 7);
}

TEST(UdpProtocolTest, ParsesRollCommandCaseInsensitive)
{
    const auto result = parseUdpMessage("roll 5");
    ASSERT_TRUE(result.isValid());
    EXPECT_EQ(result.message->pins, 5);
}

TEST(UdpProtocolTest, RejectsMissingRollArgument)
{
    const auto result = parseUdpMessage("ROLL");
    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.error, "Payload is not a valid pin count");
}

TEST(UdpProtocolTest, RejectsTooLargePayload)
{
    const QByteArray oversized(70, '7');
    const auto result = parseUdpMessage(oversized);
    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.error, "Payload too long");
}

TEST(UdpProtocolTest, RejectsNonAsciiPayload)
{
    const QByteArray nonAscii = QByteArray::fromHex("ff");
    const auto result = parseUdpMessage(nonAscii);
    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.error, "Payload contains invalid UTF-8 characters");
}
