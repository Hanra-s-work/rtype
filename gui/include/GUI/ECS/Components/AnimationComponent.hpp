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
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Clock.hpp"
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
                AnimationComponent(const std::uint32_t entityId);
                AnimationComponent(const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                AnimationComponent(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                AnimationComponent(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                AnimationComponent(const std::uint32_t entityId, const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                AnimationComponent(const std::uint32_t entityId, const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                AnimationComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                ~AnimationComponent();

                void setLoop(bool loop);
                void setReadReverse(bool reverse);
                void setDelay(float frameDuration);
                void setInitialFrame(std::uint32_t frameIndex);

                void setAnimation(const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                void setAnimation(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                void setAnimation(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);

                void checkTick();

                void start();

                void stop();

                const bool hasTicked();

                void update(const GUI::ECS::Components::AnimationComponent &copy);

                const bool getLoop() const;
                const bool getReadReverse() const;
                const float getDelay() const;
                const std::uint32_t getFrameCount() const;
                const std::uint32_t getInitialFrame() const;
                const std::uint32_t getCurrentFrame() const;
                const GUI::ECS::Components::TextureComponent getCurrentTexture() const;
                const std::vector<GUI::ECS::Components::TextureComponent> getFrames() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                AnimationComponent &operator =(const GUI::ECS::Components::AnimationComponent &copy);

                protected:
                void _tick();
                bool _loop = false;
                bool _hasTicked = false;
                bool _readReverse;
                std::uint32_t _frameDelay;
                std::uint32_t _frameInitial;
                std::uint32_t _currentFrame;
                std::uint32_t _totalFrames;
                GUI::ECS::Components::TextureComponent _baseTexture;
                std::vector<GUI::ECS::Components::TextureComponent> _frames;
                GUI::ECS::Components::TextureComponent _currentTexture;
                GUI::ECS::Utilities::Clock _clock;
            };

            /**
             * @brief Outputs the animation's info to a stream.
             * @param os The output stream.
             * @param item The animation to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const AnimationComponent &item);

        }
    }
}
