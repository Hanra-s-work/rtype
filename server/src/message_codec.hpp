#pragma once
#include "message.hpp"
#include <cstring>
#include <vector>

/**
 * @brief Decodes a raw buffer into a Message (2-byte type, 2-byte length, then payload).
 * @param data Pointer to the incoming data.
 * @param length Total bytes available in `data`.
 * @param out The Message struct to fill.
 * @return true if successful, false if invalid format.
 */
inline bool decodeMessage(const char* data, size_t length, Message& out) {
    uint8_t netType;
    std::memcpy(&netType, data, 1);

    // If needed, do ntohs here:
    // netType = ntohs(netType);
    // netLen  = ntohs(netLen);

    out.type = netType;
    out.payload.resize(length);
    std::memcpy(out.payload.data(), data, length);
    return true;
}

/**
 * @brief Encodes a Message into a raw buffer (2-byte type, 2-byte length, then payload).
 * @param msg The Message to encode.
 * @return A vector of bytes ready to send.
 */
inline std::vector<uint8_t> encodeMessage(const Message& msg) {
    // If needed, do htons
    uint8_t netType = msg.type;

    size_t size = msg.payload.size();
    std::vector<uint8_t> buffer(size + 1);
    std::memcpy(buffer.data(), &netType, 1);
    if (size > 0) {
        std::memcpy(buffer.data() + 1, msg.payload.data(), size);
    }
    return buffer;
}
