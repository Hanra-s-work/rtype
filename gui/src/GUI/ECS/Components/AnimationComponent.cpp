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

GUI::ECS::Components::AnimationComponent::AnimationComponent() : EntityNode(0) {};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::uint32_t entityId) : EntityNode(entityId) {};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::vector<GUI::ECS::Components::TextureComponent> &textures)
    : EntityNode(0)
{
    setAnimation(textures);
};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
    : EntityNode(0)
{
    setAnimation(path, frameWidth, frameHeight, startLeft, startTop);
};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
    : EntityNode(0)
{
    setAnimation(spritesheet, frameWidth, frameHeight, startLeft, startTop);
};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::uint32_t entityId, const std::vector<GUI::ECS::Components::TextureComponent> &textures)
    : EntityNode(entityId)
{
    setAnimation(textures);
};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::uint32_t entityId, const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
    : EntityNode(entityId)
{
    setAnimation(path, frameWidth, frameHeight, startLeft, startTop);
};

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
    : EntityNode(entityId)
{
    setAnimation(spritesheet, frameWidth, frameHeight, startLeft, startTop);
};



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

void GUI::ECS::Components::AnimationComponent::setAnimation(const std::string &path, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
{
    _baseTexture.setFilePath(path);
    Debug::getInstance() << "Implement spritesheet animation cutting." << std::endl;
}

void GUI::ECS::Components::AnimationComponent::setAnimation(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
{
    _baseTexture.update(spritesheet);
    Debug::getInstance() << "Implement spritesheet animation cutting." << std::endl;
}

void GUI::ECS::Components::AnimationComponent::checkTick()
{
    if (_clock.getElapsedTime() >= _frameDelay) {
        _tick();
        _hasTicked = true;
    }
}

void GUI::ECS::Components::AnimationComponent::start()
{
    _clock.start();
}

void GUI::ECS::Components::AnimationComponent::stop()
{
    _clock.stop();
}

const bool GUI::ECS::Components::AnimationComponent::hasTicked()
{
    if (_hasTicked) {
        _hasTicked = false;
        return true;
    }
    return false;
}

const bool GUI::ECS::Components::AnimationComponent::hasLooped() const
{
    return _looped;
}

const bool GUI::ECS::Components::AnimationComponent::isLooping() const
{
    return _loop;
}

const bool GUI::ECS::Components::AnimationComponent::isPaused() const
{
    return _paused;
}

const bool GUI::ECS::Components::AnimationComponent::isPlaying() const
{
    return _playing;
}

const bool GUI::ECS::Components::AnimationComponent::isStopped() const
{
    return _stopped;
}

void GUI::ECS::Components::AnimationComponent::update(const GUI::ECS::Components::AnimationComponent &copy)
{
    _loop = copy.getLoop();
    _clock = copy.getClock();
    _frames = copy.getFrames();
    _looped = copy.getLooped();
    _paused = copy.getPaused();
    _frames = copy.getFrames();
    _playing = copy.getPlaying();
    _stopped = copy.getStopped();
    _hasTicked = copy.getTicked();
    _frameDelay = copy.getDelay();
    _totalFrames = copy.getFrameCount();
    _baseTexture = copy.getBaseTexture();
    _readReverse = copy.getReadReverse();
    _frameInitial = copy.getInitialFrame();
    _currentFrame = copy.getCurrentFrame();
    _currentTexture = copy.getCurrentTexture();
}

const bool GUI::ECS::Components::AnimationComponent::getTicked() const
{
    return _hasTicked;
}

const bool GUI::ECS::Components::AnimationComponent::getPaused() const
{
    return isPaused();
}

const bool GUI::ECS::Components::AnimationComponent::getPlaying() const
{
    return isPlaying();
}

const bool GUI::ECS::Components::AnimationComponent::getStopped() const
{
    return isStopped();
}

const bool GUI::ECS::Components::AnimationComponent::getLooped() const
{
    return _looped;
}

const bool GUI::ECS::Components::AnimationComponent::getLoop() const
{
    return _loop;
}

const bool GUI::ECS::Components::AnimationComponent::getReadReverse() const
{
    return _readReverse;
}

const float GUI::ECS::Components::AnimationComponent::getDelay() const
{
    return _frameDelay;
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getFrameCount() const
{
    return _totalFrames;
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getInitialFrame() const
{
    return _frameInitial;
}

const sf::Vector2f GUI::ECS::Components::AnimationComponent::getFrameDimensions() const
{
    if (_frames.size() <= 0) {
        throw MyException::NoAnimationFrames();
    }
    return _frames[0].getCollisionInfo().getDimension();
}

const std::uint32_t GUI::ECS::Components::AnimationComponent::getCurrentFrame() const
{
    return _currentFrame;
}

const GUI::ECS::Components::TextureComponent GUI::ECS::Components::AnimationComponent::getBaseTexture() const
{
    return _baseTexture;
}

const GUI::ECS::Components::TextureComponent GUI::ECS::Components::AnimationComponent::getCurrentTexture() const
{
    return _currentTexture;
}

const std::vector<GUI::ECS::Components::TextureComponent> GUI::ECS::Components::AnimationComponent::getFrames() const
{
    return _frames;
}

const std::string GUI::ECS::Components::AnimationComponent::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "AnimationComponent:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Looped: " + MyRecodes::myToString(_looped) + "\n";
    result += indentation + "- Loop: " + MyRecodes::myToString(_loop) + "\n";
    result += indentation + "- Paused: " + MyRecodes::myToString(_paused) + "\n";
    result += indentation + "- Playing: " + MyRecodes::myToString(_playing) + "\n";
    result += indentation + "- Stopped: " + MyRecodes::myToString(_stopped) + "\n";
    result += indentation + "- Has Ticked: " + MyRecodes::myToString(_hasTicked) + "\n";
    result += indentation + "- Read Reverse: " + MyRecodes::myToString(_readReverse) + "\n";
    result += indentation + "- Frame Delay: " + MyRecodes::myToString(_frameDelay) + "\n";
    result += indentation + "- Frame Initial: " + MyRecodes::myToString(_frameInitial) + "\n";
    result += indentation + "- Current Frame: " + MyRecodes::myToString(_currentFrame) + "\n";
    result += indentation + "- Total Frames: " + MyRecodes::myToString(_totalFrames) + "\n";
    result += indentation + "- Base texture: {\n" + _baseTexture.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Frames: {\n";
    for (unsigned int i = 0; i < _frames.size(); i++) {
        result += indentation + "\t" + MyRecodes::myToString(i) + ": {\n";
        result += _frames[i].getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "Current Texture: {\n" + _currentTexture.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "Clock: {\n" + _clock.getInfo(indent + 1) + "}\n";
    return result;
}

const GUI::ECS::Utilities::Clock GUI::ECS::Components::AnimationComponent::getClock() const
{
    return _clock;
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


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::AnimationComponent &item)
{
    os << item.getInfo();
    return os;
}
