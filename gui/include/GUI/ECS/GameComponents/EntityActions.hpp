/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityActions.hpp
*/

#pragma once
#include "GUI/ECS/GameComponents/EntityActionType.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace GameComponents
        {
            struct EntityActions {
                EntityActionType type;
                int posx;
                int posy;
            };
            typedef struct EntityActions EntityActions_t;
        }
    }
}
