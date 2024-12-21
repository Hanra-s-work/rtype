#include "LifetimeSystem.hpp"
#include "Registry.hpp"
#include "Lifetime.hpp"
#include "IndexedZipper.hpp"

#include "Time.hpp"

void lifetime_system(Registry &r)
{
    auto &lifetimes = r.get_components<Lifetime>();

    for (auto &&[idx, lif] : IndexedZipper(lifetimes)) {
        lif->time_left -= Time::deltaTime;
        if (lif->time_left <= 0.f)
            r.kill_entity(Entity(idx));
    }
}
