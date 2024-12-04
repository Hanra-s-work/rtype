#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <functional>

#include "ComponentContainer.hpp"
#include "Entity.hpp"

class Registry {
public:
    template<typename Component>
    using reference_type = typename ComponentContainer<Component>::reference_type;
    using eraseFunc = std::function<void(Registry&, Entity const&)>;

    Registry() = default;

    template <typename... Components, typename Function>
    void add_system(Function&& f);
    void run_systems();

    template <class Component>
    ComponentContainer<Component>& register_component();
    template <typename... Components>
    std::tuple<ComponentContainer<Components>&...> get_component_array();
    template <class Component>
    ComponentContainer<Component>& get_components();

    template <typename Component>
    reference_type<Component> add_component(const Entity& entity, Component&& component);
    template <typename Component, typename... Params>
    reference_type<Component> emplace_component(const Entity& entity, Params&&... params);
    template <typename Component>
    void remove_component(const Entity& entity);

    Entity spawn_entity();
    Entity entity_from_index(size_t idx) const;
    void kill_entity(const Entity& entity);
private:
    std::unordered_map<std::type_index, std::any> _components;
    size_t _next_entity_id;
    std::vector<size_t> _entities;
    std::unordered_map<std::type_index, eraseFunc> _erase_functions;
    std::vector<std::function<void()>> _systems;
};