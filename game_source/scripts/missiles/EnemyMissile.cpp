#include "EnemyMissile.hpp"
#include "Obstacle.hpp"
#include "DestroyableObstacle.hpp"
#include "Ally.hpp"
#include "Scene.hpp"

EnemyMissile::EnemyMissile(sf::Vector2<int> direction) : GameObject("", "enemyMissile") { OnCreate(); }

void EnemyMissile::OnCollision(GameObject *other)
{
    if (dynamic_cast<Obstacle*>(other)) {
        Scene::DestroyObject(*this);
    } else if (Ally *ally = dynamic_cast<Ally*>(other)) {
        ally->TakeDamage(1);
        Scene::DestroyObject(*this);
    } else if (dynamic_cast<DestroyableObstacle*>(other)) {
        Scene::DestroyObject(*this);
    } else {}
}