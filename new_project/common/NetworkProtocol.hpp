#pragma once
#include <cstdint>
#include <vector>
#include <optional>

enum class MessageType : uint32_t {
    CONNECT = 1,
    CONNECT_OK,
    DISCONNECT,
    HEARTBEAT,
    PLAYER_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    SPAWN_MONSTER,
    PLAYER_FIRE,
    PLAYER_POSITION,

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
