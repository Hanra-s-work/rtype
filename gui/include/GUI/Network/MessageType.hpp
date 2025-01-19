/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MessageType.hpp
*/

/**
 * @file MessageType.hpp
 *
 * @brief Enum for the different types of messages that can be eschanged with the server.
 */

#pragma once

#include <cstdint>

namespace GUI
{
    namespace Network
    {
        /**
        * @enum MessageType
        * @brief Enum for the different message types in the UDP protocol.
        *
        * Each message type corresponds to a different action or communication between the client and the server.
        * The types include `CONNECT`, `DISCONNECT`, `MOVE`, `SHOOT`, `SPAWN`, `UPDATE`, and a generic `ERROR` type.
        */
        enum class MessageType : uint8_t {
            CONNECT = 1,
            DISCONNECT = 2,
            MOVE = 3,
            SHOOT = 4,
            SPAWN = 5,
            KILL = 6,
            DAMAGE = 7,
            STATUS = 8,
            ERROR = 255
        };
    }
}
