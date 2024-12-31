/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** InputSystem.hpp
*/

/**
 * @file InputSystem.hpp
 * @brief This is the file that contains the class in charge of capturing the input class
 */

#pragma once
#include "Log.hpp"
#include "LogMacros.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class InputSystem : public EntityNode {
                public:
                InputSystem() = default;
                ~InputSystem() = default;
                void update();
            };
        }
    }
}


