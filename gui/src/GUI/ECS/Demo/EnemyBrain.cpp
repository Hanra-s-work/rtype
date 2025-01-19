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
    return second.getPositionY() < _collision.getPositionY() + _collision.getHeight()
        && second.getPositionX() < _collision.getPositionX() + _collision.getWidth();
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
