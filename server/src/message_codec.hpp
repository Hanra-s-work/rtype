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
    if (length < 4) return false;
    uint16_t netType, netLen;
    std::memcpy(&netType, data, 2);
    std::memcpy(&netLen,  data + 2, 2);

    // If needed, do ntohs here:
    // netType = ntohs(netType);
    // netLen  = ntohs(netLen);

    if (length < (4 + netLen)) return false;

    out.type = netType;
    out.payload.resize(netLen);
    std::memcpy(out.payload.data(), data + 4, netLen);
    return true;
}

/**
 * @brief Encodes a Message into a raw buffer (2-byte type, 2-byte length, then payload).
 * @param msg The Message to encode.
 * @return A vector of bytes ready to send.
 */
inline std::vector<uint8_t> encodeMessage(const Message& msg) {
    // If needed, do htons
    uint16_t netType = msg.type;
    uint16_t netLen  = static_cast<uint16_t>(msg.payload.size());

    std::vector<uint8_t> buffer(4 + netLen);
    std::memcpy(buffer.data(), &netType, 2);
    std::memcpy(buffer.data() + 2, &netLen, 2);
    if (netLen > 0) {
        std::memcpy(buffer.data() + 4, msg.payload.data(), netLen);
    }
    return buffer;
}
