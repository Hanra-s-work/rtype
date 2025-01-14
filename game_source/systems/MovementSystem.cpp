#include "MovementSystem.hpp"
#include "IndexedZipper.hpp"
#include "Time.hpp"

void move_player(Registry &r, size_t id, float x, float y)
{
    auto &position = r.get_components<Position>();

    position[id]->X = x;
    position[id]->Y = y;

    r.dispatcher->notify({MOVE, id, {0, 0, 0, "", {x, y}}});
}

void movement_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Velocity> &velocities)
{
    for (auto &&[idx, pos, vel] : IndexedZipper(positions, velocities)) {
        if (pos && vel) {
            pos->X += vel->vX * Time::deltaTime;
            pos->Y += vel->vY * Time::deltaTime;
            r.dispatcher->notify({MOVE, idx, {0, 0, 0, "", {pos->X, pos->Y}}});
        }
    }
}
