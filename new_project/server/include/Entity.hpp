//Entity.hpp
#pragma once

#include <cstdint>
#include <atomic>
#include "../../common/NetworkProtocol.hpp"

struct Vector2 {
    float x;
    float y;
};

class Entity {
public:
    Entity(EntityType type, uint32_t id);
    virtual ~Entity();

    virtual void update(float dt) = 0;

    virtual bool collidesWith(const Entity& other) const = 0;

    virtual void onCollision(Entity& other) = 0;

    void destroy();
    bool isDestroyed() const;

    EntityType   getType() const;
    uint32_t     getId()   const;

    Vector2      getPosition() const;
    void         setPosition(const Vector2& pos);

    Vector2      getVelocity() const;
    void         setVelocity(const Vector2& vel);
    EntityType   _type;

protected:
    uint32_t     _id;

    Vector2      _position {0.f, 0.f};
    Vector2      _velocity {0.f, 0.f};
    bool         _destroyed {false};
};

uint32_t generateEntityId();