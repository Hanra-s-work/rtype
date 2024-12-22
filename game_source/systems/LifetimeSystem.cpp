#include "LifetimeSystem.hpp"
#include "Registry.hpp"
#include "Lifetime.hpp"
#include "IndexedZipper.hpp"

void lifetime_system(Registry &r)
{
    auto &lifetimes = r.get_components<Lifetime>();

    float delta_time = 1;

    for (auto &&[idx, lif] : IndexedZipper(lifetimes)) {
        lif->time_left -= delta_time;
        if (lif->time_left <= 0.f)
            r.kill_entity(Entity(idx));
    }
}
