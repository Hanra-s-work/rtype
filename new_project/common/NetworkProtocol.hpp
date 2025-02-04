//NetworkProtocol.hpp

#pragma once
#include <cstdint>
#include <vector>
#include <optional>

enum class MessageType : uint32_t {
    CONNECT = 1,
    CONNECT_OK = 2,
    DISCONNECT = 3,
    HEARTBEAT = 4,
    PLAYER_LEFT = 5,
    MOVE_UP = 6,
    MOVE_DOWN = 7,
    MOVE_RIGHT = 8,
    MOVE_LEFT = 9,
    SPAWN_MONSTER = 10,
    PLAYER_FIRE = 11,
    PLAYER_POSITION = 12,
    MOVE_UP_STOP = 13,
    MOVE_DOWN_STOP = 14,
    MOVE_LEFT_STOP = 15,
    MOVE_RIGHT_STOP = 16,
    UPDATE_ENTITY = 17,
    SPAWN_ENTITY = 18,
    LIFE = 19,
    DESTROY_ENTITY = 20,

    // You could add MOVE, SHOOT, DISCONNECT, etc. later
};

/// Distinguish teams (players, monsters, etc.)
enum class EntityTeam : uint8_t {
    Players   = 1,
    Monsters  = 2,
};

/// Distinguish specific entity types (player, monster, missile, etc.)
enum class EntityType : uint8_t {
    Player          = 1,
    Monster         = 2,
    PlayerMissile   = 3,
    MonsterMissile  = 4,
    Powerup         = 5,
    Boss            = 6,
};

struct ParsedMessage {
    MessageType type;
    std::vector<uint8_t> payload; // optional data for each message
};

// Build a packet with an 8-byte header: [type(4 bytes), payloadSize(4 bytes)]
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

// Parse a packet into {type, payload}; returns std::nullopt if data is invalid/incomplete
std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
