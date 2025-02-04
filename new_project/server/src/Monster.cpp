#include "Monster.hpp"

static float degToRad(float deg) { return deg * 3.14159f / 180.f; }

Monster::Monster(uint32_t id, GameWorld& world)
: Entity(EntityType::Monster, id)
, _world(world)
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

        float angleDeg = static_cast<float>(std::rand() % 360);
        float angle = degToRad(angleDeg);
        float speed = 200.f;
        float vx = std::cos(angle) * speed;
        float vy = std::sin(angle) * speed;

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
    float distSq = dx*dx + dy*dy;
    float radius = 20.f;
    float otherRadius = 20.f; 
    float sumR = radius + otherRadius;
    return distSq <= (sumR * sumR);
}

void Monster::onCollision(Entity& other)
{
}