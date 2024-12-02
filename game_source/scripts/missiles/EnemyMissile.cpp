#include "EnemyMissile.hpp"
#include "Obstacle.hpp"
#include "DestroyableObstacle.hpp"
#include "Ally.hpp"

void EnemyMissile::OnCollision(GameObject *other)
{
    if (dynamic_cast<Obstacle*>(other)) {
        this->OnDestroy();
        delete this;
    } else if (Ally *ally = dynamic_cast<Ally*>(other)) {
        ally->TakeDamage(1);
        this->OnDestroy();
        delete this;
    } else if (dynamic_cast<DestroyableObstacle*>(other)) {
        this->OnDestroy();
        delete this;
    } else {}
}