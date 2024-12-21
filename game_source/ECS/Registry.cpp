#include "Registry.hpp"

Registry::Registry(EventDispatcher *_dispatcher)
{
    dispatcher = _dispatcher;
    setup_systems(*this);
    setup_components(*this);
}

void Registry::run_systems()
{
    for (auto& system : _systems) {
        system();
    }
}

Entity Registry::spawn_entity()
{
    size_t entity_id = _next_entity_id++;
    _entities.push_back(entity_id);
    return Entity(entity_id);
}

Entity Registry::entity_from_index(size_t idx) const
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
