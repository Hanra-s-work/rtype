#include "Registry.hpp"

template<typename Component>
using reference_type = typename ComponentContainer<Component>::reference_type;

template <typename... Components, typename Function>
void Registry::add_system(Function &&f)
{
    auto system = [f = std::forward<Function>(f), this]() {
        auto& component_arrays = get_component_arrays<Components...>();
        f(*this, std::get<0>(component_arrays), std::get<1>(component_arrays)...);
    };

    _systems.push_back(system);
}

void Registry::run_systems()
{
    for (auto& system : _systems) {
        system();
    }
}

template <class Component>
ComponentContainer<Component> &Registry::register_component()
{
    auto type_index = std::type_index(typeid(Component));

    auto erase_function = [this](Registry& registry, entity_t const& entity) {
        auto &container = registry.get_components<Component>();
        container.erase(entity);
    };

    _erase_functions[type_index].push_back(erase_function);

    auto &arr = _components[type_index];
    if (!arr) {
        arr = std::make_any<ComponentContainer<Component>>();
    }

    return std::any_cast<ComponentContainer<Component> &>(arr);
}

template <typename... Components>
std::tuple<ComponentContainer<Components> &...> Registry::get_component_array()
{
    return std::tie(get_components<Components>()...);
}

template <class Component>
ComponentContainer<Component> &Registry::get_components()
{
    return std::any_cast<ComponentContainer<Component>&>(_components[typeid(Component)]);
}

template <typename Component>
reference_type<Component> Registry::add_component(const Entity &entity, Component &&component)
{
    auto& array = get_components<Component>();
    return array.insert_at(entity.id(), std::forward<Component>(component));
}

template <typename Component, typename... Params>
reference_type<Component> Registry::emplace_component(const Entity &entity, Params &&...params)
{
    auto& array = get_components<Component>();
    return array.emplace_at(entity.id(), std::forward<Params>(params)...);
}

template <typename Component>
void Registry::remove_component(const Entity &entity)
{
    auto& array = get_components<Component>();
    array.erase(entity.id());
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
    std::remove(_entities.begin(), _entities.end(), entity), _entities.end();

    for (auto& [type, container] : _components) {
        _erase_functions[type](*this, entity);
    }
}