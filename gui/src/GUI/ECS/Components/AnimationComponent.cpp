/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** AnimationComponent.cpp
*/

/**
 * @file AnimationComponent.cpp
 * @brief This is the file in charge of managing the animation components
 */

#include "GUI/ECS/Components/AnimationComponent.hpp"

void GUI::ECS::Components::AnimationComponent::setLoop(bool loop)
{
    _loop = loop;
}

void GUI::ECS::Components::AnimationComponent::setReadReverse(bool reverse)
{
    _readReverse = reverse;
}

void GUI::ECS::Components::AnimationComponent::setDelay(std::uint32_t frameDuration)
{
    _frameDelay = frameDuration;
}

void GUI::ECS::Components::AnimationComponent::setInitialFrame(std::uint32_t frameIndex)
{
    _frameInitial = frameIndex;
}

const bool GUI::ECS::Components::AnimationComponent::getLoop()
{
    return _loop;
}

const bool GUI::ECS::Components::AnimationComponent::getReadReverse()
{
    return _readReverse;
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getDelay()
{
    return _frameDelay;
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getInitialFrame()
{
    return _frameInitial;
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getCurrentFrame()
{
    return _currentFrame;
}

const std::vector<sf::Texture> GUI::ECS::Components::AnimationComponent::getFrames()
{
    return _frames;
}
