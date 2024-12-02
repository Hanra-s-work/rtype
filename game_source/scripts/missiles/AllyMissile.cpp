#include "AllyMissile.hpp"
#include "Obstacle.hpp"
#include "DestroyableObstacle.hpp"
#include "Monster.hpp"

void AllyMissile::OnCollision(GameObject *other) {
    if (DestroyableObstacle *destroyable = dynamic_cast<DestroyableObstacle*>(other)) {
        destroyable->TakeDamage(1);
        this->OnDestroy();
        delete this;
    } else if (Monster *monster = dynamic_cast<Monster*>(other)) {
        monster->TakeDamage(1);
        this->OnDestroy();
        delete this;
    } else if (dynamic_cast<Obstacle*>(other)) {
        this->OnDestroy();
        delete this;
    } else {}
}