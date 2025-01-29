#pragma once

#include <string>

struct Vector2 {
    float x;
    float y;
};

class Entity {
public:
    Entity() : _id(++s_nextId) {}
    virtual ~Entity() = default;

    virtual void update(double dt) = 0;

    virtual bool collidesWith(const Entity& other) const { return false; /* TODO */ }

    virtual void destroy() { _destroyed = true; }
    bool isDestroyed() const { return _destroyed; }

    int getId() const { return _id; }
    Vector2 getPosition() const { return _position; }
    void setPosition(const Vector2& pos) { _position = pos; }

protected:
    static int s_nextId;

    int _id;
    Vector2 _position {0.f, 0.f};
    Vector2 _velocity {0.f, 0.f};
    bool _destroyed  = false;
};
