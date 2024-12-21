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
    _collisionSet = true;
};

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const std::string &spritesheetPath)
{
    _spritesheet.setFilePath(spritesheetPath);
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture)
{
    _spritesheet.update(spritesheetTexture);
    _spritesheetSet = true;
}

void GUI::ECS::Components::SpriteComponent::setAnimation(const GUI::ECS::Components::AnimationComponent &animation)
{
    _animation.update(animation);
    _animationSet = true;
}

void GUI::ECS::Components::SpriteComponent::update(const GUI::ECS::Components::SpriteComponent &copy)
{
    _spriteName = copy.getName();
    setSpritesheet(copy.getSpritesheet());
    setCollision(copy.getCollision());
    setAnimation(copy.getAnimation());
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
