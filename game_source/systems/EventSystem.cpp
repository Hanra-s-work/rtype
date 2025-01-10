#include <sstream>
#include "EventSystem.hpp"
#include "SpawnSystem.hpp"
#include "MovementSystem.hpp"

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
    switch (event.type)
    {
    case CONNECT:
        spawn_player(r, 120, 540, event.msg.username);
        break;
    case DISCONNECT:
        r.kill_entity(Entity(event.id));
        break;
    case MOVE:
        move_player(r, event.id, event.msg.coords.x, event.msg.coords.y);
        break;
    case SHOOT:
        spawn_missile(r, event.msg.coords.x, event.msg.coords.y, type_enum::PLAYER);
        break;
    default:
        return false;
    }
    return true;
}