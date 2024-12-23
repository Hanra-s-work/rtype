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

GUI::ECS::Components::AnimationComponent::AnimationComponent() {};

GUI::ECS::Components::AnimationComponent::~AnimationComponent() {};

void GUI::ECS::Components::AnimationComponent::setLoop(bool loop)
{
    _loop = loop;
}

void GUI::ECS::Components::AnimationComponent::setReadReverse(bool reverse)
{
    _readReverse = reverse;
}

void GUI::ECS::Components::AnimationComponent::setDelay(float frameDuration)
{
    if (frameDuration < 0) {
        throw MyException::InvalidDuration(std::to_string(frameDuration), "0", "");
    }
    _frameDelay = frameDuration;
}

void GUI::ECS::Components::AnimationComponent::setInitialFrame(std::uint32_t frameIndex)
{
    if (frameIndex > _totalFrames || frameIndex < 0) {
        throw MyException::InvalidIndex(std::to_string(frameIndex), "0", std::to_string(_totalFrames));
    }
    _frameInitial = frameIndex;
}

void GUI::ECS::Components::AnimationComponent::setAnimation(const std::vector<GUI::ECS::Components::TextureComponent> &textures)
{
    _frames = textures;
    _totalFrames = textures.size();
}

bool GUI::ECS::Components::AnimationComponent::getLoop() const
{
    return _loop;
}

bool GUI::ECS::Components::AnimationComponent::getReadReverse() const
{
    return _readReverse;
}

float GUI::ECS::Components::AnimationComponent::getDelay() const
{
    return _frameDelay;
}

std::uint32_t GUI::ECS::Components::AnimationComponent::getFrameCount() const
{
    return _totalFrames;
}

std::uint32_t GUI::ECS::Components::AnimationComponent::getInitialFrame() const
{
    return _frameInitial;
}

std::uint32_t GUI::ECS::Components::AnimationComponent::getCurrentFrame() const
{
    return _currentFrame;
}

std::vector<GUI::ECS::Components::TextureComponent> GUI::ECS::Components::AnimationComponent::getFrames() const
{
    return _frames;
}

void GUI::ECS::Components::AnimationComponent::update(const GUI::ECS::Components::AnimationComponent &copy)
{
    _loop = copy.getLoop();
    _frames = copy.getFrames();
    _frameDelay = copy.getDelay();
    _totalFrames = copy.getFrameCount();
    _readReverse = copy.getReadReverse();
    _frameInitial = copy.getInitialFrame();
    _currentFrame = copy.getCurrentFrame();
}

void GUI::ECS::Components::AnimationComponent::checkTick()
{
    std::chrono::_V2::steady_clock::time_point  currentTick = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTick - _lastTick;

    if (elapsedTime.count() >= _frameDelay) {
        _tick();
        _lastTick = currentTick;
    }
}

bool GUI::ECS::Components::AnimationComponent::hasTicked()
{
    if (_hasTicked) {
        _hasTicked = false;
        return true;
    }
    return false;
}

GUI::ECS::Components::TextureComponent GUI::ECS::Components::AnimationComponent::getCurrentTexture() const
{
    return _currentTexture;
}

GUI::ECS::Components::AnimationComponent &GUI::ECS::Components::AnimationComponent::operator=(const GUI::ECS::Components::AnimationComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

void GUI::ECS::Components::AnimationComponent::_tick()
{
    std::uint32_t nextFrame = _currentFrame + 1;

    if (_frames.empty()) {
        throw MyException::InvalidIndex("<There are no frames>", "<Have you thought of adding frames to the class?>", "<If not use the setAnimation function>");
    }

    if (nextFrame > _totalFrames && _loop) {
        if (_frameInitial > _totalFrames) {
            throw MyException::InvalidIndex(std::to_string(_frameInitial), "0", std::to_string(_totalFrames));
        }
        _currentFrame = _frameInitial;
    } else if (nextFrame > _totalFrames && !_loop) {
        _currentFrame = 0;
    } else {
        _currentFrame = nextFrame;
    }
    _currentTexture = _frames[_currentFrame];
}
