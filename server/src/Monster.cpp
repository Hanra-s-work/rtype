//Monster.cpp
#include "Monster.hpp"

static float degToRad(float deg)
{
    return deg * 3.14159f / 180.f;
}

Monster::Monster(uint32_t id, GameWorld& world): Entity(EntityType::Monster, id), _world(world), _shootTimer(0.f), _shootInterval(2.f)
{
}

Monster::~Monster() = default;

void Monster::update(float dt)
{
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    _shootTimer += dt;
    if (_shootTimer >= _shootInterval) {
        _shootTimer = 0.f;
        float bulletSpeed = 200.f;
        float vx = 0.f, vy = 0.f;
        if (_type == EntityType::Monster) {
            vx = -bulletSpeed;
            vy = 0.f;
        } else if (_type == EntityType::Monster2) {
            vx = -bulletSpeed;
            vy = 0.f;
        } else if (_type == EntityType::Monster3) {
            float angleDeg = (std::rand() % 2 == 0) ? 135.f : 225.f;
            float angle = angleDeg * 3.14159f / 180.f;
            vx = std::cos(angle) * bulletSpeed;
            vy = std::sin(angle) * bulletSpeed;
        } else if (_type == EntityType::Boss) {
            bulletSpeed = 300.f;
            int choice = std::rand() % 3;
            if (choice == 0) {
                vx = -bulletSpeed;
                vy = 0.f;
            } else if (choice == 1) {
                vx = -bulletSpeed;
                vy = -bulletSpeed * 0.5f;
            } else {
                vx = -bulletSpeed;
                vy = bulletSpeed * 0.5f;
            }
        }
        uint32_t bulletId = generateEntityId();
        auto bullet = std::make_unique<Missile>(bulletId, EntityType::MonsterMissile);
        bullet->setPosition(_position);
        bullet->setVelocity({vx, vy});
        _world.addEntity(std::move(bullet));
    }
}

bool Monster::collidesWith(const Entity& other) const
{
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx * dx + dy * dy;
    float radius = 20.f;
    if (_type == EntityType::Monster2)
        radius = 30.f;
    else if (_type == EntityType::Monster3)
        radius = 25.f;
    else if (_type == EntityType::Boss)
        radius = 60.f;
    float otherRadius = 20.f;
    return distSq <= (radius + otherRadius) * (radius + otherRadius);
}

void Monster::onCollision(Entity& other)
{
}