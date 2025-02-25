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
    SCORE = 21,
    DEFEAT = 22,
    WIN = 23,
    HUB = 24, // Implementation in progress in gui side && To implement server side
    COLLIDE = 25 // Implementation in progress in gui side && To implement server side
};

enum class EntityType : uint8_t {
    Player          = 1,
    Monster         = 2,
    PlayerMissile   = 3,
    MonsterMissile  = 4,
    Powerup         = 5,
    Boss            = 6,
    Monster2        = 7,
    Monster3        = 8,
    Collision       = 9
};

struct ParsedMessage {
    MessageType type;
    std::vector<uint8_t> payload;
};

std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);