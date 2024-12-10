/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** AnimationComponent.hpp
*/

#pragma once
#include <vector>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class AnimationComponent {
                public:
                AnimationComponent() = default;
                ~AnimationComponent() = default;

                private:
                bool loop;
                std::uint32_t current_frame;
                std::uint32_t frame_duration;
                std::vector<sf::Texture> frames;
            };
        }
    }
}
