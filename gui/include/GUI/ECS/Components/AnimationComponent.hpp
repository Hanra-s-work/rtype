/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** AnimationComponent.hpp
*/

/**
 * @file AnimationComponent.hpp
 * @brief This is the file that contains the class in charge of tracking sprite animations.
 */

#pragma once
#include <vector>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include "Debug.hpp"

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
                virtual void setLoop(bool loop) = 0;
                virtual void setReadReverse(bool reverse) = 0;
                virtual void setDelay(std::uint32_t frameDuration) = 0;
                virtual void setInitialFrame(std::uint32_t frameIndex) = 0;

                virtual const bool getLoop() = 0;
                virtual const bool getReadReverse() = 0;
                virtual const std::uint32_t getDelay() = 0;
                virtual const std::uint32_t getInitialFrame() = 0;
                virtual const std::uint32_t getCurrentFrame() = 0;
                virtual const std::vector<sf::Texture> getFrames() = 0;

                protected:
                bool _loop;
                bool _readReverse;
                std::uint32_t _frameInitial;
                std::uint32_t _frameDelay;
                std::uint32_t _currentFrame;
                std::vector<sf::Texture> _frames;
            };
        }
    }
}
