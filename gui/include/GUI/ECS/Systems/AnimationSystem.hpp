/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** AnimationSystem.hpp
*/

#pragma once
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class AnimationSystem {
                public:
                AnimationSystem() = default;
                ~AnimationSystem() = default;
                void update(float dt);
            };
        }
    }
}

