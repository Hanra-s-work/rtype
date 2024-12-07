#include "MovementSystem.hpp"

void movement_system(Registry &r)
{
    auto &positions = r.get_components<Position>();
    auto &velocities = r.get_components<Velocity>();

    for (auto &&[pos, vel] : Zipper(positions, velocities)) {
        if (pos && vel) {
            pos->X += vel->vX;
            pos->Y += vel->vY;
        }
    }
}
