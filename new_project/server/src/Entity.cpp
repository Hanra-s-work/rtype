#include "Entity.hpp"

Entity::Entity(EntityTeam team, EntityType type, uint32_t id)
: _team(team)
, _type(type)
, _id(id)
{
}

Entity::~Entity() = default;

void Entity::destroy()
{
    _destroyed = true;
}

bool Entity::isDestroyed() const
{
    return _destroyed;
}

EntityTeam Entity::getTeam() const
{
    return _team;
}

EntityType Entity::getType() const
{
    return _type;
}

uint32_t Entity::getId() const
{
    return _id;
}

Vector2 Entity::getPosition() const
{
    return _position;
}

void Entity::setPosition(const Vector2& pos)
{
    _position = pos;
}

Vector2 Entity::getVelocity() const
{
    return _velocity;
}

void Entity::setVelocity(const Vector2& vel)
{
    _velocity = vel;
}
