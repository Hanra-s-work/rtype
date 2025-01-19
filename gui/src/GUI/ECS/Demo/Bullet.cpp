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
    _sprite.forceTick();
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
    PRETTY_DEBUG << "Bullet Position: X = " << _collision.getPositionX()
        << ", Y = " << _collision.getPositionY()
        << ", Width = " << _collision.getWidth()
        << ", Height = " << _collision.getHeight() << std::endl;

    PRETTY_DEBUG << "External entity Position: X = " << second.getPositionX()
        << ", Y = " << second.getPositionY()
        << ", Width = " << second.getWidth()
        << ", Height = " << second.getHeight() << std::endl;


    // Allow some tolerance to account for precision issues
    const float tolerance = 40.0f;

    // Calculate X overlap with a small tolerance
    const bool xOverlap = (std::abs(_collision.getPositionX() - second.getPositionX()) <= (tolerance + (_collision.getWidth() + second.getWidth())));

    // Calculate Y overlap with a small tolerance
    const bool yOverlap = (std::abs(_collision.getPositionY() - second.getPositionY()) <= (tolerance + (_collision.getHeight() + second.getHeight())));

    PRETTY_DEBUG << "X Overlap: " << Recoded::myToString(xOverlap) << ", Y Overlap: " << Recoded::myToString(yOverlap) << std::endl;
    // Return true if both X and Y overlaps are within the allowed range
    return xOverlap && yOverlap;

    // // Define a threshold for X-coordinate collision detection
    // const float xThreshold = 10.0f; // 10px tolerance for proximity

    // // Checking X-axis overlap with the threshold
    // const bool xOverlap = std::abs(second.getPositionX() - _collision.getPositionX()) <= xThreshold;

    // // Checking Y-axis overlap (no change)
    // const bool yOverlap = second.getPositionY() + second.getHeight() > _collision.getPositionY() &&
    //     second.getPositionY() < _collision.getPositionY() + _collision.getHeight();

    // // If both X and Y overlaps are true, a collision is detected
    // return xOverlap && yOverlap;
    // // Tolerance value to consider for the edge collision (10 pixels)
    // const float tolerance = 10.0f;

    // // Get the right edge of the bullet
    // const float bulletRight = _collision.getPositionX() + _collision.getWidth();
    // // Get the left edge of the enemy (second)
    // const float enemyLeft = second.getPositionX();

    // // Check if the right edge of the bullet is within the left edge of the enemy (+ tolerance)
    // const bool isCollidingRight = bulletRight >= enemyLeft - tolerance && bulletRight <= enemyLeft + tolerance;

    // // Get the left edge of the bullet
    // const float bulletLeft = _collision.getPositionX();
    // // Get the right edge of the enemy (second)
    // const float enemyRight = second.getPositionX() + second.getWidth();

    // // Check if the left edge of the bullet is within the right edge of the enemy (+ tolerance)
    // const bool isCollidingLeft = bulletLeft <= enemyRight + tolerance && bulletLeft >= enemyRight - tolerance;

    // // Get the bottom edge of the bullet
    // const float bulletBottom = _collision.getPositionY() + _collision.getHeight();
    // // Get the top edge of the enemy (second)
    // const float enemyTop = second.getPositionY();

    // // Check if the bottom edge of the bullet is within the top edge of the enemy (+ tolerance)
    // const bool isCollidingBottom = bulletBottom >= enemyTop - tolerance && bulletBottom <= enemyTop + tolerance;

    // // Get the top edge of the bullet
    // const float bulletTop = _collision.getPositionY();
    // // Get the bottom edge of the enemy (second)
    // const float enemyBottom = second.getPositionY() + second.getHeight();

    // // Check if the top edge of the bullet is within the bottom edge of the enemy (+ tolerance)
    // const bool isCollidingTop = bulletTop <= enemyBottom + tolerance && bulletTop >= enemyBottom - tolerance;

    // // Return true if any of the edges are within the tolerance range
    // return isCollidingRight || isCollidingLeft || isCollidingBottom || isCollidingTop;


    // // Set the tolerance value (±10 pixels)
    // const float tolerance = 10.0f;

    // // Check if the bullet is within ±10 pixels of the left edge of the enemy
    // const bool isCollidingRight = (_collision.getPositionX() + _collision.getWidth() > second.getPositionX() &&
    //     _collision.getPositionX() + _collision.getWidth() < second.getPositionX() + second.getWidth() + tolerance);

    // // Check if the bullet is within ±10 pixels of the right edge of the enemy
    // const bool isCollidingLeft = (_collision.getPositionX() < second.getPositionX() + second.getWidth() &&
    //     _collision.getPositionX() > second.getPositionX() - tolerance);

    // // Check if the bullet is within ±10 pixels of the top edge of the enemy
    // const bool isCollidingBottom = (_collision.getPositionY() + _collision.getHeight() > second.getPositionY() &&
    //     _collision.getPositionY() + _collision.getHeight() < second.getPositionY() + second.getHeight() + tolerance);

    // // Check if the bullet is within ±10 pixels of the bottom edge of the enemy
    // const bool isCollidingTop = (_collision.getPositionY() < second.getPositionY() + second.getHeight() &&
    //     _collision.getPositionY() > second.getPositionY() - tolerance);

    // // Return true if any of the opposing edges (right, left, top, or bottom) are within the tolerance range
    // return (isCollidingRight || isCollidingLeft || isCollidingBottom || isCollidingTop);


    // const bool isRightEdgeColliding = (_collision.getPositionX() + _collision.getWidth() > second.getPositionX() &&
    //     _collision.getPositionX() < second.getPositionX() + second.getWidth());
    // const bool isBottomEdgeColliding = (_collision.getPositionY() + _collision.getHeight() > second.getPositionY() &&
    //     _collision.getPositionY() < second.getPositionY() + second.getHeight());
    // return isRightEdgeColliding && isBottomEdgeColliding;

    // const bool isColliding = second.getPositionX() <= _collision.getPositionX() + _collision.getWidth() &&
    //     second.getPositionX() + second.getWidth() >= _collision.getPositionX() &&
    //     second.getPositionY() + second.getHeight() >= _collision.getPositionY() &&
    //     second.getPositionY() <= _collision.getPositionY() + _collision.getHeight();

    // return isColliding;

    // const float bulletLeft = _collision.getPositionX();
    // const float bulletRight = _collision.getPositionX() + _collision.getWidth();
    // const float bulletTop = _collision.getPositionY();
    // const float bulletBottom = _collision.getPositionY() + _collision.getHeight();
    // const float secondLeft = second.getPositionX();
    // const float secondRight = second.getPositionX() + second.getWidth();
    // const float secondTop = second.getPositionY();
    // const float secondBottom = second.getPositionY() + second.getHeight();
    // const bool xOverlap = bulletRight > secondLeft && bulletLeft < secondRight;
    // const bool yOverlap = bulletBottom > secondTop && bulletTop < secondBottom;
    // return xOverlap && yOverlap;
    // PRETTY_DEBUG << "Checking collision for the bullet brain" << std::endl;
    // PRETTY_DEBUG << "second: " << second << ", internal: " << _collision << std::endl;
    // const bool xOverlap = second.getPositionX() < _collision.getPositionX() + _collision.getWidth() &&
    //     second.getPositionX() + second.getWidth() > _collision.getPositionX();
    // const bool yOverlap = second.getPositionY() < _collision.getPositionY() + _collision.getHeight() &&
    //     second.getPositionY() + second.getHeight() > _collision.getPositionY();
    // PRETTY_DEBUG << "Checking overlap?, XOverlap: " << Recoded::myToString(xOverlap) << ", yOverlap: " << Recoded::myToString(yOverlap) << std::endl;
    // return xOverlap && yOverlap;
    // const bool xOverlap = second.getPositionX() + second.getWidth() > _collision.getPositionX() &&
    //     second.getPositionX() < _collision.getPositionX() + _collision.getWidth();

    // const bool yOverlap = second.getPositionY() + second.getHeight() > _collision.getPositionY() &&
    //     second.getPositionY() < _collision.getPositionY() + _collision.getHeight();

    // return xOverlap && yOverlap;
    // return second.getPositionX() + second.getWidth() > _collision.getPositionX() &&
    //     second.getPositionX() < _collision.getPositionX() + _collision.getWidth() &&
    //     second.getPositionY() + second.getHeight() > _collision.getPositionY() &&
    //     second.getPositionY() < _collision.getPositionY() + _collision.getHeight();
    // return _collision.isColliding(second);

    // return second.getPositionY() < _collision.getPositionY() + _collision.getHeight()
    //     && second.getPositionX() < _collision.getPositionX() + _collision.getWidth();
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
