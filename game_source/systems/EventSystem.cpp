#include <sstream>
#include "EventSystem.hpp"
#include "SpawnSystem.hpp"

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
            std::cerr << "Invalid action received: " << event.id << std::endl;
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
    
    default:
        break;
    }
    return false;
}