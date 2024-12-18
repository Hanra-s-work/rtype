#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <cassert>
#include <algorithm>

/**
 * @class DenseArray
 * @brief A container that provides dense storage for components with a mapping between entity IDs and component indices.
 * 
 * The `DenseArray` class is designed for efficient storage and retrieval of components in an ECS (Entity-Component-System)
 * architecture. It maintains a mapping between entity IDs and component indices to support fast lookups and iteration.
 * 
 * @tparam Component The type of the components stored in the array.
 * @tparam Allocator The allocator type used for memory management (defaults to `std::allocator<Component>`).
 */
template <typename Component, typename Allocator = std::allocator<Component>>
class DenseArray {
public:
    /// Type aliases for convenience
    using value_type = Component; /**< The type of component stored. */
    using optional_t = std::optional<Component>; /**< Optional type for components. */
    using reference_type = optional_t&; /**< Reference to a component. */
    using const_reference_type = const optional_t&; /**< Const reference to a component. */
    using id_type = size_t; /**< Type used for entity IDs. */
    using id_container_t = std::vector<id_type>; /**< Container type for storing entity IDs. */
    using component_container_t = std::vector<optional_t, Allocator>; /**< Container type for storing components. */
    using size_type = typename component_container_t::size_type; /**< Size type for the container. */
    using iterator = typename component_container_t::iterator; /**< Iterator type. */
    using const_iterator = typename component_container_t::const_iterator; /**< Const iterator type. */

    /**
     * @brief Default constructor.
     */
    DenseArray() = default;

    /**
     * @brief Copy constructor.
     * 
     * @param other The `DenseArray` to copy from.
     */
    DenseArray(const DenseArray& other) = default;

    /**
     * @brief Move constructor.
     * 
     * @param other The `DenseArray` to move from.
     */
    DenseArray(DenseArray&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~DenseArray() = default;

    /**
     * @brief Copy assignment operator.
     * 
     * @param other The `DenseArray` to copy from.
     * @return A reference to the current `DenseArray`.
     */
    DenseArray& operator=(const DenseArray& other) = default;

    /**
     * @brief Move assignment operator.
     * 
     * @param other The `DenseArray` to move from.
     * @return A reference to the current `DenseArray`.
     */
    DenseArray& operator=(DenseArray&& other) noexcept = default;

    /**
     * @brief Accesses the component at the given index.
     * 
     * @param idx The index to access.
     * @return A reference to the component at the specified index.
     */
    reference_type operator[](size_type idx) {
        assert(idx < _components.size() && "Index out of bounds");
        return _components[idx];
    }

    /**
     * @brief Accesses the component at the given index (const version).
     * 
     * @param idx The index to access.
     * @return A const reference to the component at the specified index.
     */
    const_reference_type operator[](size_type idx) const {
        return _components[idx];
    }

    /**
     * @brief Returns an iterator to the beginning of the component container.
     * 
     * @return An iterator to the first component.
     */
    iterator begin() {
        return _components.begin();
    }

    /**
     * @brief Returns a const iterator to the beginning of the component container.
     * 
     * @return A const iterator to the first component.
     */
    const_iterator begin() const {
        return _components.begin();
    }

    /**
     * @brief Returns a const iterator to the beginning of the component container.
     * 
     * @return A const iterator to the first component.
     */
    const_iterator cbegin() const {
        return _components.cbegin();
    }

    /**
     * @brief Returns an iterator to the end of the component container.
     * 
     * @return An iterator to one past the last component.
     */
    iterator end() {
        return _components.end();
    }

    /**
     * @brief Returns a const iterator to the end of the component container.
     * 
     * @return A const iterator to one past the last component.
     */
    const_iterator end() const {
        return _components.end();
    }

    /**
     * @brief Returns a const iterator to the end of the component container.
     * 
     * @return A const iterator to one past the last component.
     */
    const_iterator cend() const {
        return _components.cend();
    }

    /**
     * @brief Returns the number of components stored in the array.
     * 
     * @return The number of components.
     */
    size_type size() const {
        return _components.size();
    }

    /**
     * @brief Inserts a component at a specific ID.
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert.
     */
    void insert_at(size_type id, const Component& component) {
        ensure_size(id);
        _ids.push_back(id);
        _components.push_back(component);
    }

    /**
     * @brief Inserts a component at a specific ID (move version).
     * 
     * @param id The ID where the component should be inserted.
     * @param component The component to insert (moved).
     */
    void insert_at(size_type id, Component&& component) {
        ensure_size(id);
        _ids.push_back(id);
        _components[id] = std::move(component);
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
        ensure_size(id);
        _ids.push_back(id);
        _components.emplace_back(std::forward<Params>(params)...);
    }

    /**
     * @brief Removes the component at a specific ID.
     * 
     * @param id The ID of the component to erase.
     */
    void erase(size_type id) {
        _ids.erase(_ids.begin() + id);
        _components.erase(_components.begin() + id);
    }

private:
    /**
     * @brief Ensures the internal storage is large enough to accommodate a given position.
     * 
     * @param pos The position to accommodate.
     */
    void ensure_size(size_type pos) {
        if (pos >= _components.size()) {
            _ids.resize(pos + 1);
            _components.resize(pos + 1);
        }
    }

    id_container_t _ids; /**< Internal container for entity IDs. */
    component_container_t _components; /**< Internal container for components. */
    Allocator _allocator; /**< Allocator for managing memory. */
};
