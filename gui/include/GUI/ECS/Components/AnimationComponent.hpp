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
#include <chrono>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class AnimationComponent : public EntityNode {
                public:
                AnimationComponent();
                ~AnimationComponent();
                virtual void setLoop(bool loop);
                virtual void setReadReverse(bool reverse);
                virtual void setDelay(float frameDuration);
                virtual void setInitialFrame(std::uint32_t frameIndex);
                virtual void setAnimation(const std::vector<GUI::ECS::Components::TextureComponent> &textures);

                virtual void checkTick();

                virtual bool hasTicked();

                virtual void update(const GUI::ECS::Components::AnimationComponent &copy);

                virtual bool getLoop() const;
                virtual bool getReadReverse() const;
                virtual float getDelay() const;
                virtual std::uint32_t getFrameCount() const;
                virtual std::uint32_t getInitialFrame() const;
                virtual std::uint32_t getCurrentFrame() const;
                virtual GUI::ECS::Components::TextureComponent getCurrentTexture() const;
                virtual std::vector<GUI::ECS::Components::TextureComponent> getFrames() const;

                AnimationComponent &operator =(const GUI::ECS::Components::AnimationComponent &copy);

                protected:
                void _tick();
                bool _loop;
                bool _hasTicked = false;
                bool _readReverse;
                std::uint32_t _frameDelay;
                std::uint32_t _frameInitial;
                std::uint32_t _currentFrame;
                std::uint32_t _totalFrames;
                std::vector<GUI::ECS::Components::TextureComponent> _frames;
                GUI::ECS::Components::TextureComponent _currentTexture;
                std::chrono::_V2::steady_clock::time_point _lastTick = std::chrono::steady_clock::now();
            };
        }
    }
}
