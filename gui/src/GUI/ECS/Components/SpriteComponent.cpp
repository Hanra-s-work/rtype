/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SpriteComponent.cpp
*/

#include "GUI/ECS/Components/SpriteComponent.hpp"

GUI::ECS::Components::SpriteComponent::SpriteComponent() {};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name)
{
    setName(name);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &spritesheetPath)
{
    setSpritesheet(spritesheetPath);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::CollisionComponent &collision)
{
    setCollision(collision);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation)
{
    setAnimation(animation);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    setSpritesheet(spritesheetTexture);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision)
{
    setName(name);
    setCollision(collision);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation)
{
    setName(name);
    setAnimation(animation);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    setName(name);
    setSpritesheet(spritesheetTexture);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation)
{
    setName(name);
    setCollision(collision);
    setAnimation(animation);
};

GUI::ECS::Components::SpriteComponent::SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    setName(name);
    setCollision(collision);
    setSpritesheet(spritesheetTexture);
};

GUI::ECS::Components::SpriteComponent::~SpriteComponent() {};

void GUI::ECS::Components::SpriteComponent::setName(const std::string &name)
{
    _spriteName = name;
};

void GUI::ECS::Components::SpriteComponent::setCollision(const GUI::ECS::Components::CollisionComponent &copy)
{
    _collision.update(copy);
    _sfSprite.setPosition(_collision.getPosition());
    _sfSprite.setScale(_collision.getDimension());
    _collisionSet = true;
};

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const std::string &spritesheetPath)
{
    _spritesheet.setFilePath(spritesheetPath);
    _sfSprite.setTexture(_spritesheet.getTexture());
    _spriteSet = true;
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    _spritesheet.update(spritesheetTexture);
    _sfSprite.setTexture(_spritesheet.getTexture());
    _spriteSet = true;
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setAnimation(const GUI::ECS::Components::AnimationComponent &animation)
{
    _animation.update(animation);
    _sfSprite.setTexture(_animation.getCurrentTexture().getTexture());
    _spriteSet = true;
    _animationSet = true;
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
    if (!_spriteSet) {
        throw MyException::NoSprite();
    }
    if (_visible) {
        window.draw(_sfSprite);
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
    if (_animationSet) {
        _animation.checkTick();
        if (_animation.hasTicked()) {
            GUI::ECS::Components::TextureComponent node = _animation.getCurrentTexture();
            _sfSprite.setTexture(node.getTexture());
            _spriteSet = true;
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
