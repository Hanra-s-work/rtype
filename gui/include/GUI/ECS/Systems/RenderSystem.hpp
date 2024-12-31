/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderSystem.hpp
*/

/**
 * @file RenderSystem.hpp
 * @brief This is the file that contains the Rendering class
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
            class RenderSystem : public EntityNode {
                public:
                RenderSystem() = default;
                ~RenderSystem() = default;
                void update();
            };
        }
    }
}


