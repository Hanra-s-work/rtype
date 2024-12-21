#include "AISystem.hpp"

#include "Time.hpp"
#include "Registry.hpp"
#include "Behaviour.hpp"
#include "Velocity.hpp"
#include "Zipper.hpp"

void ai_system(Registry &r)
{
    auto &behaviours = r.get_components<Behaviour>();
    auto &velocities = r.get_components<Velocity>();

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
