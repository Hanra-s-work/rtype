/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonSystem.hpp
*/

/**
 * @file ButtonSystem.hpp
 * @brief This is the file that contains the ButtonSystem class
 */

#pragma once
#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class ButtonSystem : public EntityNode {
                public:
                ButtonSystem() = default;
                ~ButtonSystem() = default;
                void update();
            };
        }
    }
}


