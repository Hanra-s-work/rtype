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

GUI::Network::Packet::Packet(MessageType type, const std::vector<uint8_t> &payload)
    : type(type), size(static_cast<uint16_t>(payload.size())), payload(payload)
{
}

GUI::Network::MessageType GUI::Network::Packet::getType() const
{
    return type;
}

uint16_t GUI::Network::Packet::getSize() const
{
    return size;
}

const std::vector<uint8_t> &GUI::Network::Packet::getPayload() const
{
    return payload;
}

std::vector<uint8_t> GUI::Network::Packet::serialize(const GUI::Network::Packet &packet)
{
    std::vector<uint8_t> buffer;
    buffer.push_back(static_cast<uint8_t>(packet.type));
    buffer.push_back(static_cast<uint8_t>((packet.size >> 8) & 0xFF));
    buffer.push_back(static_cast<uint8_t>(packet.size & 0xFF));
    buffer.insert(buffer.end(), packet.payload.begin(), packet.payload.end());

    return buffer;
}

GUI::Network::Packet GUI::Network::Packet::deserialize(const std::vector<uint8_t> &data)
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

const std::string GUI::Network::Packet::print() const
{
    std::string result = "";
    result += "Packet Type: " + Recoded::myToString(static_cast<int>(type)) + "\n";
    result += "Packet Size: " + Recoded::myToString(size) + "\n";
    result += "Payload: ";
    for (auto byte : payload) {
        result += Recoded::myToString(static_cast<int>(byte)) + " ";
    }
    result += "\n";
    return result;
}
