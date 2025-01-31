#include "NetworkProtocol.hpp"
#include <cstring>

std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload)
{
    uint32_t typeInt  = static_cast<uint32_t>(type);
    uint32_t sizeInt  = static_cast<uint32_t>(payload.size());

    std::vector<uint8_t> data;
    data.reserve(8 + payload.size()); // 8 for type+size

    // Copy the 4 bytes of type
    const uint8_t* typePtr = reinterpret_cast<const uint8_t*>(&typeInt);
    data.insert(data.end(), typePtr, typePtr + 4);

    // Copy the 4 bytes of payload size
    const uint8_t* sizePtr = reinterpret_cast<const uint8_t*>(&sizeInt);
    data.insert(data.end(), sizePtr, sizePtr + 4);

    // Copy payload
    data.insert(data.end(), payload.begin(), payload.end());

    return data;
}

std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data)
{
    if (data.size() < 8) {
        return std::nullopt; // not enough for header
    }

    // Read type
    uint32_t typeInt;
    std::memcpy(&typeInt, data.data(), 4);

    // Read payload size
    uint32_t payloadSize;
    std::memcpy(&payloadSize, data.data() + 4, 4);

    if (data.size() < 8 + payloadSize) {
        return std::nullopt; // incomplete payload
    }

    ParsedMessage msg;
    msg.type = static_cast<MessageType>(typeInt);
    msg.payload.assign(
        data.begin() + 8,
        data.begin() + 8 + payloadSize
    );

    return msg;
}
