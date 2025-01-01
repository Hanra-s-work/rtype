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
#include <utility>
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/Clock.hpp"
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
                 * @brief Construct a new Animation Component object
                 *
                 */
                AnimationComponent();
                /**
                 * @brief Construct a new Animation Component object with the entity id
                 *
                 * @param entityId The id of the component
                 */
                AnimationComponent(const std::uint32_t entityId);
                /**
                 * @brief Construct a new Animation Component object with:
                 * @li The loaded IntRect's ready to be played
                 *
                 * @param rects The loaded IntRects ready to be played
                 */
                AnimationComponent(const std::vector<Recoded::IntRect> &rects);
                /**
                 * @brief Construct a new Animation Component object with:
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
                AnimationComponent(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));
                /**
                 * @brief Construct a new Animation Component object with:
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
                AnimationComponent(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));
                /**
                 * @brief Construct a new Animation Component object with:
                 * @li The id of the entity
                 * @li The loaded IntRects ready to be played
                 *
                 * @param entityId Id of the component
                 * @param rects The IntRects ready to be played
                 */
                AnimationComponent(const std::uint32_t entityId, const std::vector<Recoded::IntRect> &rects);
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
                AnimationComponent(const std::uint32_t entityId, const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));
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
                AnimationComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));

                /**
                 * @brief Destroy the Animation Component object
                 *
                 */
                ~AnimationComponent();

                /**
                 * @brief Set the Loop object
                 *
                 * @param loop
                 */
                void setLoop(bool loop);
                /**
                 * @brief Set the Read Reverse object
                 *
                 * @param reverse
                 */
                void setReadReverse(bool reverse);
                /**
                 * @brief Set the Delay object
                 *
                 * @param frameDuration
                 */
                void setDelay(float frameDuration);
                /**
                 * @brief Set the Initial Frame object
                 *
                 * @param frameIndex
                 */
                void setInitialFrame(std::uint32_t frameIndex);

                /**
                 * @brief Set the Animation object
                 *
                 * @param rects
                 */
                void setAnimation(const std::vector<Recoded::IntRect> &rects);
                /**
                 * @brief Set the Animation object
                 *
                 * @param path
                 * @param frameWidth
                 * @param frameHeight
                 * @param startLeft
                 * @param startTop
                 */
                void setAnimation(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));
                /**
                 * @brief Set the Animation object
                 *
                 * @param spritesheet
                 * @param frameWidth
                 * @param frameHeight
                 * @param startLeft
                 * @param startTop
                 */
                void setAnimation(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));

                /**
                 * @brief Check if it is time to change the frame of the animation.
                 *
                 */
                void checkTick();

                /**
                 * @brief Start the playing of the animation from the current index in memory
                 *
                 */
                void start();

                /**
                 * @brief Pause the playing of the animation but does not reset the index to the default frame
                 *
                 */
                void pause();
                /**
                 * @brief Resume the playing of the animation (has no effect if already playing)
                 *
                 */
                void resume();

                /**
                 * @brief A function to stop the animation, and reset the index to the default frame
                 *
                 */
                void stop();

                /**
                 * @brief A function to check if the frame has changed
                 *
                 * @return true
                 * @return false
                 */
                const bool hasTicked();

                /**
                 * @brief A function to check if the animation has looped around (valid for the 1rst frame of the new loop)
                 *
                 * @return true The animation has looped
                 * @return false The animation has not looped
                 */
                const bool hasLooped() const;

                /**
                 * @brief Get the information about if the component is set to loop the animation
                 *
                 * @return true The component will loop the animation
                 * @return false The component will not loop the animation
                 */
                const bool isLooping() const;

                /**
                 * @brief Get the information about the state of the animation (paused)
                 *
                 * @return true The animation is paused
                 * @return false The animation is playing or stopped
                 */
                const bool isPaused() const;
                /**
                 * @brief Get the information about the state of the animation (playing)
                 *
                 * @return true The animation is playing
                 * @return false The animation is paused or stopped
                 */
                const bool isPlaying() const;
                /**
                 * @brief Get the information about the state of the animation (stopped)
                 *
                 * @return true The animation is stopped
                 * @return false The animation is playing or paused
                 */
                const bool isStopped() const;

                /**
                 * @brief Update the current Animation component with another Animation class.
                 *
                 * @param copy
                 */
                void update(const GUI::ECS::Components::AnimationComponent &copy);

                /**
                * @brief A function to check if the frame has changed
                *
                * @return true
                * @return false
                *
                * @note This is a function intended for the update function,
                * if you wish to check if the clock has ticked, please use
                * it's sister function `hasTicked`
                */
                const bool getTicked() const;

                /**
                 * @brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is paused
                 * @return false The animation is playing or stopped
                 *
                 * @note This function is there for cpp convention logics
                 * as well as the update function, please use it's sister
                 * function `isPaused`
                 */
                const bool getPaused() const;

                /**
                 * @brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is playing
                 * @return false The animation is paused or stopped
                 *
                 * @note This function is there for cpp convention logics
                 * as well as the update function, please use it's sister
                 * function `isPlaying`
                 */
                const bool getPlaying() const;

                /**
                 * @brief Get the information about the state of the animation (paused/playing)
                 *
                 * @return true The animation is stopped
                 * @return false The animation is playing or paused
                 *
                 * @note This function is there for cpp convention logics
                 * as well as the update function, please use it's sister
                 * function `isStopped`
                 */
                const bool getStopped() const;

                /**
                 * @brief Get the information about if the animation has completed a loop (valid for the 1rst frame of the new loop)
                 *
                 * @return true The program has looped
                 * @return false The program has not looped
                 *
                 * @note This function is there for cpp convention logics
                 * as well as the update function, please use it's sister
                 * function `hasLooped`
                 */
                const bool getLooped() const;

                /**
                 * @brief Get the info about if the animation is being read in a loop or not (once at the end, go back to the begining and start over)
                 *
                 * @return true The animation is looping
                 * @return false The animation is not looping
                 */
                const bool getLoop() const;
                /**
                 * @brief Get the info about if the order of the frames are being read from right to left instead of left to right.
                 *
                 * @return true reading from right to left
                 * @return false reading from left to right
                 */
                const bool getReadReverse() const;
                /**
                 * @brief Get the Delay object that is used before changing frames.
                 *
                 * @return const float
                 */
                const float getDelay() const;
                /**
                 * @brief Get the total number of frames contained in the animation.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getFrameCount() const;
                /**
                 * @brief Get the index of the frame considered as the first in the series of the animation.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getInitialFrame() const;
                /**
                 * @brief Get the index of the frame that is currently in use.
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getCurrentFrameIndex() const;
                /**
                 * @brief Get the index of the frame that is currently in use.
                 *
                 * @return const Recoded::IntRect
                 */
                const Recoded::IntRect getCurrentFrame() const;
                /**
                 * @brief Get the Base Texture object
                 *
                 * @return const GUI::ECS::Components::TextureComponent
                 */
                const GUI::ECS::Components::TextureComponent getBaseTexture() const;
                /**
                 * @brief Get the dimension of the first frame under an std::pair<int, int> instance.
                 *
                 * @return const std::pair<int, int>
                 *
                * @throws CustomExceptions::NoAnimationFrames if there are no frames to read the content from.
                 */
                const std::pair<int, int> getFrameDimensions() const;
                /**
                 * @brief Get the Rectangle that is currently in use.
                 *
                 * @return const Recoded::IntRect
                 */
                const Recoded::IntRect getCurrentRectangle() const;
                /**
                 * @brief Get all the frames loaded in the animation component
                 *
                 * @return const std::vector<Recoded::IntRect>
                 */
                const std::vector<Recoded::IntRect> getFrames() const;
                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                /**
                 * @brief Get the Clock object
                 *
                 * @return const GUI::ECS::Systems::Clock
                 *
                 * @note This function is intended for the update function,
                 * you can call it but I'm not sure the clock instance will be
                 * of any use without the animation component class to go with it
                 */
                const GUI::ECS::Systems::Clock getClock() const;

                AnimationComponent &operator =(const GUI::ECS::Components::AnimationComponent &copy);

                protected:
                /**
                 * @brief Main function to process the ticking of the animation.
                 *
                 * This function is responsible for advancing the current frame of the animation. It first checks if the animation is paused,
                 * if there are frames to render, and if the initial frame is valid. It then calls either `_tickRegular()` or `_tickReverse()`
                 * based on the direction of the animation (forward or reverse).
                 *
                 * If the animation is paused, no frame is updated. If there are no frames or if the initial frame is invalid, appropriate
                 * exceptions are thrown. This function decides whether to proceed with regular or reverse ticking of the frames.
                 *
                 * @throws CustomExceptions::InvalidIndex If there are no frames, or if the frame index exceeds the valid range.
                 */
                void _tick();
                /**
                 * @brief Advances the animation by one frame in reverse.
                 *
                 * This function is responsible for decrementing the current frame index in reverse order. If the next frame is out of bounds
                 * (i.e., the index becomes negative), the frame index is reset either to the last frame or the initial frame depending on
                 * whether looping is enabled. The current frame is then updated.
                 *
                 * @throws CustomExceptions::InvalidIndex If the initial frame is invalid or greater than the total number of frames.
                 */
                void _tickReverse();
                /**
                 * @brief Advances the animation by one frame in regular (forward) order.
                 *
                 * This function is responsible for incrementing the current frame index in forward order. If the next frame exceeds the total
                 * number of frames, the index is reset either to the first frame or the initial frame, depending on whether looping is enabled.
                 * The current frame is then updated.
                 *
                 * @throws CustomExceptions::InvalidIndex If the initial frame is invalid or greater than the total number of frames.
                 */
                void _tickRegular();
                /**
                 * @brief Function in charge of generating the animation frames based on the provided information.
                 *
                 * @param frameWidth The width of the resulting sprite
                 * @param frameHeight The height of the resulting sprite
                 * @param startLeft Start from the left
                 * @param startTop Start from the top
                 */
                void _processAnimation(const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop, const unsigned int initialFrame = 0, const int endFrame = (-1));
                const short int _getIndexUpdater(const bool startBegining = true) const;
                const bool _continueLoop(const bool startBegining, const unsigned int position, const unsigned int maxValue) const;
                bool _looped = false;                                          //!< A boolean instance in charge of informing the user that the program has looped (valid for the first 2 frames after the loop has occurred)
                bool _loop = false;                                            //!< A boolean instance in charge of informing the program to play the animation as a loop
                bool _paused = false;                                          //!< A boolean instance in charge of informing the program to not play the animation but retain the current position
                bool _playing = false;                                         //!< A boolean instance in charge of informing the program to play or resume the animation
                bool _stopped = false;                                         //!< A boolean instance in charge of informing the program to not play the animation as well as resetting the index to the default one
                bool _hasTicked = false;                                       //!< A boolean instance in charge of informing the user that the frame has been changed
                bool _readReverse = false;                                     //!< A boolean instance in charge of informing the program to read the animation backwards
                std::uint32_t _frameDelay;                                     //!< An unsigned integer to store the delay to wait between each frame
                std::uint32_t _frameInitial;                                   //!< An unsigned integer to store the index of the initial frame (the default frame)
                std::uint32_t _currentFrameIndex;                              //!< An unsigned integer to store the index of the frame that is currently active
                std::uint32_t _totalFrames;                                    //!< An unsigned integer to store the total amount of frames in the animation
                GUI::ECS::Components::TextureComponent _baseTexture;           //!< A Texture component to store the base texture that is used to derive all the animations rectangles
                std::vector<Recoded::IntRect> _frames;                         //!< An std::vector of Rectangle components to store all the derived frames of the animation
                Recoded::IntRect _currentRectangle;                            //!< A Rectangle component to store the frame that is to be displayed
                GUI::ECS::Systems::Clock _clock;                               //!< A clock component that allows the Animation component to track time and know when to change frames
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
