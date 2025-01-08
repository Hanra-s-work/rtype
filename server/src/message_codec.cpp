#include "message_codec.hpp"

bool decodeMessage(const char* data, size_t length, Message& out_msg) {
    if (length < 4) {
        return false;
    }
    uint16_t net_type;
    uint16_t net_length;
    std::memcpy(&net_type, data, 2);
    std::memcpy(&net_length, data + 2, 2);

    if (length < (4 + net_length)) {
        return false;
    }

    out_msg.type = net_type;
    out_msg.payload.resize(net_length);
    std::memcpy(out_msg.payload.data(), data + 4, net_length);

    return true;
}

std::vector<uint8_t> encodeMessage(const Message& msg) {
    uint16_t net_type = msg.type;
    uint16_t net_len  = static_cast<uint16_t>(msg.payload.size());

    std::vector<uint8_t> buffer(4 + net_len);
    std::memcpy(buffer.data(), &net_type, 2);
    std::memcpy(buffer.data() + 2, &net_len, 2);
    std::memcpy(buffer.data() + 4, msg.payload.data(), net_len);
    return buffer;
}
