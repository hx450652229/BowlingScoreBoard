#pragma once

#include <QByteArray>
#include <QString>
#include <optional>

namespace Bowling::Network
{

/**
 * @brief Supported UDP message types for the bowling protocol.
 * */
enum class UdpMessageType
{
    Roll, /**< A rollover message carrying the number of knocked down pins. */
};

/**
 * @brief A parsed UDP message for the bowling protocol.
 * */
struct UdpMessage
{
    UdpMessageType type;
    int pins;
};

/**
 * @brief Result of parsing a UDP payload.
 * */
struct UdpParseResult
{
    std::optional<UdpMessage> message;
    QString error;

    [[nodiscard]] bool isValid() const noexcept { return message.has_value(); }
};

/**
 * @brief Parse a UDP payload into a bowling protocol message.
 *
 * Supported payloads are either a plain integer string from 0 to 10,
 * or a command of the form "ROLL <n>".
 *
 * @param payload Raw datagram payload.
 * @return A parse result containing either a valid message or an error.
 */
UdpParseResult parseUdpMessage(const QByteArray &payload);

} // namespace Bowling::Network
