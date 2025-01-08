#pragma once
#include <cstdint>
#include <vector>

/**
 * @struct Message
 * @brief Minimal network message with a 4-byte header (type + length) and a payload.
 */
struct Message {
    uint16_t type; ///< Could map to messageType in GameMessage.hpp (CONNECT, DISCONNECT, etc.)
    std::vector<uint8_t> payload; ///< Arbitrary payload bytes
};

// In your case, 'type' might match the 'messageType' enum from GameMessage.hpp.
// You can define: CONNECT=1, DISCONNECT=2, MOVE=3, etc. or directly use the enum's values.
