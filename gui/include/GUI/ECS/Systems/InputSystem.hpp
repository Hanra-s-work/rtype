/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** InputSystem.hpp
*/

#pragma once
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


