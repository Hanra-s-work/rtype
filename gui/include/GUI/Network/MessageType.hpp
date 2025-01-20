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
            P_CONNECT = 1,
            P_DISCONNECT = 2,
            P_MOVE = 3,
            P_SHOOT = 4,
            P_SPAWN = 5,
            P_KILL = 6,
            P_DAMAGE = 7,
            P_STATUS = 8,
            P_HANDSHAKE = 254,
            P_ERROR = 255
        };
    }
}
