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

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(0)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
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

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
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

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setCollision(collision);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setAnimation(animation);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processSprite();
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
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

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
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

void GUI::ECS::Components::SpriteComponent::setCollision(const GUI::ECS::Components::CollisionComponent &copy)
{
    _collision.update(copy);
    _processCollision();
    _collisionSet = true;
};

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const std::string &spritesheetPath)
{
    _spritesheet.setFilePath(spritesheetPath);
    if (!_sfSprite.has_value()) {
        _sfSprite.emplace(_spritesheet.getTexture());
    } else {
        _sfSprite->setTexture(_spritesheet.getTexture());
    }
    _spriteSet = true;
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setNormalColor(const sf::Color &color)
{
    _normalColor = color;
}

void GUI::ECS::Components::SpriteComponent::setHoverColor(const sf::Color &color)
{
    _hoverColor = color;
}

void GUI::ECS::Components::SpriteComponent::setClickedColor(const sf::Color &color)
{
    _clickedColor = color;
}

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    _spritesheet.update(spritesheetTexture);
    if (_sfSprite.has_value()) {
        _sfSprite->setTexture(_spritesheet.getTexture());
        _spriteSet = true;
    }
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setAnimation(const GUI::ECS::Components::AnimationComponent &animation)
{
    _animation.update(animation);
    if (_sfSprite.has_value()) {
        _sfSprite->setTexture(_animation.getCurrentTexture().getTexture());
        _spriteSet = true;
    }
    _animationSet = true;
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

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Components::SpriteComponent &copy)
{
    _spriteName = copy.getName();
    setSpritesheet(copy.getSpritesheet());
    setCollision(copy.getCollision());
    setAnimation(copy.getAnimation());
}

void GUI::ECS::Components::SpriteComponent::render(sf::RenderWindow &window) const
{
    if (!_sfSprite.has_value()) {
        return;
    }
    if (!_spriteSet) {
        throw MyException::NoSprite();
    }
    if (_visible) {
        sf::Sprite node = _sfSprite.value();
        window.draw(node);
    }
}

bool GUI::ECS::Components::SpriteComponent::isCollisionSet() const
{
    return _collisionSet;
}

bool GUI::ECS::Components::SpriteComponent::isAnimationSet() const
{
    return _animationSet;
}

bool GUI::ECS::Components::SpriteComponent::isSpritesheetSet() const
{
    return _spritesheetSet;
}

bool GUI::ECS::Components::SpriteComponent::isSpriteSet() const
{
    return _spriteSet;
}

void GUI::ECS::Components::SpriteComponent::checkTick()
{
    _spriteSet = false;
    if (_animationSet) {
        _animation.checkTick();
        if (_animation.hasTicked()) {
            GUI::ECS::Components::TextureComponent node = _animation.getCurrentTexture();
            if (!_sfSprite.has_value()) {
                _sfSprite->setTexture(node.getTexture(), false);
                _spriteSet = true;
            }
        }
    }
}

std::string GUI::ECS::Components::SpriteComponent::getName() const
{
    return _spriteName;
}

GUI::ECS::Components::TextureComponent GUI::ECS::Components::SpriteComponent::getSpritesheet() const
{
    if (!_spritesheetSet) {
        throw MyException::NoSpriteSheet();
    }
    return _spritesheet;
}

GUI::ECS::Components::CollisionComponent GUI::ECS::Components::SpriteComponent::getCollision() const
{
    if (!_collisionSet) {
        throw MyException::NoCollision();
    }
    return _collision;
}

GUI::ECS::Components::AnimationComponent GUI::ECS::Components::SpriteComponent::getAnimation() const
{
    if (!_animationSet) {
        throw MyException::NoAnimation();
    }
    return _animation;
}

sf::Color GUI::ECS::Components::SpriteComponent::getNormalColor() const
{
    return _normalColor;
}

sf::Color GUI::ECS::Components::SpriteComponent::getHoverColor() const
{
    return _hoverColor;
}

sf::Color GUI::ECS::Components::SpriteComponent::getClickedColor() const
{
    return _clickedColor;
}

GUI::ECS::Components::SpriteComponent &GUI::ECS::Components::SpriteComponent::operator =(const GUI::ECS::Components::SpriteComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

void GUI::ECS::Components::SpriteComponent::_processSpriteColor()
{
    if (!_sfSprite.has_value()) {
        return;
    }
    if (!_collisionSet) {
        return;
    }
    if (_collision.isClicked()) {
        _sfSprite->setColor(_clickedColor);
    } else if (_collision.isHovered()) {
        _sfSprite->setColor(_hoverColor);
    } else {
        _sfSprite->setColor(_normalColor);
    }
}

void GUI::ECS::Components::SpriteComponent::_processCollision()
{
    if (!_sfSprite.has_value()) {
        return;
    }
    _sfSprite->setPosition(_collision.getPosition());
    _sfSprite->setScale(_collision.getDimension());
    _processSpriteColor();
}

void GUI::ECS::Components::SpriteComponent::_processSprite()
{
    if (!_sfSprite.has_value()) {
        _sfSprite.emplace(_spritesheet.getTexture());
    }
    _processCollision();
    _processSpriteColor();
}
