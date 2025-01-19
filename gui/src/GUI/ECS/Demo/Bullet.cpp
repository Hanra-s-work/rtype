/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Bullet.cpp
*/

/**
 * @file Bullet.cpp
 *
 * @brief Implementation of the functions for the Bullet class.
 */

#include "GUI/ECS/Demo/Bullet.hpp"

GUI::ECS::Demo::Bullet::Bullet(const std::uint32_t EntityId)
    : EntityNode(EntityId)
{
};

GUI::ECS::Demo::Bullet::Bullet(const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction, const int damage)
    : EntityNode(0), _sprite(sprite), _fromEnemy(fromEnemy), _speed(speed), _direction(direction), _positionInitial(positionInitial), _damage(damage)
{
    _createBullet(positionInitial);
};

GUI::ECS::Demo::Bullet::Bullet(const std::uint32_t EntityId, const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction, const int damage)
    : EntityNode(EntityId), _sprite(sprite), _fromEnemy(fromEnemy), _speed(speed), _direction(direction), _positionInitial(positionInitial), _damage(damage)
{
    _createBullet(positionInitial);
};

GUI::ECS::Demo::Bullet::Bullet(const GUI::ECS::Demo::Bullet &bullet)
    : EntityNode(0)
{
    update(bullet);
};

GUI::ECS::Demo::Bullet::Bullet(const std::uint32_t EntityId, const GUI::ECS::Demo::Bullet &bullet)
    : EntityNode(EntityId)
{
    update(bullet);
};


void GUI::ECS::Demo::Bullet::setVisible(const bool visible)
{
    _visible = visible;
    _sprite.setVisible(visible);
}

void GUI::ECS::Demo::Bullet::setPosition(const std::pair<float, float> &pos)
{
    _collision.setPosition(pos);
    _sprite.setPosition(pos);
};

void GUI::ECS::Demo::Bullet::setSprite(const GUI::ECS::Components::SpriteComponent &sprite)
{
    _sprite.update(sprite);
}

void GUI::ECS::Demo::Bullet::setEnemy(const bool enemy)
{
    _fromEnemy = enemy;
}

void GUI::ECS::Demo::Bullet::setSpeed(const unsigned int speed)
{
    _speed = speed;
}

void GUI::ECS::Demo::Bullet::setDirection(const std::pair<int, int> &direction)
{
    _direction = direction;
}

void GUI::ECS::Demo::Bullet::setSize(const std::pair<float, float> &dimension)
{
    _collision.setDimension(dimension);
    _sprite.setDimension(dimension);
}

void GUI::ECS::Demo::Bullet::setDamage(const int damage)
{
    _damage = damage;
}

void GUI::ECS::Demo::Bullet::tick()
{
    PRETTY_DEBUG << "In the bullet tick function" << std::endl;
    if (!_visible) {
        PRETTY_DEBUG << "The bullet isn't visible" << std::endl;
        return;
    }
    PRETTY_DEBUG << "Checking sprite tick" << std::endl;
    _sprite.checkTick();
    PRETTY_DEBUG << "Sprite has ticked: " << Recoded::myToString(_sprite.hasTicked()) << std::endl;
    PRETTY_DEBUG << "Calculating the new position" << std::endl;
    PRETTY_DEBUG << "Current collision: " << _collision.getPosition() << ", direction: " << _direction << ", speed :" << Recoded::myToString(_speed) << std::endl;
    const float offsetX = (_direction.first * static_cast<int>(_speed));
    const float offsetY = (_direction.second * static_cast<int>(_speed));
    PRETTY_DEBUG << "OffsetX = " << Recoded::myToString(offsetX) << ", offsetY = " << Recoded::myToString(offsetY) << std::endl;
    const float finalPositionX = _collision.getPositionX() + offsetX;
    const float finalPositionY = _collision.getPositionY() + offsetY;
    PRETTY_DEBUG << "finalPositionX = " << finalPositionX << ", finalPositionY = " << finalPositionY << std::endl;
    std::pair<float, float> opt = { finalPositionX,finalPositionY };
    PRETTY_DEBUG << "Bullet tick: initial position: " << getPosition() << ", updated position: " << opt << std::endl;
    setPosition(opt);
    PRETTY_DEBUG << "Position updated" << std::endl;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::Bullet::render()
{
    return _sprite;
};

const bool GUI::ECS::Demo::Bullet::isVisible() const
{
    return _visible;
}

const bool GUI::ECS::Demo::Bullet::isEnemy() const
{
    return _fromEnemy;
}

const std::pair<float, float> GUI::ECS::Demo::Bullet::getPosition() const
{
    return _collision.getPosition();
}


/*
If needed, check the opposite condition, as if<object> was the target and target the object
( = check isColliding as target with bullet as parameter)
*/
const bool GUI::ECS::Demo::Bullet::isColliding(const GUI::ECS::Systems::Collision &second) const
{
    return _collision.isColliding(second);
}

/**
 * @brief Updates the sprite by copying another Bullet.
 *
 * @param copy The Bullet to copy data from.
 */
void GUI::ECS::Demo::Bullet::update(const GUI::ECS::Demo::Bullet &copy)
{
    _speed = copy.getSpeed();
    _sprite = copy.getSprite();
    _damage = copy.getDamage();
    _visible = copy.isVisible();
    _fromEnemy = copy.isEnemy();
    _direction = copy.getDirection();
    _collision = copy.getCollision();
    _positionInitial = copy.getPositionInitial();
}

/**
 * @brief Overloads the assignment operator to copy from another Bullet.
 *
 * @param copy The Bullet to copy data from.
 *
 * @return A reference to the updated instance.
 */
GUI::ECS::Demo::Bullet &GUI::ECS::Demo::Bullet::operator =(const GUI::ECS::Demo::Bullet &copy)
{
    update(copy);
    return *this;
}

const unsigned int GUI::ECS::Demo::Bullet::getSpeed() const
{
    return _speed;
}

const GUI::ECS::Systems::Collision GUI::ECS::Demo::Bullet::getCollision() const
{
    return _collision;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Demo::Bullet::getSprite() const
{
    return _sprite;
}

const std::pair<int, int> GUI::ECS::Demo::Bullet::getPositionInitial() const
{
    return _positionInitial;
}

const int GUI::ECS::Demo::Bullet::getDamage() const
{
    return _damage;
}

const std::pair<int, int> GUI::ECS::Demo::Bullet::getDirection() const
{
    return _direction;
}

const std::string GUI::ECS::Demo::Bullet::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Bullet:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Damage: '" + Recoded::myToString(_damage) + "'\n";
    result += indentation + "- Visible: '" + Recoded::myToString(_visible) + "'\n";
    result += indentation + "- From Enemy: '" + Recoded::myToString(_fromEnemy) + "'\n";
    result += indentation + "- Speed: '" + Recoded::myToString(_speed) + "'\n";
    result += indentation + "- Direction: '" + Recoded::myToString(_direction) + "'\n";
    result += indentation + "- Position Initial: '" + Recoded::myToString(_positionInitial) + "'\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite: {\n" + _sprite.getInfo(indent + 1) + indentation + "}\n";

    return result;
}

void GUI::ECS::Demo::Bullet::_createBullet(const std::pair<int, int> &positionInitial)
{
    _sprite.setPosition(positionInitial);
    _collision.setPosition(positionInitial);
    _collision.setDimension(_sprite.getSpritesheet().getCollisionInfo().getDimension());
}

std::ostream &GUI::ECS::Demo::operator<<(std::ostream &os, const GUI::ECS::Demo::Bullet &item)
{
    os << item.getInfo();
    return os;
}
