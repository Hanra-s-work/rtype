/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EnemyBrain.cpp
*/

/**
 * @file EnemyBrain.cpp
 *
 * @brief The file in charge of containing the functions that will fill the logic of the enemy movements.
 */

#include "GUI/ECS/Demo/EnemyBrain.hpp"

GUI::ECS::Demo::EnemyBrain::EnemyBrain(const GUI::ECS::Demo::EnemyBrain &copy)
{
    update(copy);
}

void GUI::ECS::Demo::EnemyBrain::setSprite(const GUI::ECS::Components::SpriteComponent &sprite, const GUI::ECS::Components::SpriteComponent &bullet)
{
    _sprite = sprite;
    _bullet.setSprite(bullet);
    _bullet.setVisible(true);
    _bullet.setEnemy(true);
    _bullet.setDirection({ -1,0 });
    _bullet.setDamage(5);
    _bullet.setSpeed(5);
    _collision.update(_sprite.getCollision());
};

void GUI::ECS::Demo::EnemyBrain::setPosition(const std::pair<float, float> &pos)
{
    _collision.setPosition(pos);
    _sprite.setPosition(pos);
};

void GUI::ECS::Demo::EnemyBrain::setHealth(const long int health)
{
    _health = health;
    if (_health <= 0) {
        _health = 0;
    }
}

void GUI::ECS::Demo::EnemyBrain::setVisible(const bool visible)
{
    _visible = visible;
    _sprite.setVisible(visible);
};

const bool GUI::ECS::Demo::EnemyBrain::isColliding(const GUI::ECS::Systems::Collision &second) const
{
    return second.getPositionY() < _collision.getPositionY() + _collision.getHeight()
        && second.getPositionX() < _collision.getPositionX() + _collision.getWidth();
};

const bool GUI::ECS::Demo::EnemyBrain::isVisible() const
{
    return _visible;
};

const std::optional<GUI::ECS::Demo::Bullet> GUI::ECS::Demo::EnemyBrain::tick()
{
    _sprite.checkTick();
    if (_delayBeforeShot == 0) {
        _delayBeforeShot = _randInt(5, 20);
        GUI::ECS::Demo::Bullet shot(_bullet);
        _bullet.setDamage(_randInt(1, 10));
        _bullet.setPosition(_collision.getPosition());
        return std::optional(shot);
    }
    _delayBeforeShot--;
    return std::nullopt;
};

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::EnemyBrain::render()
{
    return _sprite;
};

/**
 * @brief Updates the sprite by copying another EnemyBrain.
 *
 * @param copy The EnemyBrain to copy data from.
 */
void GUI::ECS::Demo::EnemyBrain::update(const GUI::ECS::Demo::EnemyBrain &copy)
{
    _health = copy.getHealth();
    _bullet = copy.getBullet();
    _sprite = copy.getSprite();
    _visible = copy.getVisible();
    _collision = copy.getCollision();
}

/**
 * @brief Overloads the assignment operator to copy from another EnemyBrain.
 *
 * @param copy The EnemyBrain to copy data from.
 *
 * @return A reference to the updated instance.
 */
GUI::ECS::Demo::EnemyBrain &GUI::ECS::Demo::EnemyBrain::operator =(const GUI::ECS::Demo::EnemyBrain &copy)
{
    update(copy);
    return *this;
}

const bool GUI::ECS::Demo::EnemyBrain::getVisible() const
{
    return _visible;
}

const unsigned int GUI::ECS::Demo::EnemyBrain::getHealth() const
{
    return _health;
}

const GUI::ECS::Demo::Bullet GUI::ECS::Demo::EnemyBrain::getBullet() const
{
    return _bullet;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::EnemyBrain::getSprite() const
{
    return _sprite;
}

const GUI::ECS::Systems::Collision GUI::ECS::Demo::EnemyBrain::getCollision() const
{
    return _collision;
}


const int GUI::ECS::Demo::EnemyBrain::_randInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
