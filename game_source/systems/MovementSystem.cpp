#include "MovementSystem.hpp"
#include "Zipper.hpp"
#include "Time.hpp"

void movement_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Velocity> &velocities)
{
    for (auto &&[pos, vel] : Zipper(positions, velocities)) {
        if (pos && vel) {
            std::cout << "My position is: (" << pos->X << ", " << pos->Y << ")" << std::endl;
            pos->X += vel->vX * Time::deltaTime;
            pos->Y += vel->vY * Time::deltaTime;
        }
    }
}
