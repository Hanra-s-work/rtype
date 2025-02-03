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
    // Move monster
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    // Update shooting timer
    _shootTimer += dt;
    if (_shootTimer >= _shootInterval) {
        _shootTimer = 0.f;

        float angleDeg = static_cast<float>(std::rand() % 360);
        float angle = degToRad(angleDeg);
        float speed = 200.f; // bullet speed
        float vx = std::cos(angle) * speed;
        float vy = std::sin(angle) * speed;

        auto bullet = std::make_unique<Missile>(generateBulletId());
        bullet->setPosition(_position);

        bullet->setVelocity({vx, vy});
        // Possibly set bullet's team to Monsters

        _world.addEntity(std::move(bullet));
    }
}

bool Monster::collidesWith(const Entity& other) const
{
    // Similar bounding-circle approach as Player
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 20.f; // example monster radius
    float otherRadius = 20.f; 
    float sumR = radius + otherRadius;
    return distSq <= (sumR * sumR);
}

void Monster::onCollision(Entity& other)
{
    // If collided with a Player missile => destroy ourselves
    // If collided with a player => maybe deal damage, etc.
}
