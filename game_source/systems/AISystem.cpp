#include "AISystem.hpp"

#include "../ECS/include/Time.hpp"
#include "Zipper.hpp"

void ai_system(Registry &r, ComponentContainer<Behaviour> &behaviours, ComponentContainer<Velocity> &velocities)
{
    for (auto &&[beh, vel] : Zipper(behaviours, velocities)) {
        if (!beh || !vel) continue;

        switch (beh->type) {
            case behaviour_enum::DEFAULT:
                continue;
            case behaviour_enum::UP_DOWN:
                beh->timer += Time::deltaTime;
                if (beh->timer >= AI_TIMER) {
                    vel->vY *= -1;
                    beh->timer = 0;
                }
                break;
            case behaviour_enum::FOLLOW:
                continue;
        }
    }
}
