/*
** EPITECH PROJECT, 2024
** ProtocolHandler.cpp
** File description:
** Handle message format Sent/received to/from the server
*/

/**
 * @file ProtocolHandler.cpp
 * @brief This is the file in charge of managing the sending and receiving to and from the server.
 */

#include "GUI/Network/ProtocolHandler.hpp"

Packet::Packet(MessageType type, const std::vector<uint8_t> &payload)
    : type(type), size(static_cast<uint16_t>(payload.size())), payload(payload)
{
}

Packet::MessageType Packet::getType() const
{
    return type;
}

uint16_t Packet::getSize() const
{
    return size;
}

const std::vector<uint8_t> &Packet::getPayload() const
{
    return payload;
}

std::vector<uint8_t> Packet::serialize(const Packet &packet)
{
    std::vector<uint8_t> buffer;
    buffer.push_back(static_cast<uint8_t>(packet.type));
    buffer.push_back(static_cast<uint8_t>((packet.size >> 8) & 0xFF));
    buffer.push_back(static_cast<uint8_t>(packet.size & 0xFF));
    buffer.insert(buffer.end(), packet.payload.begin(), packet.payload.end());

    return buffer;
}

Packet Packet::deserialize(const std::vector<uint8_t> &data)
{
    if (data.size() < 3)
        throw std::runtime_error("Invalid packet size");

    MessageType type = static_cast<MessageType>(data[0]);
    uint16_t size = (static_cast<uint16_t>(data[1]) << 8) | static_cast<uint16_t>(data[2]);

    if (data.size() - 3 != size)
        throw std::runtime_error("Payload size mismatch");

    std::vector<uint8_t> payload(data.begin() + 3, data.end());

    return Packet(type, payload);
}

void Packet::print() const
{
    std::cout << "Packet Type: " << static_cast<int>(type) << "\n";
    std::cout << "Packet Size: " << size << "\n";
    std::cout << "Payload: ";
    for (auto byte : payload) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
}
