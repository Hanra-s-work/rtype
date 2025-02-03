#include "Entity.hpp"

Entity::Entity(EntityType type, uint32_t id)
: _type(type)
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

uint32_t generateEntityId()
{
    // Start from 10,000 so it doesn't clash with players that start from 1
    static std::atomic<uint32_t> nextEntity_Id{10000};
    return nextEntity_Id.fetch_add(1, std::memory_order_relaxed);
}