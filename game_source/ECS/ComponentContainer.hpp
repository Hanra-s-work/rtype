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

    using reference = optional_t&; /**< Reference to a component. */
    using const_reference = const optional_t&; /**< Const reference to a component. */
    using iterator = typename std::vector<optional_t, Allocator>::iterator; /**< Iterator type. */
    using const_iterator = typename std::vector<optional_t, Allocator>::const_iterator; /**< Const iterator type. */

    /**
     * @brief Default constructor.
     */
    ComponentContainer() : _storage(sparse_storage_t()) {}

    /**
     * @brief Accesses the component at a given index.
     * 
     * @param idx The index of the component.
     * @return A reference to the component at the specified index.
     */
    reference operator[](size_t idx) {
        return std::visit([&](auto& storage) -> reference { return storage[idx]; }, _storage);
    }

    /**
     * @brief Accesses the component at a given index (const version).
     * 
     * @param idx The index of the component.
     * @return A const reference to the component at the specified index.
     */
    const_reference operator[](size_t idx) const {
        return std::visit([&](auto const& storage) -> const_reference { return storage[idx]; }, _storage);
    }

    /**
     * @brief Returns an iterator to the beginning of the component container.
     * 
     * @return An iterator to the first component.
     */
    iterator begin() {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.begin();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.begin();
        }
    }

    /**
     * @brief Returns a const iterator to the beginning of the component container.
     * 
     * @return A const iterator to the first component.
     */
    const_iterator begin() const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.begin();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.begin();
        }
    }

    /**
     * @brief Returns a const iterator to the beginning of the component container.
     * 
     * @return A const iterator to the first component.
     */
    const_iterator cbegin() const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.cbegin();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.cbegin();
        }
    }

    /**
     * @brief Returns an iterator to the end of the component container.
     * 
     * @return An iterator to one past the last component.
     */
    iterator end() {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.end();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.end();
        }
    }

    /**
     * @brief Returns a const iterator to the end of the component container.
     * 
     * @return A const iterator to one past the last component.
     */
    const_iterator end() const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.end();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.end();
        }
    }

    /**
     * @brief Returns a const iterator to the end of the component container.
     * 
     * @return A const iterator to one past the last component.
     */
    const_iterator cend() const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.cend();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.cend();
        }
    }

    /**
     * @brief Returns the number of components stored in the array.
     * 
     * @return The number of components.
     */
    size_type size() const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            return sparse.size();
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            return dense.size();
        }
    }

    /**
     * @brief Inserts a component at a specific ID.
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert.
     */
    void insert_at(size_type id, const Component& component) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            sparse[id] = component;
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            dense.insert_at(id, component);
        }
    }

    /**
     * @brief Inserts a component at a specific ID (move version).
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert (moved).
     */
    void insert_at(size_type id, Component&& component) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            sparse[id] = std::forward<Component>(component);
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            dense.insert_at(id, std::forward<Component>(component));
        }
    }

    /**
     * @brief Constructs and inserts a component at a specific ID.
     * 
     * @tparam Params The types of the parameters for the component constructor.
     * @param id The ID where the component should be inserted.
     * @param params The parameters for constructing the component.
     */
    template <typename... Params>
    void emplace_at(size_type id, Params&&... params) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            if (id >= sparse.size()) {
                sparse.resize(id + 1);
            }

            sparse[id].emplace(std::forward<Params>(params)...);
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            
            dense.emplace_at(id, std::forward<Params>(params)...);
        }
    }

    /**
     * @brief Retrieves a component by its id.
     * 
     * @param id The id value to search for.
     * @return An optional containing the component if found, or `std::nullopt` if not.
     */
    std::optional<Component> get(const value_type& id) const {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            const auto& sparse = std::get<sparse_storage_t>(_storage);
            if (id < sparse.size()) {
                return sparse[id];
            }
        } else {
            const auto& dense = std::get<dense_storage_t>(_storage);
             if (id < dense.size()) {
                return dense[id];
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Removes a component at a specific ID.
     * 
     * @param id The ID of the component to erase.
     */
    void erase(size_type id) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            if (id < sparse.size()) {
                sparse[id].reset();
            }
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            if (id < dense.size()) {
                dense.erase(id);
            }
        }
    }

    /**
     * @brief Resizes the container to a new size.
     * 
     * @param new_size The new size of the container.
     */
    void resize(size_type new_size) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            sparse.resize(new_size);
        }
    }

    /**
     * @brief Optimizes the storage type based on thresholds for sparse and dense storage.
     * 
     * @param sparse_threshold The threshold for switching to sparse storage.
     * @param dense_threshold The threshold for switching to dense storage.
     */
    void optimize_storage(size_type sparse_threshold, size_type dense_threshold) {
        if (std::holds_alternative<sparse_storage_t>(_storage)) {
            auto& sparse = std::get<sparse_storage_t>(_storage);
            size_type filled = std::count_if(sparse.begin(), sparse.end(), [](const auto& opt) { return opt.has_value(); });
            if (filled >= dense_threshold) {
                dense_storage_t dense;
                migrate_storage(dense);
                _storage = std::move(dense);
            }
        } else {
            auto& dense = std::get<dense_storage_t>(_storage);
            if (dense.size() <= sparse_threshold) {
                sparse_storage_t sparse;
                migrate_storage(sparse);
                _storage = std::move(sparse);
            }
        }
    }

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
    void migrate_storage(NewContainer& new_storage) {
         if (std::holds_alternative<sparse_storage_t>(_storage)) {
            const auto& sparse = std::get<sparse_storage_t>(_storage);
            for (size_type i = 0; i < sparse.size(); ++i) {
                if (sparse[i]) {
                    new_storage.insert_at(i, *sparse[i]);
                }
            }
        } else {
            const auto& dense = std::get<dense_storage_t>(_storage);
            size_type max_id = *std::max_element(dense.begin(), dense.end());
            new_storage.resize(max_id + 1);
            for (size_type i = 0; i < dense.size(); ++i) {
                new_storage[i] = dense[i];
            }
        }
    }
};
