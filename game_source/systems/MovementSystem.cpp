#include "MovementSystem.hpp"
#include "Zipper.hpp"
#include "../ECS/include/Time.hpp"

void move_player(Registry &r, size_t id, float x, float y)
{
    auto &position = r.get_components<Position>();

    position[id]->X = x;
    position[id]->Y = y;
}

void movement_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Velocity> &velocities)
{
    for (auto &&[pos, vel] : Zipper(positions, velocities)) {
        if (pos && vel) {
            pos->X += vel->vX * Time::deltaTime;
            pos->Y += vel->vY * Time::deltaTime;
        }
    }
}
