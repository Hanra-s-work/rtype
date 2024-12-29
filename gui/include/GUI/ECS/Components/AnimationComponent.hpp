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
                /**
                 *@brief Construct a new Animation Component object
                 *
                 */
                AnimationComponent();
                /**
                 *@brief Construct a new Animation Component object with the entity id
                 *
                 * @param entityId The id of the component
                 */
                AnimationComponent(const std::uint32_t entityId);
                /**
                 *@brief Construct a new Animation Component object with:
                 * @li The loaded textures ready to be played
                 *
                 * @param textures The loaded textures ready to be played
                 */
                AnimationComponent(const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                /**
                 *@brief Construct a new Animation Component object with:
                 * @li The path to the spritesheet
                 * @li The width of the frame
                 * @li The height of the frame
                 * @li Start parsing the animation from the left
                 * @li Start parsing the animation from the right
                 *
                 * @param path
                 * @param frameWidth
                 * @param frameHeight
                 * @param startLeft
                 * @param startTop
                 */
                AnimationComponent(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                /**
                 *@brief Construct a new Animation Component object with:
                 * @li The loaded raw spritesheet
                 * @li The width of the frame
                 * @li The height of the frame
                 * @li Start parsing the animation from the left
                 * @li Start parsing the animation from the right
                 *
                 * @param spritesheet Path to the spritesheet
                 * @param frameWidth Width of the frame for the sprite
                 * @param frameHeight Height of the frame for the sprite
                 * @param startLeft Start parsing the animation from the left
                 * @param startTop Start parsing the animation from the top
                 */
                AnimationComponent(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                /**
                 * @brief Construct a new Animation Component object with:
                 * @li The id of the entity
                 * @li The loaded textures ready to be played
                 *
                 * @param entityId Id of the component
                 * @param textures The textures ready to be played
                 */
                AnimationComponent(const std::uint32_t entityId, const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                /**
                 * @brief Construct a new Animation Component object with:
                 * @li The id of the entity
                 * @li The path to the spritesheet
                 * @li The width of the frame
                 * @li The height of the frame
                 * @li Start parsing the animation from the left
                 * @li Start parsing the animation from the right
                 *
                 * @param entityId Id of the component
                 * @param spritesheet Path to the spritesheet
                 * @param frameWidth Width of the frame for the sprite
                 * @param frameHeight Height of the frame for the sprite
                 * @param startLeft Start parsing the animation from the left
                 * @param startTop Start parsing the animation from the top
                 */
                AnimationComponent(const std::uint32_t entityId, const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                /**
                 * @brief Construct a new Animation Component object with:
                 * @li The id of the entity
                 * @li The loaded raw spritesheet
                 * @li The width of the frame
                 * @li The height of the frame
                 * @li Start parsing the animation from the left
                 * @li Start parsing the animation from the right
                 *
                 * @param entityId Id of the component
                 * @param spritesheet The spritsheet
                 * @param frameWidth Width of the frame for the sprite
                 * @param frameHeight Height of the frame for the sprite
                 * @param startLeft Start parsing the animation from the left
                 * @param startTop Start parsing the animation from the top
                 */
                AnimationComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);

                /**
                 *@brief Destroy the Animation Component object
                 *
                 */
                ~AnimationComponent();

                /**
                 *@brief Set the Loop object
                 *
                 * @param loop
                 */
                void setLoop(bool loop);
                /**
                 *@brief Set the Read Reverse object
                 *
                 * @param reverse
                 */
                void setReadReverse(bool reverse);
                /**
                 *@brief Set the Delay object
                 *
                 * @param frameDuration
                 */
                void setDelay(float frameDuration);
                /**
                 *@brief Set the Initial Frame object
                 *
                 * @param frameIndex
                 */
                void setInitialFrame(std::uint32_t frameIndex);

                /**
                 *@brief Set the Animation object
                 *
                 * @param textures
                 */
                void setAnimation(const std::vector<GUI::ECS::Components::TextureComponent> &textures);
                /**
                 * @brief Set the Animation object
                 *
                 * @param path
                 * @param frameWidth
                 * @param frameHeight
                 * @param startLeft
                 * @param startTop
                 */
                void setAnimation(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);
                /**
                 *@brief Set the Animation object
                 *
                 * @param spritesheet
                 * @param frameWidth
                 * @param frameHeight
                 * @param startLeft
                 * @param startTop
                 */
                void setAnimation(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop);

                /**
                 *@brief Check if it is time to change the frame of the animation.
                 *
                 */
                void checkTick();

                /**
                 *@brief Start the playing of the animation from the current index in memory
                 *
                 */
                void start();

                /**
                 *@brief Pause the playing of the animation but does not reset the index to the default frame
                 *
                 */
                void pause();
                /**
                 *@brief Resume the playing of the animation (has no effect if already playing)
                 *
                 */
                void resume();

                /**
                 *@brief A function to stop the animation, and reset the index to the default frame
                 *
                 */
                void stop();

                /**
                 *@brief A function to check if the frame has changed
                 *
                 * @return true
                 * @return false
                 */
                const bool hasTicked();


                /**
                 *@brief A function to check if the animation has looped around (valid for the 1rst frame of the new loop)
                 *
                 * @return true The animation has looped
                 * @return false The animation has not looped
                 */
                const bool hasLooped() const;

                /**
                 *@brief Get the information about if the component is set to loop the animation
                 *
                 * @return true The component will loop the animation
                 * @return false The component will not loop the animation
                 */
                const bool isLooping() const;

                /**
                 * @brief Get the information about the state of the animation (paused)
                 *
                 * @return true The animation is paused
                 * @return false The animation is not paused
                 */
                const bool isPaused() const;
                /**
                 * @brief Get the information about the state of the animation (playing)
                 *
                 * @return true The animation is playing
                 * @return false The animation is not playing
                 */
                const bool isPlaying() const;
                /**
                 * @brief Get the information about the state of the animation (stopped)
                 *
                 * @return true The animation is stopped
                 * @return false The animation is not stopped
                 */
                const bool isStopped() const;

                /**
                 *@brief Update the current Animation component with another Animation class.
                 *
                 * @param copy
                 */
                void update(const GUI::ECS::Components::AnimationComponent &copy);

                /**
                 *@brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is paused
                 * @return false The animation is playing or stopped
                 */
                const bool getPaused() const;

                /**
                 *@brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is playing
                 * @return false The animation is paused or stopped
                 */
                const bool getPlaying() const;

                /**
                 *@brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is stopped
                 * @return false The animation is playing or paused
                 */
                const bool getStopped() const;

                /**
                 *@brief Get the information about if the animation has completed a loop (valid for the 1rst frame of the new loop)
                 *
                 * @return true The program has looped
                 * @return false The program has not looped
                 */
                const bool getLooped() const;

                /**
                 *@brief Get the info about if the animation is being read in a loop or not (once at the end, go back to the begining and start over)
                 *
                 * @return true The animation is looping
                 * @return false The animation is not looping
                 */
                const bool getLoop() const;
                /**
                 *@brief Get the info about if the order of the frames are being read from right to left instead of left to right.
                 *
                 * @return true reading from right to left
                 * @return false reading from left to right
                 */
                const bool getReadReverse() const;
                /**
                 *@brief Get the Delay object that is used before changing frames.
                 *
                 * @return const float
                 */
                const float getDelay() const;
                /**
                 *@brief Get the total number of frames contained in the animation.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getFrameCount() const;
                /**
                 *@brief Get the index of the frame considered as the first in the series of the animation.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getInitialFrame() const;
                /**
                 *@brief Get the index of the frame that is currently in use.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getCurrentFrame() const;
                /**
                 *@brief Get the dimension of the first frame under an sf::Vector2f instance.
                 *
                 * @return const sf::Vector2f
                 *
                * @throws MyException::NoAnimationFrames if there are no frames to read the content from.
                 */
                const sf::Vector2f getFrameDimensions() const;
                /**
                 *@brief Get the texture that is currently in use.
                 *
                 * @return const GUI::ECS::Components::TextureComponent
                 */
                const GUI::ECS::Components::TextureComponent getCurrentTexture() const;
                /**
                 * @brief Get all the frames loaded in the animation component
                 *
                 * @return const std::vector<GUI::ECS::Components::TextureComponent>
                 */
                const std::vector<GUI::ECS::Components::TextureComponent> getFrames() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                AnimationComponent &operator =(const GUI::ECS::Components::AnimationComponent &copy);

                protected:
                /**
                 *@brief Function in charge of changing the frame when it is time.
                 *
                 */
                void _tick();
                bool _looped = false;                                          //!< A boolean instance in charge of informing the user that the program has looped (valid for the first 2 frames after the loop has occurred)
                bool _loop = false;                                            //!< A boolean instance in charge of informing the program to play the animation as a loop
                bool _paused = false;                                          //!< A boolean instance in charge of informing the program to not play the animation but retain the current position
                bool _playing = false;                                         //!< A boolean instance in charge of informing the program to play or resume the animation
                bool _stopped = false;                                         //!< A boolean instance in charge of informing the program to not play the animation as well as resetting the index to the default one
                bool _hasTicked = false;                                       //!< A boolean instance in charge of informing the user that the frame has been changed
                bool _readReverse;                                             //!< A boolean instance in charge of informing the program to read the animation backwards
                std::uint32_t _frameDelay;                                     //!< An unsigned integer to store the delay to wait between each frame
                std::uint32_t _frameInitial;                                   //!< An unsigned integer to store the index of the initial frame (the default frame)
                std::uint32_t _currentFrame;                                   //!< An unsigned integer to store the index of the frame that is currently active
                std::uint32_t _totalFrames;                                    //!< An unsigned integer to store the total amount of frames in the animation
                GUI::ECS::Components::TextureComponent _baseTexture;           //!< A Texture component to store the base texture that is used to derive all the animations
                std::vector<GUI::ECS::Components::TextureComponent> _frames;   //!< An std::vector of Texture components to store all the derived frames of the animation
                GUI::ECS::Components::TextureComponent _currentTexture;        //!< A Texture component to store the frame that is to be displayed
                GUI::ECS::Utilities::Clock _clock;                             //!< A clock component that allows the Animation component to track time and know when to change frames
            };

            /**
             * @brief Outputs the animation's info to a stream.
             *
             * @param os The output stream.
             * @param item The animation to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const AnimationComponent &item);

        }
    }
}
