#include <sstream>
#include "EventSystem.hpp"
#include "SpawnSystem.hpp"
#include "MovementSystem.hpp"
#include "WeaponSystem.hpp"
#include "PlayerMiscellaneous.hpp"

void event_system(Registry& r)
{
    while (true) {
        if (r.queue->isEmpty()) {
            break;
        }

        auto optionalEvent = r.queue->pop();
        if (!optionalEvent.has_value()) {
            continue;
        }

        const GameMessage& event = optionalEvent.value();

        if (validateAction(event, r)) {
            performAction(event, r);
        } else {
            std::cerr << "Invalid action received: " << event.type << std::endl;
        }
    }
}

bool validateAction(const GameMessage& event, Registry& r)
{
    return true;
}

bool performAction(const GameMessage& event, Registry& r)
{
    std::size_t id;
    switch (event.type)
    {
    case P_CONNECT:
        spawn_player(r, 120.f, 540.f, event.msg.cli_id, event.msg.username);
        break;
    case P_DISCONNECT:
        id = getIdByClientId(r, event.msg.cli_id);
        r.kill_entity(Entity(id));
        r.dispatcher->notify({P_KILL, id, { 0, 0, 0, "", {0, 0} }});
        break;
    case P_MOVE:
        move_player(r, event.id, event.msg.coords.x, event.msg.coords.y);
        break;
    case P_SHOOT:
        make_shot(r, event.id);
        break;
    default:
        return false;
    }
    return true;
}