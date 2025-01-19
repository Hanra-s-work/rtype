/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SpriteComponent.cpp
*/

/**
 * @file SpriteComponent.cpp
 *
 * @brief File in charge of containing the code for the sprite component
 */

#include "GUI/ECS/Components/SpriteComponent.hpp"

GUI::ECS::Components::SpriteComponent::SpriteComponent()
    :EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Systems::Collision &collision)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const std::string &spritesheetPath)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setSpritesheet(spritesheetPath);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0), _normalColor(0), _clickedColor(0)
{
    setName(name);
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(0), _spritesheet(0), _collision(0), _animation(0),
    _hoverColor(0, GUI::ECS::Systems::Colour::White), _normalColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
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
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Collision &collision)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const std::string &spritesheetPath)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setSpritesheet(spritesheetPath);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    PRETTY_INFO << "In sprite constructor taking an entity id, a name and an animation." << std::endl;
    setName(name);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    PRETTY_INFO << "In sprite constructor taking an entity id, a name and a spritesheet texture." << std::endl;
    setName(name);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::AnimationComponent &animation)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Systems::Collision &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId), _spritesheet(entityId), _collision(entityId), _animation(entityId),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _normalColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
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
    PRETTY_INFO << "Setting sprite name to '" << name << "'" << std::endl;
    _spriteName = name;
    PRETTY_SUCCESS << "Sprite name set to '" << name << "'" << std::endl;
};

void GUI::ECS::Components::SpriteComponent::setApplication(const std::string &application)
{
    _application = application;
}

void GUI::ECS::Components::SpriteComponent::setCollision(const GUI::ECS::Systems::Collision &copy)
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
        PRETTY_ERROR << "There is no texture to manage" << std::endl;
        return;
    }
    _spritesheetSet = true;
    setSpritesheet(_spritesheet);
}

void GUI::ECS::Components::SpriteComponent::setNormalColor(const GUI::ECS::Systems::Colour &color)
{
    _normalColor = color;
}

void GUI::ECS::Components::SpriteComponent::setHoverColor(const GUI::ECS::Systems::Colour &color)
{
    _hoverColor = color;
}

void GUI::ECS::Components::SpriteComponent::setClickedColor(const GUI::ECS::Systems::Colour &color)
{
    _clickedColor = color;
}

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    _spritesheet.update(spritesheetTexture);
    _spritesheetSet = true;
    if (!_sfSprite.has_value()) {
        PRETTY_ERROR << "There is no sprite instance" << std::endl;
        return;
    }
    std::any textureCapsule = _spritesheet.getTexture();
    if (!textureCapsule.has_value()) {
        PRETTY_ERROR << "There is not texture instance" << std::endl;
        return;
    }
    std::shared_ptr<sf::Texture> texture = std::any_cast<std::shared_ptr<sf::Texture>>(textureCapsule);
    _sfSprite->setTexture(*texture);
    _spriteSet = true;
}

void GUI::ECS::Components::SpriteComponent::setAnimation(const GUI::ECS::Components::AnimationComponent &animation)
{
    PRETTY_INFO << "Setting sprite animation." << std::endl;
    PRETTY_INFO << "Updating the _animation node with the child version." << std::endl;
    _animation.update(animation);
    PRETTY_SUCCESS << "Animation updated" << std::endl;
    PRETTY_INFO << "Updating the collision node with the child version. '" << _spriteName << "'" << std::endl;
    _collision.setDimension(animation.getFrameDimensions());
    PRETTY_SUCCESS << "Collision updated for sprite '" << _spriteName << "'" << std::endl;
    _animationSet = true;
    _collisionSet = true;
    setSpritesheet(animation.getBaseTexture());
    PRETTY_SUCCESS << "Spritesheet set" << std::endl;
}

void GUI::ECS::Components::SpriteComponent::setVisible(const bool visible)
{
    _visible = visible;
}

void GUI::ECS::Components::SpriteComponent::setPosition(const std::pair<int, int> &pos)
{
    _collision.setPosition(pos);
    _processCollision();
}

void GUI::ECS::Components::SpriteComponent::setDimension(const std::pair<float, float> &dim)
{
    _collision.setDimension(dim);
    _processCollision();
}

void GUI::ECS::Components::SpriteComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
}

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    if (_collisionSet) {
        _collision.update(mouse);
        _processCollision();
    } else {
        throw CustomExceptions::NoCollision();
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
        PRETTY_DEBUG << "Instance is hidden or no sfImage instance found, not rendering" << std::endl;
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
    PRETTY_DEBUG << "Checking sprite tick" << std::endl;
    _spriteSet = false;
    if (!_animationSet) {
        PRETTY_ERROR << "There are no animations set, skipping tick" << std::endl;
        return;
    }
    PRETTY_INFO << "Running animation.checkTick()" << std::endl;
    _animation.checkTick();
    PRETTY_INFO << "Animation checkTick ran, checking if frames need to be updated." << std::endl;
    if (!_animation.hasTicked()) {
        PRETTY_WARNING << "No tick has occurred yet, nothing to do, exiting function" << std::endl;
        return;
    }
    PRETTY_DEBUG << "Animation has ticked, Getting the updated rectangle." << std::endl;
    Recoded::IntRect RectComponent = _animation.getCurrentRectangle();
    PRETTY_DEBUG << "Got the updated rectangle, updating sprite." << std::endl;
    if (!_sfSprite.has_value()) {
        PRETTY_WARNING << "There is no sprite value, initialising sprite." << std::endl;
        _initialiseSprite();
        PRETTY_SUCCESS << "Sprite initialised." << std::endl;
    }
    PRETTY_DEBUG << "Converting internal rectangle to sf::IntRect." << std::endl;
    sf::IntRect transporter = {
        {
            RectComponent.position.first,
            RectComponent.position.second
        },
        {
            RectComponent.size.first,
            RectComponent.size.second
        }
    };
    PRETTY_DEBUG << "sf::IntRect initialised." << std::endl;
    _sfSprite->setTextureRect(transporter);
    PRETTY_DEBUG << "Texture rect set." << std::endl;
    _spriteSet = true;
}

void GUI::ECS::Components::SpriteComponent::forceTick()
{
    PRETTY_DEBUG << "Checking sprite tick" << std::endl;
    _spriteSet = false;
    if (!_animationSet) {
        PRETTY_ERROR << "There are no animations set, skipping tick" << std::endl;
        return;
    }
    PRETTY_INFO << "Running animation.forceTick()" << std::endl;
    _animation.forceTick();
    PRETTY_INFO << "Animation forceTick ran, updating the frame." << std::endl;
    PRETTY_DEBUG << "Animation has ticked, Getting the updated rectangle." << std::endl;
    Recoded::IntRect RectComponent = _animation.getCurrentRectangle();
    PRETTY_DEBUG << "Got the updated rectangle, updating sprite." << std::endl;
    if (!_sfSprite.has_value()) {
        PRETTY_WARNING << "There is no sprite value, initialising sprite." << std::endl;
        _initialiseSprite();
        PRETTY_SUCCESS << "Sprite initialised." << std::endl;
    }
    PRETTY_DEBUG << "Converting internal rectangle to sf::IntRect." << std::endl;
    sf::IntRect transporter = {
        {
            RectComponent.position.first,
            RectComponent.position.second
        },
        {
            RectComponent.size.first,
            RectComponent.size.second
        }
    };
    PRETTY_DEBUG << "sf::IntRect initialised." << std::endl;
    _sfSprite->setTextureRect(transporter);
    PRETTY_DEBUG << "Texture rect set." << std::endl;
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
        throw CustomExceptions::NoSpriteSheet();
    }
    return _spritesheet;
}

const GUI::ECS::Systems::Collision GUI::ECS::Components::SpriteComponent::getCollision() const
{
    if (!_collisionSet) {
        throw CustomExceptions::NoCollision();
    }
    return _collision;
}

const GUI::ECS::Components::AnimationComponent GUI::ECS::Components::SpriteComponent::getAnimation() const
{
    if (!_animationSet) {
        throw CustomExceptions::NoAnimation();
    }
    return _animation;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::SpriteComponent::getNormalColor() const
{
    return _normalColor;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::SpriteComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::SpriteComponent::getClickedColor() const
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
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
    result += indentation + "- Name: '" + _spriteName + "'\n";
    result += indentation + "- Application: '" + _application + "'\n";
    result += indentation + "- Spritesheet Set: " + Recoded::myToString(_spritesheetSet) + "\n";
    result += indentation + "- Spritesheet: {\n" + _spritesheet.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Collision Set: " + Recoded::myToString(_collisionSet) + "\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Animation Set: " + Recoded::myToString(_animationSet) + "\n";
    result += indentation + "- Animation: {\n" + _animation.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Spritesheet Set: " + Recoded::myToString(_spriteSet) + "\n";
    result += indentation + "- (sfSprite) Has sprite: " + Recoded::myToString(_sfSprite.has_value()) + "\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + indentation + "}\n";
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
        std::optional<std::shared_ptr<sf::Texture>> texture = std::any_cast<std::shared_ptr<sf::Texture>>(textureCapsule);
        if (!texture.has_value()) {
            PRETTY_ERROR << "No Texture found" << std::endl;
            return;
        }
        _sfSprite.emplace(*(texture.value()));
    }
}

void GUI::ECS::Components::SpriteComponent::_processSpriteColor()
{
    if (!_sfSprite.has_value()) {
        PRETTY_ERROR << "Sprite instance not set" << std::endl;
        return;
    }
    if (!_collisionSet) {
        PRETTY_ERROR << "Collision component not set" << std::endl;
        return;
    }
    std::any systemColour;
    if (_collision.isClicked()) {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _clickedColor << "\n} and corresponds to the _clickedColour"
            << std::endl;
        systemColour = _clickedColor.getRenderColour();
    } else if (_collision.isHovered()) {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _hoverColor << "\n} and corresponds to the _hoverColour"
            << std::endl;
        systemColour = _hoverColor.getRenderColour();
    } else {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _normalColor << "\n} and corresponds to the _normalColour"
            << std::endl;
        systemColour = _normalColor.getRenderColour();
    }
    const std::string errMsg = "<The content returned by the getRenderColour function is not of type sf::Color>, system error: ";
    const std::optional<sf::Color> color = Utilities::unCast<sf::Color, CustomExceptions::NoColour>(systemColour, true, errMsg);
    if (!color.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "No Color found, " << errMsg << std::endl;
        throw CustomExceptions::NoColour(errMsg);
    }
    _sfSprite->setColor(color.value());
    PRETTY_SUCCESS << "Sprite colour has been set" << std::endl;
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
