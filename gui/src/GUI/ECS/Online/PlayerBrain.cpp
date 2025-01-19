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

#include "GUI/ECS/Online/PlayerBrain.hpp"

GUI::ECS::Online::PlayerBrain::PlayerBrain(const std::uint32_t entityId)
    : EntityNode(entityId)
{

};

GUI::ECS::Online::PlayerBrain::PlayerBrain(const GUI::ECS::Online::PlayerBrain &copy)
{
    update(copy);
}

GUI::ECS::Online::PlayerBrain::PlayerBrain(const std::uint32_t entityId, const GUI::ECS::Online::PlayerBrain &copy)
    : EntityNode(entityId)
{
    update(copy);
}


void GUI::ECS::Online::PlayerBrain::setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet)
{
    PRETTY_DEBUG << "Setting the sprite content" << std::endl;
    _sprite = *sprite;
    PRETTY_DEBUG << "The sprite entity is set" << std::endl;
    _bullet.setSprite(*bullet);
    PRETTY_DEBUG << "The bullet entity is set" << std::endl;
    _bullet.setVisible(true);
    _bullet.setEnemy(false);
    _bullet.setDamage(5);
    _bullet.setSpeed(5);
    _bullet.setPosition({ 1,1 });
    _bullet.setDirection({ 1,0 });
    _bullet.setSize({ 0.5, 0.5 });
    _bullet.tick();
    PRETTY_DEBUG << "Bullet info has been set" << std::endl;
    _collision.update(_sprite.getCollision());
    _collision.setPosition(_bullet.getPosition());
    PRETTY_DEBUG << "Sprite info: " << _sprite << std::endl;
    PRETTY_DEBUG << "Bullet info: " << *bullet << std::endl;
    PRETTY_DEBUG << "Collision info: " << _collision << std::endl;
};

void GUI::ECS::Online::PlayerBrain::setPosition(const std::pair<float, float> &pos)
{
    PRETTY_DEBUG << "In setPosition" << std::endl;
    _collision.setPosition(pos);
    _sprite.setPosition(pos);
    _bullet.setPosition(pos);
    PRETTY_DEBUG << "collision: " << _collision << "sprite: " << _sprite << "bullet:" << _bullet << std::endl;
};

void GUI::ECS::Online::PlayerBrain::setDimension(const std::pair<float, float> &dim)
{
    _collision.setDimension(dim);
    _sprite.setDimension(dim);
};

void GUI::ECS::Online::PlayerBrain::setHealth(const long int health)
{
    _health = health;
    if (health <= 0) {
        _health = 0;
    }
}

void GUI::ECS::Online::PlayerBrain::setVisible(const bool visible)
{
    _visible = visible;
    _sprite.setVisible(visible);
};

void GUI::ECS::Online::PlayerBrain::setBulletSize(const std::pair<float, float> &size)
{
    _bullet.setSize(size);
}

const bool GUI::ECS::Online::PlayerBrain::isColliding(const GUI::ECS::Systems::Collision &second) const
{
    PRETTY_DEBUG << "Enemy Position: X = " << _collision.getPositionX()
        << ", Y = " << _collision.getPositionY()
        << ", Width = " << _collision.getWidth()
        << ", Height = " << _collision.getHeight() << std::endl;

    PRETTY_DEBUG << "External entity Position: X = " << second.getPositionX()
        << ", Y = " << second.getPositionY()
        << ", Width = " << second.getWidth()
        << ", Height = " << second.getHeight() << std::endl;


    PRETTY_DEBUG << "Setting the tolerance for the collision" << std::endl;
    const float tolerance = 30.0f;
    PRETTY_DEBUG << "The tolerance is set to: " << Recoded::myToString(tolerance) << std::endl;

    PRETTY_DEBUG << "Calculating the overlap of X" << std::endl;
    const bool xOverlap = (std::abs(_collision.getPositionX() - second.getPositionX()) <= (tolerance + (_collision.getWidth() + second.getWidth())));
    PRETTY_DEBUG << "The X overlap was calculated at: " << Recoded::myToString(xOverlap) << std::endl;

    PRETTY_DEBUG << "Calculating the overlap of Y" << std::endl;
    const bool yOverlap = (std::abs(_collision.getPositionY() - second.getPositionY()) <= (tolerance + (_collision.getHeight() + second.getHeight())));
    PRETTY_DEBUG << "The Y overlap was calculated at: " << Recoded::myToString(yOverlap) << std::endl;

    PRETTY_DEBUG << "X Overlap: " << Recoded::myToString(xOverlap) << ", Y Overlap: " << Recoded::myToString(yOverlap) << std::endl;
    PRETTY_DEBUG << "Checking if x and y are overlapping" << std::endl;
    const bool overlapping = xOverlap && yOverlap;
    PRETTY_DEBUG << "The result of if x and y are overlapping is: " << Recoded::myToString(overlapping) << std::endl;
    return overlapping;
};

const bool GUI::ECS::Online::PlayerBrain::isVisible() const
{
    return _visible;
};


void GUI::ECS::Online::PlayerBrain::tick()
{
    _sprite.checkTick();
    _bullet.tick();
};

const GUI::ECS::Online::Bullet GUI::ECS::Online::PlayerBrain::shoot(const std::uint32_t id) const
{
    GUI::ECS::Online::Bullet shot(id, _bullet);
    shot.setPosition(_collision.getPosition());
    shot.setSize({ 0.5,0.5 });
    shot.tick();
    PRETTY_DEBUG << "User Position: " << _collision << std::endl;
    PRETTY_DEBUG << "bullet: " << _bullet << ", shot: " << shot << std::endl;
    return shot;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Online::PlayerBrain::render()
{
    return _sprite;
};

/**
 * @brief Updates the sprite by copying another PlayerBrain.
 *
 * @param copy The PlayerBrain to copy data from.
 */
void GUI::ECS::Online::PlayerBrain::update(const GUI::ECS::Online::PlayerBrain &copy)
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
GUI::ECS::Online::PlayerBrain &GUI::ECS::Online::PlayerBrain::operator =(const GUI::ECS::Online::PlayerBrain &copy)
{
    update(copy);
    return *this;
}

const bool GUI::ECS::Online::PlayerBrain::getVisible() const
{
    return _visible;
}

const long int GUI::ECS::Online::PlayerBrain::getHealth() const
{
    return _health;
}

const GUI::ECS::Online::Bullet GUI::ECS::Online::PlayerBrain::getBullet() const
{
    return _bullet;
}

const GUI::ECS::Components::SpriteComponent GUI::ECS::Online::PlayerBrain::getSprite() const
{
    return _sprite;
}

const GUI::ECS::Systems::Collision GUI::ECS::Online::PlayerBrain::getCollision() const
{
    return _collision;
}

const std::string GUI::ECS::Online::PlayerBrain::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Player brain:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: '" + Recoded::myToString(_visible) + "'\n";
    result += indentation + "- Health: '" + Recoded::myToString(_health) + "'\n";
    result += indentation + "- Bullet: {\n" + _bullet.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Sprite: {\n" + _sprite.getInfo(indent + 1) + indentation + "}\n";

    return result;
}

std::ostream &GUI::ECS::Online::operator<<(std::ostream &os, const GUI::ECS::Online::PlayerBrain &item)
{
    os << item.getInfo();
    return os;
}
