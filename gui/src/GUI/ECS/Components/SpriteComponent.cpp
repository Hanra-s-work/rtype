/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SpriteComponent.cpp
*/

#include "GUI/ECS/Components/SpriteComponent.hpp"

GUI::ECS::Components::SpriteComponent::SpriteComponent() :EntityNode(0) {};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name)
    : EntityNode(0)
{
    setName(name);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::CollisionComponent &collision)
    : EntityNode(0)
{
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0)
{
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0)
{
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const std::string &spritesheetPath)
    : EntityNode(0)
{
    setName(name);
    setSpritesheet(spritesheetPath);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0)
{
    setName(name);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};



GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId)
    : EntityNode(entityId)
{
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name)
    : EntityNode(entityId)
{
    setName(name);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::CollisionComponent &collision)
    : EntityNode(entityId)
{
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId)
{
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId)
{
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const std::string &spritesheetPath)
    : EntityNode(entityId)
{
    setName(name);
    setSpritesheet(spritesheetPath);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId)
{
    setName(name);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};


GUI::ECS::Components::SpriteComponent::~SpriteComponent() {};

void GUI::ECS::Components::SpriteComponent::setName(const std::string &name)
{
    _spriteName = name;
};

void GUI::ECS::Components::SpriteComponent::setApplication(const std::string &application)
{
    _application = application;
}

void GUI::ECS::Components::SpriteComponent::setCollision(const GUI::ECS::Components::CollisionComponent &copy)
{
    _collision.update(copy);
    _processCollision();
    _collisionSet = true;
};

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const std::string &spritesheetPath)
{
    _spritesheet.setFilePath(spritesheetPath);
    std::any textureCapsule = _spritesheet.getTexture();
    if (!textureCapsule.has_value()) {
        return;
    }
    sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
    if (!_sfSprite.has_value()) {
        _sfSprite.emplace(texture);
    } else {
        _sfSprite->setTexture(texture);
    }
    _spriteSet = true;
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setNormalColor(const GUI::ECS::Utilities::Colour &color)
{
    _normalColor = color;
}

void GUI::ECS::Components::SpriteComponent::setHoverColor(const GUI::ECS::Utilities::Colour &color)
{
    _hoverColor = color;
}

void GUI::ECS::Components::SpriteComponent::setClickedColor(const GUI::ECS::Utilities::Colour &color)
{
    _clickedColor = color;
}

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    _spritesheet.update(spritesheetTexture);
    _spritesheetSet = true;
    if (!_sfSprite.has_value()) {
        return;
    }
    std::any textureCapsule = _spritesheet.getTexture();
    if (!textureCapsule.has_value()) {
        return;
    }
    sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
    _sfSprite->setTexture(texture);
    _spriteSet = true;
}

void GUI::ECS::Components::SpriteComponent::setAnimation(const GUI::ECS::Components::AnimationComponent &animation)
{
    _animation.update(animation);
    _collision.setDimension(animation.getFrameDimensions());
    _animationSet = true;
    if (!_sfSprite.has_value()) {
        return;
    }
    std::any textureCapsule = _animation.getCurrentTexture().getTexture();
    if (!textureCapsule.has_value()) {
        return;
    }
    sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
    _sfSprite->setTexture(texture);
    _spriteSet = true;


}

void GUI::ECS::Components::SpriteComponent::setVisible(const bool visible)
{
    _visible = visible;
}

void GUI::ECS::Components::SpriteComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
}

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    if (_collisionSet) {
        _collision.update(mouse);
        _processCollision();
    } else {
        throw MyException::NoCollision();
    }
}

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Components::AnimationComponent &animation)
{
    setAnimation(animation);
}

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Components::SpriteComponent &copy)
{
    _spriteName = copy.getName();
    setSpritesheet(copy.getSpritesheet());
    setCollision(copy.getCollision());
    setAnimation(copy.getAnimation());
}

std::any GUI::ECS::Components::SpriteComponent::render() const
{
    if (!_visible || !_sfSprite.has_value()) {
        Debug::getInstance() << "Instance is hidden or no sfImage instance found, not rendering" << std::endl;
        return std::nullopt;
    }
    return std::make_any<sf::Sprite>(_sfSprite.value());
};

void GUI::ECS::Components::SpriteComponent::start()
{
    _animation.start();
}

void GUI::ECS::Components::SpriteComponent::pause()
{
    _animation.pause();
}

void GUI::ECS::Components::SpriteComponent::resume()
{
    _animation.resume();
}

void GUI::ECS::Components::SpriteComponent::stop()
{
    _animation.stop();
}

const bool GUI::ECS::Components::SpriteComponent::isCollisionSet() const
{
    return _collisionSet;
}

const bool GUI::ECS::Components::SpriteComponent::isAnimationSet() const
{
    return _animationSet;
}

const bool GUI::ECS::Components::SpriteComponent::isSpritesheetSet() const
{
    return _spritesheetSet;
}

const bool GUI::ECS::Components::SpriteComponent::isSpriteSet() const
{
    return _spriteSet;
}

const bool GUI::ECS::Components::SpriteComponent::isVisible() const
{
    return _visible;
}

const bool GUI::ECS::Components::SpriteComponent::isLooping() const
{
    return _animation.isLooping();
}

const bool GUI::ECS::Components::SpriteComponent::isPaused() const
{
    return _animation.isPaused();
}

const bool GUI::ECS::Components::SpriteComponent::isPlaying() const
{
    return _animation.isPlaying();
}

const bool GUI::ECS::Components::SpriteComponent::isStopped() const
{
    return _animation.isStopped();
}

const bool GUI::ECS::Components::SpriteComponent::hasTicked()
{
    return _animation.hasTicked();
}

const bool GUI::ECS::Components::SpriteComponent::hasLooped() const
{
    return _animation.hasLooped();
}

void GUI::ECS::Components::SpriteComponent::checkTick()
{
    _spriteSet = false;
    if (!_animationSet) {
        return;
    }
    _animation.checkTick();
    if (!_animation.hasTicked()) {
        return;
    }
    GUI::ECS::Components::TextureComponent textureComponent = _animation.getCurrentTexture();
    std::any textureCapsule = textureComponent.getTexture();
    if (!textureCapsule.has_value()) {
        return;
    }
    sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);

    if (!_sfSprite.has_value()) {
        _initialiseSprite();
    }
    _sfSprite->setTexture(texture, false);
    _spriteSet = true;
}

const bool GUI::ECS::Components::SpriteComponent::getVisible() const
{
    return _visible;
}

const std::string GUI::ECS::Components::SpriteComponent::getName() const
{
    return _spriteName;
}

const std::string GUI::ECS::Components::SpriteComponent::getApplication() const
{
    return _application;
}

const GUI::ECS::Components::TextureComponent GUI::ECS::Components::SpriteComponent::getSpritesheet() const
{
    if (!_spritesheetSet) {
        throw MyException::NoSpriteSheet();
    }
    return _spritesheet;
}

const GUI::ECS::Components::CollisionComponent GUI::ECS::Components::SpriteComponent::getCollision() const
{
    if (!_collisionSet) {
        throw MyException::NoCollision();
    }
    return _collision;
}

const GUI::ECS::Components::AnimationComponent GUI::ECS::Components::SpriteComponent::getAnimation() const
{
    if (!_animationSet) {
        throw MyException::NoAnimation();
    }
    return _animation;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::SpriteComponent::getNormalColor() const
{
    return _normalColor;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::SpriteComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::SpriteComponent::getClickedColor() const
{
    return _clickedColor;
}


const std::string GUI::ECS::Components::SpriteComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Sprite:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + MyRecodes::myToString(_visible) + "\n";
    result += indentation + "- Name: '" + _spriteName + "'\n";
    result += indentation + "- Application: '" + _application + "'\n";
    result += indentation + "- Spritesheet Set: " + MyRecodes::myToString(_spritesheetSet) + "\n";
    result += indentation + "- Spritesheet: {\n" + _spritesheet.getInfo(indent + 1) + "}\n";
    result += indentation + "- Collision Set: " + MyRecodes::myToString(_collisionSet) + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + "}\n";
    result += indentation + "- Animation Set: " + MyRecodes::myToString(_animationSet) + "}\n";
    result += indentation + "- Animation: {\n" + _animation.getInfo(indent + 1) + "}\n";
    result += indentation + "- Spritesheet Set: " + MyRecodes::myToString(_spriteSet) + "\n";
    result += indentation + "- (sfSprite) Has sprite: " + MyRecodes::myToString(_sfSprite.has_value()) + "\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    return result;
}

GUI::ECS::Components::SpriteComponent &GUI::ECS::Components::SpriteComponent::operator =(const GUI::ECS::Components::SpriteComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

void GUI::ECS::Components::SpriteComponent::_initialiseSprite()
{
    if (_sfSprite.has_value()) {
        return;
    }
    std::any textureCapsule = _spritesheet.getTexture();
    if (textureCapsule.has_value()) {
        sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
        _sfSprite.emplace(texture);
    }
}

void GUI::ECS::Components::SpriteComponent::_processSpriteColor()
{
    if (!_sfSprite.has_value()) {
        return;
    }
    if (!_collisionSet) {
        return;
    }
    std::any systemColour;
    if (_collision.isClicked()) {
        systemColour = _clickedColor.getRenderColour();
    } else if (_collision.isHovered()) {
        systemColour = _hoverColor.getRenderColour();
    } else {
        systemColour = _normalColor.getRenderColour();
    }
    if (!systemColour.has_value()) {
        throw MyException::NoColour("<There was no content returned by getRenderColour when std::any (containing sf::Font was expected)>");
    }
    try {
        sf::Color result = std::any_cast<sf::Color>(systemColour);
        _sfSprite->setColor(result);
    }
    catch (std::bad_any_cast &e) {
        throw MyException::NoColour("<The content returned by the getRenderColour function is not of type sf::Color>, system error: " + std::string(e.what()));
    }
}

void GUI::ECS::Components::SpriteComponent::_processCollision()
{
    _initialiseSprite();
    if (!_sfSprite.has_value()) {
        return;
    }
    std::pair<float, float> pos = _collision.getPosition();
    std::pair<float, float> dim = _collision.getDimension();
    _sfSprite->setPosition({ pos.first, pos.second });
    _sfSprite->setScale({ dim.first, dim.second });
    _processSpriteColor();
}

void GUI::ECS::Components::SpriteComponent::_processSprite()
{
    _initialiseSprite();
    _processCollision();
    _processSpriteColor();
}

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::SpriteComponent &item)
{
    os << item.getInfo();
    return os;
}
