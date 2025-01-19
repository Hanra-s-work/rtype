/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MessageStruct.hpp
*/

#pragma once
#include <cstddef>
#include <utility>


#include "GUI/Network/MessageType.hpp"

namespace GUI
{
    namespace Network
    {
        struct MessageInfo {
            int status;                                                         //!< Status of the event (e.g., success or failure).
            int assetId;                                                       //!< ID representing the game asset related to the event (e.g., entity or object).
            char username[9];                                                   //!< Username of player connecting.
            std::pair<float, float> coords;                                     //!< Coordinates associated with the event, such as the position of an entity.
        };

        struct MessageNode {
            MessageType type;
            std::size_t id;
            MessageInfo info;
        };
    }
}
