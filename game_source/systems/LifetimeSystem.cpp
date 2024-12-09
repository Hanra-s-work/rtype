#include "LifetimeSystem.hpp"

void lifetime_system(Registry &r, float delta_time)
{
    auto &lifetimes = r.get_components<Lifetime>();

    for (auto &&[idx, lif] : IndexedZipper(lifetimes)) {
        lif->time_left -= delta_time;
        if (lif->time_left <= 0.f)
            r.kill_entity(Entity(idx));
    }
}
