#pragma once
#include <cstdint>
#include <vector>
#include <optional>

enum class MessageType : uint32_t {
    CONNECT = 1,
    CONNECT_OK,
    // You could add MOVE, SHOOT, DISCONNECT, etc. later
};

struct ParsedMessage {
    MessageType type;
    std::vector<uint8_t> payload; // optional data for each message
};

// Build a packet with an 8-byte header: [type(4 bytes), payloadSize(4 bytes)]
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

// Parse a packet into {type, payload}; returns std::nullopt if data is invalid/incomplete
std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
