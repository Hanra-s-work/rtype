#include "LifetimeSystem.hpp"
#include "IndexedZipper.hpp"

#include "Time.hpp"

void lifetime_system(Registry &r, ComponentContainer<Lifetime> &lifetimes)
{
    for (auto &&[idx, lif] : IndexedZipper(lifetimes)) {
        if (!lif) continue;
        lif->time_left -= Time::deltaTime;
        if (lif->time_left <= 0.f){
            r.kill_entity(Entity(idx));
            r.dispatcher->notify({messageType::P_KILL, idx, {0, 0, 0, "", {0, 0}}});
        }
    }
}
