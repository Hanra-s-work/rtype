/*
** EPITECH PROJECT, 2024
** ProtocolHandler.hpp
** File description:
** Serialisation & Deserialisation of binary protocol UDP
*/

#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "Debug.hpp"

class Packet {
    public:
    enum class MessageType : uint8_t {
        CONNECT = 1,
        DISCONNECT = 2,
        MOVE = 3,
        SHOOT = 4,
        SPAWN = 5,
        UPDATE = 6,
        ERROR = 255
    };

    Packet(MessageType type = MessageType::ERROR, const std::vector<uint8_t> &payload = {});
    ~Packet() = default;

    MessageType getType() const;
    uint16_t getSize() const;
    const std::vector<uint8_t> &getPayload() const;

    static std::vector<uint8_t> serialize(const Packet &packet);
    static Packet deserialize(const std::vector<uint8_t> &data);

    /*// Debug part \\*/
    void print() const;
    /*// Debug part \\*/

    private:
    MessageType type;
    uint16_t size;
    std::vector<uint8_t> payload;
};
