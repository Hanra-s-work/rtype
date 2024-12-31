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

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::vector<Recoded::IntRect> &textures)
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

GUI::ECS::Components::AnimationComponent::AnimationComponent(const std::uint32_t entityId, const std::vector<Recoded::IntRect> &rects)
    : EntityNode(entityId)
{
    setAnimation(rects);
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

void GUI::ECS::Components::AnimationComponent::setAnimation(const std::vector<Recoded::IntRect> &rects)
{
    _frames = rects;
    _totalFrames = rects.size();
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
    PRECISE_INFO << "Processing getCurrentFrameIndex" << std::endl;
    _currentFrameIndex = copy.getCurrentFrameIndex();
    PRECISE_SUCCESS << "Processed getCurrentFrameIndex" << std::endl;
    PRECISE_INFO << "Processing getCurrentFrame" << std::endl;
    _currentRectangle = copy.getCurrentFrame();
    PRECISE_SUCCESS << "Processed getCurrentFrame" << std::endl;
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

const std::uint32_t GUI::ECS::Components::AnimationComponent::getCurrentFrameIndex() const
{
    PRECISE_INFO << "Getting the current frame index" << std::endl;
    if (_frames.size() <= 0) {
        PRECISE_CRITICAL << "No frames available" << std::endl;
        throw CustomExceptions::NoAnimationFrames();
    }
    return _currentFrameIndex;
}

const Recoded::IntRect GUI::ECS::Components::AnimationComponent::getCurrentFrame() const
{
    PRECISE_INFO << "Getting the current frame" << std::endl;
    std::uint32_t frame = getCurrentFrameIndex();
    std::uint32_t frameSize = _frames.size();
    if (frame >= frameSize || frame <= frameSize) {
        PRECISE_CRITICAL << "Frame index out of bounds" << std::endl;
        throw CustomExceptions::InvalidIndex(std::to_string(frame), "0", std::to_string(frameSize));
    }
    PRECISE_SUCCESS << "Getting the current frame frame list." << std::endl;
    return _frames[frame];
}

const GUI::ECS::Components::TextureComponent GUI::ECS::Components::AnimationComponent::getBaseTexture() const
{
    return _baseTexture;
}

const std::pair<int, int> GUI::ECS::Components::AnimationComponent::getFrameDimensions() const
{
    PRECISE_INFO << "Getting the frame dimension" << std::endl;
    if (_frames.size() <= 0) {
        PRECISE_CRITICAL << "No frames available" << std::endl;
        throw CustomExceptions::NoAnimationFrames();
    }
    PRECISE_SUCCESS << "Getting the frame dimensions from the first frame." << std::endl;
    return _frames[0].size;
}

const Recoded::IntRect GUI::ECS::Components::AnimationComponent::getCurrentRectangle() const
{
    return getCurrentRectangle();
}

const std::vector<Recoded::IntRect> GUI::ECS::Components::AnimationComponent::getFrames() const
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
    result += indentation + "- Current Frame: " + Recoded::myToString(_currentFrameIndex) + "\n";
    result += indentation + "- Total Frames: " + Recoded::myToString(_totalFrames) + "\n";
    result += indentation + "- Base texture: {\n" + _baseTexture.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Frames: {\n";
    for (unsigned int i = 0; i < _frames.size(); i++) {
        result += indentation + "\t- " + Recoded::myToString(i) + ": " + Recoded::myToString(_frames[i]) + "\n";
    }
    result += indentation + "}\n";
    result += indentation + "Current Rectangle: " + Recoded::myToString(_currentRectangle) + "\n";
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
    if (_paused) {
        PRECISE_INFO << "The animation ticking is paused." << std::endl;
        return;
    }

    if (_frames.empty()) {
        PRECISE_CRITICAL << "There are no frames to render." << std::endl;
        throw CustomExceptions::InvalidIndex("<There are no frames>", "<Have you thought of adding frames to the class?>", "<If not use the setAnimation function>");
    }

    if (_frameInitial > _totalFrames) {
        PRECISE_CRITICAL << "The default frame is greater than "
            << " the total amount of frames, frame initial: "
            << std::to_string(_frameInitial)
            << "minimum frames: 0"
            << "maximum frames:" << std::to_string(_totalFrames)
            << std::endl;
        throw CustomExceptions::InvalidIndex(std::to_string(_frameInitial), "0", std::to_string(_totalFrames));
    }

    if (!_readReverse) {
        _tickRegular();
    } else {
        _tickReverse();
    }
}

void GUI::ECS::Components::AnimationComponent::_tickReverse()
{

    std::uint32_t nextFrame = _currentFrameIndex - 1;


    if (nextFrame == std::numeric_limits<std::uint32_t>::max() && _readReverse) {
        PRECISE_INFO << "The next frame if negative, resetting counter to the maximum available frames." << std::endl;
        if (_loop) {
            PRECISE_INFO << "Looping is enabled, the sprite will thus return to the last frame." << std::endl;
            nextFrame = _totalFrames - 1;
        } else {
            if (_frameInitial > _totalFrames) {
                PRECISE_CRITICAL << "The default frame is greater than "
                    << " the total amount of frames, frame initial: "
                    << std::to_string(_frameInitial)
                    << "minimum frames: 0"
                    << "maximum frames:" << std::to_string(_totalFrames)
                    << std::endl;
                throw CustomExceptions::InvalidIndex(std::to_string(_frameInitial), "0", std::to_string(_totalFrames));
            }
            _currentFrameIndex = _frameInitial;
        }
    } else {
        _currentFrameIndex = nextFrame;
    }
    _currentRectangle = _frames[_currentFrameIndex];

};

void GUI::ECS::Components::AnimationComponent::_tickRegular()
{
    std::uint32_t nextFrame = _currentFrameIndex + 1;


    if (nextFrame >= _totalFrames && !_readReverse) {
        PRECISE_INFO << "The next frame if negative, resetting counter to the maximum available frames." << std::endl;
        if (_loop) {
            PRECISE_INFO << "Looping is enabled, the sprite will thus return to the last frame." << std::endl;
            nextFrame = 0;
        } else {
            if (_frameInitial > _totalFrames) {
                PRECISE_CRITICAL << "The default frame is greater than "
                    << " the total amount of frames, frame initial: "
                    << std::to_string(_frameInitial)
                    << "minimum frames: 0"
                    << "maximum frames:" << std::to_string(_totalFrames)
                    << std::endl;
                throw CustomExceptions::InvalidIndex(std::to_string(_frameInitial), "0", std::to_string(_totalFrames));
            }
            _currentFrameIndex = _frameInitial;
        }
    } else {
        _currentFrameIndex = nextFrame;
    }
    _currentRectangle = _frames[_currentFrameIndex];
};

void GUI::ECS::Components::AnimationComponent::_processAnimation(const unsigned int frameWidth, const unsigned int frameHeight, const bool startLeft, const bool startTop)
{
    PRECISE_DEBUG << "User provided values: frameWidth: "
        << Recoded::myToString(frameWidth)
        << ", frameHeight: " << Recoded::myToString(frameHeight)
        << ", starLeft: " << Recoded::myToString(startLeft)
        << ", startTop: " << Recoded::myToString(startTop)
        << std::endl;

    GUI::ECS::Components::CollisionComponent spritesheetSize;
    std::any textureCapsule = _baseTexture.getTexture();
    if (!textureCapsule.has_value()) {
        PRECISE_CRITICAL << "Texture is not set." << std::endl;
        throw CustomExceptions::NoTexture("Base texture for the spritesheet animation");
    }
    PRECISE_DEBUG << "Getting the texture" << std::endl;
    std::optional<sf::Texture> OptionalTexture = Utilities::unCast<sf::Texture, CustomExceptions::NoTexture>(textureCapsule, true, "Base texture for the spritesheet animation, <std::any , bad cast error>, system error: ");
    if (!OptionalTexture.has_value()) {
        PRECISE_ERROR << "The decasting has failed, skipping the rest of the function" << std::endl;
        return;
    }
    sf::Texture texture = OptionalTexture.value();
    PRECISE_DEBUG << "Getting the texture size" << std::endl;
    sf::Vector2u textureDim = texture.getSize();
    PRECISE_DEBUG << "Texture size gathered ( width: " << textureDim.x
        << " height: " << textureDim.y << ")" << std::endl;
    spritesheetSize.setDimension({ textureDim.x, textureDim.y });
    PRECISE_INFO << "Checking if the texture width and height can contain"
        << " the required frameWidth (" << frameWidth
        << ") and fameHeight (" << frameHeight << ")"
        << std::endl;
    if (frameWidth <= 0) {
        PRECISE_ERROR << "Frame width must be greater than zero." << std::endl;
        throw CustomExceptions::InvalidWidth(std::to_string(frameWidth), "1", std::to_string(spritesheetSize.getWidth()));
    }
    if (frameHeight <= 0) {
        PRECISE_ERROR << "Frame height must be greater than zero." << std::endl;
        throw CustomExceptions::InvalidHeight(std::to_string(frameHeight), "1", std::to_string(spritesheetSize.getHeight()));
    }
    if (frameWidth > spritesheetSize.getWidth()) {
        PRECISE_CRITICAL << "The frame width is greater than the texture width, "
            << "frame width: " << frameWidth
            << "texture width: " << spritesheetSize.getWidth()
            << std::endl;
        throw CustomExceptions::InvalidWidth(Recoded::myToString(frameWidth), "0", Recoded::myToString(textureDim.x));
    }
    if (frameHeight > spritesheetSize.getHeight()) {
        PRECISE_CRITICAL << "The frame height is greater than the texture height, "
            << "frame height: " << frameHeight
            << "texture height: " << spritesheetSize.getHeight()
            << std::endl;
        throw CustomExceptions::InvalidHeight(Recoded::myToString(frameHeight), "0", Recoded::myToString(textureDim.y));
    }
    PRECISE_INFO << "Cutting the texture into frames" << std::endl;
    const int columns = spritesheetSize.getWidth() / frameWidth;
    const int rows = spritesheetSize.getHeight() / frameHeight;

    const short int columUpdater = _getIndexUpdater(startLeft);
    const short int rowUpdater = _getIndexUpdater(startTop);

    unsigned int posx = 0;
    unsigned int posy = 0;

    if (startTop) {
        PRECISE_INFO << "The texture is set to be cut from the top." << std::endl;
        posy = 0;
    } else {
        PRECISE_INFO << "The texture is set to be cut from the bottom." << std::endl;
        posy = rows - 1;
    }

    _totalFrames = (columns * rows);
    PRECISE_INFO << "There are : " << _totalFrames << " in total" << std::endl;
    std::pair<int, int> pos{ posy, posx };
    for (; _continueLoop(startTop, posy, rows); posy += rowUpdater) {
        posx = (columns - 1);
        if (startLeft) {
            posx = 0;
        }
        for (posx = 0; _continueLoop(startLeft, posx, columns); posx += columUpdater) {
            PRECISE_DEBUG << "Processing frame: " << Recoded::myToString<unsigned int>({ posx, posy }) << std::endl;
            std::pair<int, int> position = {
                (posx * frameWidth),
                (posy * frameHeight)
            };
            std::pair<int, int> dimension = {
                ((posx * frameWidth) + frameWidth),
                ((posy * frameHeight) + frameHeight)
            };
            Recoded::IntRect viewField(position, dimension);
            _frames.push_back(viewField);
            PRECISE_DEBUG << "Adding a new frame : " << Recoded::myToString(viewField) << std::endl;
        }
    }
    PRECISE_SUCCESS << "The frames have been processed." << std::endl;
}

const short int GUI::ECS::Components::AnimationComponent::_getIndexUpdater(const bool startBegining) const
{
    if (startBegining) {
        return 1;
    }
    return (-1);
}

const bool GUI::ECS::Components::AnimationComponent::_continueLoop(const bool startBegining, const unsigned int position, const unsigned int maxValue) const
{
    if (startBegining) {
        return (position < maxValue);
    }
    return (position > 0);
}

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::AnimationComponent &item)
{
    os << item.getInfo();
    return os;
}
