#pragma once

#include <cstdint>
#include <atomic>

/// Basic 2D vector struct
struct Vector2 {
    float x;
    float y;
};

/* Distinguish specific entity types (player, monster, missile, etc.)*/
enum class EntityType : uint8_t {
    Player          = 1,
    Monster         = 2,
    PlayerMissile   = 3,
    MonsterMissile  = 4,
    Powerup         = 5,
    Boss            = 6,
};

class Entity {
public:
    Entity(EntityType type, uint32_t id);
    virtual ~Entity();

    /// Update the entity state each frame (e.g. movement)
    virtual void update(float dt) = 0;

    /// Simple collision check (e.g. bounding box or circle)
    virtual bool collidesWith(const Entity& other) const = 0;

    /// Called when a collision is detected
    virtual void onCollision(Entity& other) = 0;

    /// Mark entity for removal
    void destroy();
    bool isDestroyed() const;

    // Getters
    EntityType   getType() const;
    uint32_t     getId()   const;

    Vector2      getPosition() const;
    void         setPosition(const Vector2& pos);

    Vector2      getVelocity() const;
    void         setVelocity(const Vector2& vel);

protected:
    EntityType   _type;
    uint32_t     _id; // unique ID for networking sync

    Vector2      _position {0.f, 0.f};
    Vector2      _velocity {0.f, 0.f};
    bool         _destroyed {false};
};

uint32_t generateEntityId();
