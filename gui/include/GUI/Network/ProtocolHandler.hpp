/*
** EPITECH PROJECT, 2024
** ProtocolHandler.hpp
** File description:
** Serialisation & Deserialisation of binary protocol UDP
*/


/**
 * @file ProtocolHandler.hpp
 * @brief This file defines the `Packet` class responsible for serializing and deserializing a custom binary UDP protocol.
 *
 * The `Packet` class handles the creation, serialization, and deserialization of UDP protocol packets. It includes functionality
 * for managing various message types such as connection, disconnection, movement, shooting, and spawning of entities.
 * This allows efficient communication between client and server by sending and receiving structured data over UDP.
 */

#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/Network/MessageType.hpp"

namespace GUI
{
    namespace Network
    {
        /**
         * @class Packet
         *
         * @brief Represents a packet for the custom binary UDP protocol.
         *
         * The `Packet` class defines a network packet with a message type, payload, and size. It offers functions to serialize and
         * deserialize packets to and from a byte array for easy transmission over UDP. The supported message types include
         * connection, disconnection, movement, shooting, entity spawning, updates, and error messages.
         */
        class Packet : public GUI::ECS::EntityNode {
            public:
            /**
             * @brief Constructs a `Packet` with a specified message type and payload.
             *
             * @param type The type of message for the packet (default is `ERROR`).
             * @param payload The data to be included in the packet as the payload (optional, defaults to empty).
             */
            Packet(MessageType type = MessageType::ERROR, const std::vector<uint8_t> &payload = {});
            /**
             * @brief Destructor for the `Packet` class.
             *
             * The destructor is defined as default, as there is no dynamic memory allocation needing special cleanup.
             */
            ~Packet() = default;

            /**
             * @brief Gets the message type of the packet.
             *
             * @return The type of message this packet represents (e.g., `CONNECT`, `DISCONNECT`, etc.).
             */
            MessageType getType() const;
            /**
             * @brief Gets the size of the packet's payload.
             *
             * @return The size of the payload in bytes.
             */
            uint16_t getSize() const;
            /**
             * @brief Gets the payload of the packet.
             *
             * @return A reference to the vector of bytes representing the packet's payload.
             */
            const std::vector<uint8_t> &getPayload() const;

            /**
             * @brief Serializes a `Packet` object into a vector of bytes suitable for network transmission.
             *
             * The serialized format includes:
             *  - 1 byte for the message type.
             *  - 2 bytes for the payload size (high byte, low byte).
             *  - The payload itself (a sequence of bytes).
             *
             * @param packet The packet to serialize.
             *
             * @return A vector of bytes representing the serialized packet.
             */
            static std::vector<uint8_t> serialize(const Packet &packet);
            /**
             * @brief Deserializes a packet from a vector of bytes received over the network.
             *
             * This method reconstructs a `Packet` object from its binary representation, extracting the type,
             * size, and payload from the byte array.
             *
             * @param data The vector of bytes representing a serialized packet.
             *
             * @return A `Packet` object constructed from the deserialized data.
             *
             * @throws std::runtime_error If the packet is invalid (e.g., incorrect size).
             */
            static Packet deserialize(const std::vector<uint8_t> &data);

            /*// Debug part \\*/
            /**
             * @brief Prints a string representation of the packet's contents, for debugging purposes.
             *
             * The printed output includes the packet's type, size, and a list of the payload bytes.
             *
             * @return A string containing a human-readable description of the packet.
             */
            const std::string print() const;
            /*// Debug part \\*/

            private:
            MessageType type;                                                   //!< The type of the message in the packet (e.g., `CONNECT`, `MOVE`).
            uint16_t size;                                                      //!< The size of the packet's payload (in bytes).
            std::vector<uint8_t> payload;                                       //!< The actual data being transmitted in the packet.
        };
    }
}
