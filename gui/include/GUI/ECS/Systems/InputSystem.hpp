/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** InputSystem.hpp
*/

#pragma once
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class InputSystem {
                public:
                InputSystem() = default;
                ~InputSystem() = default;
                void update();
            };
        }
    }
}


