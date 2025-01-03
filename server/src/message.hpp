#pragma once

#include <cstdint>
#include <vector>

/**
 * Basic message format:
 *   - 2 bytes: type
 *   - 2 bytes: length
 *   - payload (length bytes)
 */
struct Message {
    uint16_t type = 0;
    std::vector<uint8_t> payload;
};
