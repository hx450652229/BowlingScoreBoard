#include "UdpProtocol.hpp"

#include <QChar>
#include <QString>

namespace Bowling::Network
{

namespace
{
constexpr int kMaxDatagramSize = 64;
constexpr int kMinPins = 0;
constexpr int kMaxPins = 10;

std::optional<int> parsePinsFromAscii(const QByteArray &token)
{
    if (token.isEmpty() || token.size() > 2)
    {
        return std::nullopt;
    }

    int value = 0;
    for (char c : token)
    {
        if (c < '0' || c > '9')
        {
            return std::nullopt;
        }
        value = value * 10 + (c - '0');
    }

    if (value < kMinPins || value > kMaxPins)
    {
        return std::nullopt;
    }

    return value;
}

bool containsInvalidUtf8(const QByteArray &payload)
{
    const QString text = QString::fromUtf8(payload);
    return text.contains(QChar::ReplacementCharacter);
}

} // namespace

UdpParseResult parseUdpMessage(const QByteArray &payload)
{
    if (payload.size() > kMaxDatagramSize)
    {
        return { std::nullopt, QStringLiteral("Payload too long") };
    }

    const QByteArray trimmedPayload = payload.trimmed();
    if (trimmedPayload.isEmpty())
    {
        return { std::nullopt, QStringLiteral("Payload is empty") };
    }

    if (containsInvalidUtf8(trimmedPayload))
    {
        return { std::nullopt, QStringLiteral("Payload contains invalid UTF-8 characters") };
    }

    const QByteArray upperPayload = trimmedPayload.toUpper();
    QByteArray payloadArgument;

    if (upperPayload.startsWith("ROLL "))
    {
        payloadArgument = trimmedPayload.mid(5).trimmed();
    }
    else
    {
        payloadArgument = trimmedPayload;
    }

    const auto pins = parsePinsFromAscii(payloadArgument);
    if (!pins)
    {
        const QString error = upperPayload.startsWith("ROLL ") ? QStringLiteral("Invalid ROLL command payload")
                                                               : QStringLiteral("Payload is not a valid pin count");
        return { std::nullopt, error };
    }

    return { UdpMessage{ UdpMessageType::Roll, *pins }, {} };
}

} // namespace Bowling::Network
