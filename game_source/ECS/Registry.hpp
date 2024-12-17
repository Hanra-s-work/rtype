#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <functional>

#include "ComponentContainer.hpp"
#include "Entity.hpp"
#include "Systems.hpp"

/**
 * @class Registry
 * @brief Manages entities and their associated components, enabling the creation, deletion, and interaction of entities within a system.
 * 
 * The Registry class acts as the core of an ECS (Entity-Component-System) architecture, handling the registration of components,
 * the spawning and killing of entities, and the execution of systems.
 */
class Registry {
public:
    /**
     * @typedef reference
     * @brief A type alias for a reference to a component in a ComponentContainer.
     * 
     * @tparam Component The component type.
     */
    template<typename Component>
    using reference = typename ComponentContainer<Component>::reference;

    /**
     * @typedef eraseFunc
     * @brief A function type for erasing components associated with an entity.
     */
    using eraseFunc = std::function<void(Entity const&)>;

    /**
     * @brief Default constructor.
     */
    Registry();

    /**
     * @brief Adds a system to the registry.
     * 
     * A system is a function that operates on entities and their components.
     * 
     * @tparam Components The types of components required by the system.
     * @tparam Function The type of the system function.
     * @param f The system function to add.
     */
    template <typename... Components, typename Function>
    void add_system(Function&& f) {
        auto system = [f = std::forward<Function>(f), this]() {
        auto component_arrays = get_component_array<Components...>();
        std::apply([&](auto&&... args) {
            f(*this, std::forward<decltype(args)>(args)...);
        }, component_arrays);
        };

        _systems.push_back(system);
    }

    /**
     * @brief Executes all registered systems.
     */
    void run_systems();

    /**
     * @brief Registers a new component type.
     * 
     * @tparam Component The component type to register.
     * @return A reference to the component container for the given type.
     */
    template <class Component>
    ComponentContainer<Component>& register_component() {
        auto type_index = std::type_index(typeid(Component));

        auto erase_function = [&](Entity const& entity) {
            auto &container = this->get_components<Component>();
            container.erase(entity);
        };

        _erase_functions[type_index] = erase_function;

        auto &arr = _components[type_index];
        if (arr.has_value()) {
            arr = std::make_any<ComponentContainer<Component>>();
        }

        return std::any_cast<ComponentContainer<Component> &>(arr);
    }

    /**
     * @brief Retrieves component containers for multiple component types.
     * 
     * @tparam Components The component types.
     * @return A tuple containing references to the component containers.
     */
    template <typename... Components>
    std::tuple<ComponentContainer<Components>&...> get_component_array() {
        return std::tie(get_components<Components>()...);
    }

    /**
     * @brief Retrieves the component container for a specific type.
     * 
     * @tparam Component The component type.
     * @return A reference to the component container.
     */
    template <class Component>
    ComponentContainer<Component>& get_components() {
        return std::any_cast<ComponentContainer<Component>&>(_components[typeid(Component)]);
    }

    /**
     * @brief Adds a component to an entity.
     * 
     * @tparam Component The component type.
     * @param entity The entity to add the component to.
     * @param component The component to add.
     * @return A reference to the added component.
     */
    template <typename Component>
    reference<Component> add_component(const Entity& entity, Component&& component) {
        auto& array = get_components<Component>();
        array.insert_at(entity.getID(), std::forward<Component>(component));
        return array[entity];
    }

    /**
     * @brief Emplaces a component for an entity with constructor parameters.
     * 
     * @tparam Component The component type.
     * @tparam Params The parameter types for the component's constructor.
     * @param entity The entity to add the component to.
     * @param params The parameters for constructing the component.
     * @return A reference to the added component.
     */
    template <typename Component, typename... Params>
    reference<Component> emplace_component(const Entity& entity, Params&&... params) {
        auto& array = get_components<Component>();
        array.emplace_at(entity.getID(), std::forward<Params>(params)...);
        return array[entity];
    }

    /**
     * @brief Removes a component from an entity.
     * 
     * @tparam Component The component type.
     * @param entity The entity to remove the component from.
     */
    template <typename Component>
    void remove_component(const Entity& entity) {
        auto& array = get_components<Component>();
        array.erase(entity.getID());
    }

    /**
     * @brief Creates a new entity.
     * 
     * @return The newly created entity.
     */
    Entity spawn_entity();

    /**
     * @brief Retrieves an entity by its index.
     * 
     * @param idx The index of the entity.
     * @return The entity corresponding to the given index.
     */
    Entity entity_from_index(size_t idx) const;

    /**
     * @brief Deletes an entity and removes all its components.
     * 
     * @param entity The entity to delete.
     */
    void kill_entity(const Entity& entity);

private:
    std::unordered_map<std::type_index, std::any> _components; /**< Stores component containers indexed by type. */
    size_t _next_entity_id; /**< The ID for the next entity to be created. */
    std::vector<size_t> _entities; /**< A list of active entity IDs. */
    std::unordered_map<std::type_index, eraseFunc> _erase_functions; /**< Maps component types to their erase functions. */
    std::vector<std::function<void()>> _systems; /**< A list of system functions to execute. */
};
