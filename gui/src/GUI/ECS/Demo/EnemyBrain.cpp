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

GUI::ECS::Demo::EnemyBrain::EnemyBrain(const std::uint32_t entityId)
    : EntityNode(entityId)
{

};

GUI::ECS::Demo::EnemyBrain::EnemyBrain(const GUI::ECS::Demo::EnemyBrain &copy)
{
    update(copy);
}

GUI::ECS::Demo::EnemyBrain::EnemyBrain(const std::uint32_t entityId, const GUI::ECS::Demo::EnemyBrain &copy)
    : EntityNode(entityId)
{
    update(copy);
}

void GUI::ECS::Demo::EnemyBrain::setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet)
{
    PRETTY_DEBUG << "Setting the sprite content" << std::endl;
    _sprite = *sprite;
    PRETTY_DEBUG << "The sprite entity is set" << std::endl;
    _bullet.setSprite(*bullet);
    PRETTY_DEBUG << "The bullet entity is set" << std::endl;
    _bullet.setVisible(true);
    _bullet.setEnemy(true);
    _bullet.setDamage(5);
    _bullet.setSpeed(5);
    _bullet.setPosition({ 1,1 });
    _bullet.setDirection({ -1,0 });
    _bullet.setSize({ 0.5, 0.5 });
    _bullet.tick();
    PRETTY_DEBUG << "Bullet info has been set" << std::endl;
    _collision.update(_sprite.getCollision());
    _collision.setPosition(_bullet.getPosition());
    PRETTY_DEBUG << "Sprite info: " << _sprite << std::endl;
    PRETTY_DEBUG << "Bullet info: " << *bullet << std::endl;
    PRETTY_DEBUG << "Collision info: " << _collision << std::endl;
};

void GUI::ECS::Demo::EnemyBrain::setPosition(const std::pair<float, float> &pos)
{
    PRETTY_DEBUG << "In setPosition" << std::endl;
    _collision.setPosition(pos);
    _sprite.setPosition(pos);
    _bullet.setPosition(pos);
    PRETTY_DEBUG << "collision: " << _collision << "sprite: " << _sprite << "bullet:" << _bullet << std::endl;
};

void GUI::ECS::Demo::EnemyBrain::setDimension(const std::pair<float, float> &dim)
{
    _collision.setDimension(dim);
    _sprite.setDimension(dim);
};

void GUI::ECS::Demo::EnemyBrain::setHealth(const long int health)
{
    _health = health;
    if (health <= 0) {
        _health = 0;
    }
}

void GUI::ECS::Demo::EnemyBrain::setVisible(const bool visible)
{
    _visible = visible;
    _sprite.setVisible(visible);
};

void GUI::ECS::Demo::EnemyBrain::setBulletSize(const std::pair<float, float> &size)
{
    _bullet.setSize(size);
}

const bool GUI::ECS::Demo::EnemyBrain::isColliding(const GUI::ECS::Systems::Collision &second) const
{
    PRETTY_DEBUG << "Enemy Position: X = " << _collision.getPositionX()
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
    // PRETTY_DEBUG << "Checking collision for the enemy brain" << std::endl;
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
};

const bool GUI::ECS::Demo::EnemyBrain::isVisible() const
{
    return _visible;
};

const std::optional<GUI::ECS::Demo::Bullet> GUI::ECS::Demo::EnemyBrain::tick()
{
    PRETTY_DEBUG << "In enemy brain tick" << std::endl;
    _sprite.checkTick();
    if (_delayBeforeShot == 0) {
        _delayBeforeShot = _randInt(20, 80);
        GUI::ECS::Demo::Bullet shot(_bullet);
        shot.tick();
        shot.setDamage(_randInt(1, 20));
        shot.setPosition(_collision.getPosition());
        PRETTY_DEBUG << "User Position: " << _collision << std::endl;
        PRETTY_DEBUG << "bullet: " << _bullet << ", shot: " << shot << std::endl;
        PRETTY_DEBUG << "Shot has been sent" << std::endl;
        return std::optional(shot);
    }
    _delayBeforeShot--;
    PRETTY_DEBUG << "No shot has been sent" << std::endl;
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

const long int GUI::ECS::Demo::EnemyBrain::getHealth() const
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


const std::string GUI::ECS::Demo::EnemyBrain::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Enemy brain:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: '" + Recoded::myToString(_visible) + "'\n";
    result += indentation + "- Health: '" + Recoded::myToString(_health) + "'\n";
    result += indentation + "- Delay before shot: '" + Recoded::myToString(_delayBeforeShot) + "'\n";
    result += indentation + "- Bullet: {\n" + _bullet.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite: {\n" + _sprite.getInfo(indent + 1) + indentation + "}\n";

    return result;
}

std::ostream &GUI::ECS::Demo::operator<<(std::ostream &os, const GUI::ECS::Demo::EnemyBrain &item)
{
    os << item.getInfo();
    return os;
}
