#pragma once
#include "message.hpp"
#include <cstring>

/**
 * @brief Decodes a raw buffer into a Message struct using a 4-byte header.
 * 
 * Header:
 *  - 2 bytes: type (uint16_t)
 *  - 2 bytes: length (uint16_t)
 * Then `length` bytes of payload follow.
 *
 * @param data The raw incoming buffer.
 * @param length The total bytes in `data`.
 * @param out A reference to a Message struct to fill.
 * @return true if successful, false if invalid/too short.
 */
inline bool decodeMessage(const char* data, size_t length, Message& out) {
    if (length < 4) return false;

    uint16_t net_type, net_len;
    std::memcpy(&net_type, data, 2);
    std::memcpy(&net_len, data + 2, 2);

    // If needed, do ntohs on net_type, net_len
    // net_type = ntohs(net_type);
    // net_len = ntohs(net_len);

    if (length < (4 + net_len)) return false;

    out.type = net_type;
    out.payload.resize(net_len);
    if (net_len > 0) {
        std::memcpy(out.payload.data(), data + 4, net_len);
    }
    return true;
}

/**
 * @brief Encodes a Message into a raw buffer (4-byte header + payload).
 * @param msg The Message to encode.
 * @return A vector of bytes ready to send over the network.
 */
inline std::vector<uint8_t> encodeMessage(const Message& msg) {
    uint16_t net_type = msg.type;  // or htons(msg.type)
    uint16_t net_len  = static_cast<uint16_t>(msg.payload.size()); // or htons

    std::vector<uint8_t> buffer(4 + net_len);
    std::memcpy(buffer.data(), &net_type, 2);
    std::memcpy(buffer.data() + 2, &net_len, 2);
    if (net_len > 0) {
        std::memcpy(buffer.data() + 4, msg.payload.data(), net_len);
    }
    return buffer;
}
