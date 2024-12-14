/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderSystem.hpp
*/

#pragma once
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class RenderSystem {
                public:
                RenderSystem() = default;
                ~RenderSystem() = default;
                void update();
            };
        }
    }
}


