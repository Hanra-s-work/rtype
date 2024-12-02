#include "AllyMissile.hpp"
#include "Obstacle.hpp"
#include "DestroyableObstacle.hpp"
#include "Monster.hpp"
#include "Scene.hpp"

void AllyMissile::OnCollision(GameObject *other) {
    if (DestroyableObstacle *destroyable = dynamic_cast<DestroyableObstacle*>(other)) {
        destroyable->TakeDamage(1);
        Scene::DestroyObject(*this);
    } else if (Monster *monster = dynamic_cast<Monster*>(other)) {
        monster->TakeDamage(1);
        Scene::DestroyObject(*this);
    } else if (dynamic_cast<Obstacle*>(other)) {
        Scene::DestroyObject(*this);
    } else {}
}