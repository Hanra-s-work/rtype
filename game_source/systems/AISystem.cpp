#include "AISystem.hpp"

#include "Registry.hpp"
#include "Behaviour.hpp"
#include "Velocity.hpp"
#include "Zipper.hpp"

void ai_system(Registry &r)
{
    float delta_time = 1;
    auto &behaviours = r.get_components<Behaviour>();
    auto &velocities = r.get_components<Velocity>();

    for (auto &&[beh, vel] : Zipper(behaviours, velocities)) {
        if (!beh || !vel) continue;

        switch (beh->type) {
            case behaviour_enum::DEFAULT:
                continue;
            case behaviour_enum::UP_DOWN:
                beh->timer += delta_time;
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
