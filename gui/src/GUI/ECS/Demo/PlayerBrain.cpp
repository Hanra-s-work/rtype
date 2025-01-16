/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PlayerBrain.cpp
*/

/**
 * @file PlayerBrain.cpp
 *
 * @brief The file in charge of containing the function for the brain of the player
 */

#include "GUI/ECS/Demo/PlayerBrain.hpp"


GUI::ECS::Demo::PlayerBrain::PlayerBrain(const GUI::ECS::Demo::PlayerBrain &copy)
{
    update(copy);
}


void GUI::ECS::Demo::PlayerBrain::setSprite(const GUI::ECS::Components::SpriteComponent &sprite, const GUI::ECS::Components::SpriteComponent &bullet)
{
    _sprite = sprite;
    _bullet.setSprite(bullet);
    _bullet.setVisible(true);
    _bullet.setEnemy(false);
    _bullet.setDirection({ -1,0 });
    _bullet.setDamage(5);
    _bullet.setSpeed(5);
    _collision.update(_sprite.getCollision());
};

void GUI::ECS::Demo::PlayerBrain::setPosition(const std::pair<float, float> &pos)
{
    _collision.setPosition(pos);
    _sprite.setPosition(pos);
};

void GUI::ECS::Demo::PlayerBrain::setHealth(const long int health)
{
    _health = health;
    if (_health <= 0) {
        _health = 0;
    }
}

void GUI::ECS::Demo::PlayerBrain::setVisible(const bool visible)
{
    _visible = visible;
    _sprite.setVisible(visible);
};

const bool GUI::ECS::Demo::PlayerBrain::isColliding(const GUI::ECS::Systems::Collision &second) const
{
    return second.getPositionY() < _collision.getPositionY() + _collision.getHeight()
        && second.getPositionX() < _collision.getPositionX() + _collision.getWidth();
};

const bool GUI::ECS::Demo::PlayerBrain::isVisible() const
{
    return _visible;
};


void GUI::ECS::Demo::PlayerBrain::tick()
{
    _sprite.checkTick();
};

const GUI::ECS::Demo::Bullet GUI::ECS::Demo::PlayerBrain::shoot() const
{
    GUI::ECS::Demo::Bullet shot(_bullet);
    shot.setPosition(_collision.getPosition());
    return shot;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::PlayerBrain::render()
{
    return _sprite;
};

/**
 * @brief Updates the sprite by copying another PlayerBrain.
 *
 * @param copy The PlayerBrain to copy data from.
 */
void GUI::ECS::Demo::PlayerBrain::update(const GUI::ECS::Demo::PlayerBrain &copy)
{
    _health = copy.getHealth();
    _bullet = copy.getBullet();
    _sprite = copy.getSprite();
    _visible = copy.getVisible();
    _collision = copy.getCollision();
}

/**
 * @brief Overloads the assignment operator to copy from another PlayerBrain.
 *
 * @param copy The PlayerBrain to copy data from.
 *
 * @return A reference to the updated instance.
 */
GUI::ECS::Demo::PlayerBrain &GUI::ECS::Demo::PlayerBrain::operator =(const GUI::ECS::Demo::PlayerBrain &copy)
{
    update(copy);
    return *this;
}

const bool GUI::ECS::Demo::PlayerBrain::getVisible() const
{
    return _visible;
}

const unsigned int GUI::ECS::Demo::PlayerBrain::getHealth() const
{
    return _health;
}

const GUI::ECS::Demo::Bullet GUI::ECS::Demo::PlayerBrain::getBullet() const
{
    return _bullet;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::PlayerBrain::getSprite() const
{
    return _sprite;
}

const GUI::ECS::Systems::Collision GUI::ECS::Demo::PlayerBrain::getCollision() const
{
    return _collision;
}
