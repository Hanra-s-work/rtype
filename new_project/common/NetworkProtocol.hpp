#pragma once
#include <vector>
#include <cstdint>
#include <optional>

enum class MessageType : uint32_t {
    HELLO = 0,
    JOIN,
    LEAVE,
    MOVE,
    SHOOT,
};

struct ParsedMessage {
    MessageType type;
    std::vector<uint8_t> payload;
};

/**
 * Build a packet with 8-byte header [type + payloadSize], then payload data.
 */
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

/**
 * Parse a packet into {type, payload}.
 * Returns std::nullopt if data is incomplete or invalid.
 */
std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
