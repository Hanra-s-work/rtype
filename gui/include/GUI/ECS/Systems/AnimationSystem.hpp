/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** AnimationSystem.hpp
*/

/**
 * @file AnimationSystem.hpp
 * @brief This is the file that contains the Animation class
 */

#pragma once
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            class AnimationSystem : public EntityNode {
                public:
                AnimationSystem() = default;
                ~AnimationSystem() = default;
                void update(float dt);
            };
        }
    }
}

