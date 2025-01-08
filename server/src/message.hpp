#pragma once
#include <cstdint>
#include <vector>

/**
 * @struct Message
 * @brief Represents a decoded message with a 2-byte type, a 2-byte payload length, and a payload vector.
 */
struct Message {
    uint16_t type;               ///< The message type code
    std::vector<uint8_t> payload;///< The message payload bytes
};
