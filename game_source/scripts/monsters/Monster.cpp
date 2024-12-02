#include "Monster.hpp"
#include "Scene.hpp"

Monster::Monster(const int initialHealth) : GameObject("", "monster"), health(initialHealth) { OnCreate(); }

void Monster::OnCreate()
{
    //nothing for now
}

void Monster::Update()
{
    //update position when receiving a server response
}

void Monster::Fire()
{
    //send request to fire... i think
}

void Monster::TakeDamage(int damage)
{
    health -= damage;

    if (health <= 0) {
        Scene::DestroyObject(*this);
    }
}
