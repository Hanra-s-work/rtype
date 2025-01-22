#include "Registry.hpp"

Registry::Registry(EventDispatcher *_dispatcher, Queue *_queue)
{
    dispatcher = _dispatcher;
    queue = _queue;
    setup_systems(*this);
    setup_components(*this);
}

void Registry::run_systems()
{
    for (auto& system : _systems) {
        system();
    }
}

std::vector<GameMessage> Registry::sync_game()
{
    return syncGameState(*this);
}

Entity Registry::spawn_entity()
{
    std::size_t entity_id = _next_entity_id++;
    _entities.push_back(entity_id);
    return Entity(entity_id);
}

Entity Registry::entity_from_index(std::size_t idx) const
{
    return Entity(idx);
}

void Registry::kill_entity(const Entity &entity)
{
    auto end = std::remove(_entities.begin(), _entities.end(), entity);

    for (auto& [type, container] : _components) {
        _erase_functions[type](entity);
    }
}
