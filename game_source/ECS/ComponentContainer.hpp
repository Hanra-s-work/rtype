#pragma once

#include <vector>
#include <optional>
#include <variant>
#include <memory>
#include <cassert>
#include <algorithm>

#include "DenseArray.hpp"
#include "SparseArray.hpp"

/**
 * @class ComponentContainer
 * @brief Manages a collection of components associated with entities in an ECS (Entity-Component-System) architecture.
 * 
 * The `ComponentContainer` class provides an interface for managing components, offering storage flexibility between sparse and dense arrays,
 * and supports efficient insertion, retrieval, and optimization.
 * 
 * @tparam Component The type of component stored.
 * @tparam Allocator The allocator type used for memory management (defaults to `std::allocator<Component>`).
 */
template <typename Component, typename Allocator = std::allocator<Component>>
class ComponentContainer {
public:
    /// Type aliases for convenience
    using value_type = Component; /**< The type of component stored. */
    using optional_t = std::optional<Component>; /**< Optional type for components. */
    using sparse_storage_t = SparseArray<Component, Allocator>; /**< Sparse storage type. */
    using dense_storage_t = DenseArray<Component, Allocator>; /**< Dense storage type. */
    using size_type = typename sparse_storage_t::size_type; /**< Size type. */

    using reference = std::optional<Component>&; /**< Reference to a component. */
    using const_reference = const std::optional<Component>&; /**< Const reference to a component. */
    using iterator = std::variant<typename sparse_storage_t::iterator, typename dense_storage_t::iterator>; /**< Iterator type. */
    using const_iterator = std::variant<typename sparse_storage_t::const_iterator, typename dense_storage_t::const_iterator>; /**< Const iterator type. */

    /**
     * @brief Default constructor.
     */
    ComponentContainer();

    /**
     * @brief Accesses the component at a given index.
     * 
     * @param idx The index of the component.
     * @return A reference to the component at the specified index.
     */
    reference operator[](size_t idx);

    /**
     * @brief Accesses the component at a given index (const version).
     * 
     * @param idx The index of the component.
     * @return A const reference to the component at the specified index.
     */
    const_reference operator[](size_t idx) const;

    /**
     * @brief Inserts a component at a specific ID.
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert.
     */
    void insert_at(size_type id, const Component& component);

    /**
     * @brief Inserts a component at a specific ID (move version).
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert (moved).
     */
    void insert_at(size_type id, Component&& component);

    /**
     * @brief Constructs and inserts a component at a specific ID.
     * 
     * @tparam Params The types of the parameters for the component constructor.
     * @param id The ID where the component should be inserted.
     * @param params The parameters for constructing the component.
     */
    template <typename... Params>
    void emplace_at(size_type id, Params&&... params);

    /**
     * @brief Retrieves a component by its value.
     * 
     * @param component The component value to search for.
     * @return An optional containing the component if found, or `std::nullopt` if not.
     */
    std::optional<Component> get(const value_type& component) const;

    /**
     * @brief Removes a component at a specific ID.
     * 
     * @param id The ID of the component to erase.
     */
    void erase(size_type id);

    /**
     * @brief Resizes the container to a new size.
     * 
     * @param new_size The new size of the container.
     */
    void resize(size_type new_size);

    /**
     * @brief Optimizes the storage type based on thresholds for sparse and dense storage.
     * 
     * @param sparse_threshold The threshold for switching to sparse storage.
     * @param dense_threshold The threshold for switching to dense storage.
     */
    void optimize_storage(size_type sparse_threshold, size_type dense_threshold);

private:
    /**
     * @brief A variant type holding either sparse or dense storage.
     */
    using ComponentStorage = std::variant<sparse_storage_t, dense_storage_t>;
    ComponentStorage _storage; /**< The internal storage of components. */

    /**
     * @brief Migrates storage from one container type to another.
     * 
     * @tparam NewContainer The new container type (sparse or dense).
     * @param new_storage The new storage container.
     */
    template <typename NewContainer>
    void migrate_storage(NewContainer& new_storage);
};
