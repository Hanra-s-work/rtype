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
        throw CustomExceptions::InvalidDuration(std::to_string(frameDuration), "0", "");
    }
    _frameDelay = frameDuration;
}

void GUI::ECS::Components::AnimationComponent::setInitialFrame(std::uint32_t frameIndex)
{
    if (frameIndex > _totalFrames || frameIndex < 0) {
        throw CustomExceptions::InvalidIndex(std::to_string(frameIndex), "0", std::to_string(_totalFrames));
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
    _processAnimation(frameWidth, frameHeight, startLeft, startTop);
}

void GUI::ECS::Components::AnimationComponent::setAnimation(const GUI::ECS::Components::TextureComponent &spritesheet, const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
{
    _baseTexture.update(spritesheet);
    _processAnimation(frameWidth, frameHeight, startLeft, startTop);
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
    _hasTicked = false;
    _playing = true;
    _paused = false;
    _stopped = false;
}

void GUI::ECS::Components::AnimationComponent::pause()
{
    _clock.stop();
    _hasTicked = false;
    _playing = false;
    _paused = true;
    _stopped = false;
}

void GUI::ECS::Components::AnimationComponent::resume()
{
    _clock.start();
    _hasTicked = false;
    _playing = true;
    _paused = false;
    _stopped = false;
}

void GUI::ECS::Components::AnimationComponent::stop()
{
    _clock.reset();
    _hasTicked = false;
    _playing = false;
    _paused = false;
    _stopped = true;
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
    PRECISE_INFO << "Processing getLoop" << std::endl;
    _loop = copy.getLoop();
    PRECISE_SUCCESS << "Processed getLoop" << std::endl;
    PRECISE_INFO << "Processing getCLock" << std::endl;
    _clock = copy.getClock();
    PRECISE_SUCCESS << "Processed getCLock" << std::endl;
    PRECISE_INFO << "Processing getFrames" << std::endl;
    _frames = copy.getFrames();
    PRECISE_SUCCESS << "Processed getFrames" << std::endl;
    PRECISE_INFO << "Processing getLooped" << std::endl;
    _looped = copy.getLooped();
    PRECISE_SUCCESS << "Processed getLooped" << std::endl;
    PRECISE_INFO << "Processing getPaused" << std::endl;
    _paused = copy.getPaused();
    PRECISE_SUCCESS << "Processed getPaused" << std::endl;
    PRECISE_INFO << "Processing getFrames" << std::endl;
    _frames = copy.getFrames();
    PRECISE_SUCCESS << "Processed getFrames" << std::endl;
    PRECISE_INFO << "Processing getPlaying" << std::endl;
    _playing = copy.getPlaying();
    PRECISE_SUCCESS << "Processed getPlaying" << std::endl;
    PRECISE_INFO << "Processing getStopped" << std::endl;
    _stopped = copy.getStopped();
    PRECISE_SUCCESS << "Processed getStopped" << std::endl;
    PRECISE_INFO << "Processing getTicked" << std::endl;
    _hasTicked = copy.getTicked();
    PRECISE_SUCCESS << "Processed getTicked" << std::endl;
    PRECISE_INFO << "Processing getDelay" << std::endl;
    _frameDelay = copy.getDelay();
    PRECISE_SUCCESS << "Processed getDelay" << std::endl;
    PRECISE_INFO << "Processing getFramesCount" << std::endl;
    _totalFrames = copy.getFrameCount();
    PRECISE_SUCCESS << "Processed getFramesCount" << std::endl;
    PRECISE_INFO << "Processing getBaseTexture" << std::endl;
    _baseTexture = copy.getBaseTexture();
    PRECISE_SUCCESS << "Processed getBaseTexture" << std::endl;
    PRECISE_INFO << "Processing getReadReverse" << std::endl;
    _readReverse = copy.getReadReverse();
    PRECISE_SUCCESS << "Processed getReadReverse" << std::endl;
    PRECISE_INFO << "Processing getInitialFrame" << std::endl;
    _frameInitial = copy.getInitialFrame();
    PRECISE_SUCCESS << "Processed getInitialFrame" << std::endl;
    PRECISE_INFO << "Processing getCurrentFrame" << std::endl;
    _currentFrame = copy.getCurrentFrame();
    PRECISE_SUCCESS << "Processed getCurrentFrame" << std::endl;
    PRECISE_INFO << "Processing getCurrentTexture" << std::endl;
    _currentTexture = copy.getCurrentTexture();
    PRECISE_SUCCESS << "Processed getCurrentTexture" << std::endl;
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

const std::pair<float, float> GUI::ECS::Components::AnimationComponent::getFrameDimensions() const
{
    if (_frames.size() <= 0) {
        throw CustomExceptions::NoAnimationFrames();
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
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Looped: " + Recoded::myToString(_looped) + "\n";
    result += indentation + "- Loop: " + Recoded::myToString(_loop) + "\n";
    result += indentation + "- Paused: " + Recoded::myToString(_paused) + "\n";
    result += indentation + "- Playing: " + Recoded::myToString(_playing) + "\n";
    result += indentation + "- Stopped: " + Recoded::myToString(_stopped) + "\n";
    result += indentation + "- Has Ticked: " + Recoded::myToString(_hasTicked) + "\n";
    result += indentation + "- Read Reverse: " + Recoded::myToString(_readReverse) + "\n";
    result += indentation + "- Frame Delay: " + Recoded::myToString(_frameDelay) + "\n";
    result += indentation + "- Frame Initial: " + Recoded::myToString(_frameInitial) + "\n";
    result += indentation + "- Current Frame: " + Recoded::myToString(_currentFrame) + "\n";
    result += indentation + "- Total Frames: " + Recoded::myToString(_totalFrames) + "\n";
    result += indentation + "- Base texture: {\n" + _baseTexture.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Frames: {\n";
    for (unsigned int i = 0; i < _frames.size(); i++) {
        result += indentation + "\t" + Recoded::myToString(i) + ": {\n";
        result += _frames[i].getInfo(indent + 2);
        result += indentation + "\t}\n";
    }
    result += indentation + "}\n";
    result += indentation + "Current Texture: {\n" + _currentTexture.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "Clock: {\n" + _clock.getInfo(indent + 1) + "}\n";
    return result;
}

const GUI::ECS::Systems::Clock GUI::ECS::Components::AnimationComponent::getClock() const
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
        throw CustomExceptions::InvalidIndex("<There are no frames>", "<Have you thought of adding frames to the class?>", "<If not use the setAnimation function>");
    }

    if (nextFrame > _totalFrames && _loop) {
        if (_frameInitial > _totalFrames) {
            throw CustomExceptions::InvalidIndex(std::to_string(_frameInitial), "0", std::to_string(_totalFrames));
        }
        _currentFrame = _frameInitial;
    } else if (nextFrame > _totalFrames && !_loop) {
        _currentFrame = 0;
    } else {
        _currentFrame = nextFrame;
    }
    _currentTexture = _frames[_currentFrame];
}

void GUI::ECS::Components::AnimationComponent::_processAnimation(const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
{
    PRECISE_DEBUG << "Implement spritesheet animation cutting." << std::endl;

    GUI::ECS::Components::CollisionComponent spritesheetSize;
    std::any textureCapsule = _baseTexture.getTexture();
    if (!textureCapsule.has_value()) {
        throw CustomExceptions::NoTexture("Base texture for the spritesheet animation");
    }
    PRECISE_DEBUG << "Getting the texture" << std::endl;
    try {
        sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
        PRECISE_DEBUG << "Getting the texture size" << std::endl;
        sf::Vector2u tmp = texture.getSize();
        spritesheetSize.setDimension({ tmp.x, tmp.y });
    }
    catch (std::bad_any_cast &e) {
        throw CustomExceptions::NoTexture("Base texture for the spritesheet animation, <std::any , bad cast error>, system error: " + std::string(e.what()));
    }

}


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::AnimationComponent &item)
{
    os << item.getInfo();
    return os;
}
