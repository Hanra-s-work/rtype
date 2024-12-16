#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <cassert>

/**
 * @class SparseArray
 * @brief A container that provides sparse storage for optional components.
 * 
 * The `SparseArray` class is designed for efficient storage of components where not all indices are occupied,
 * allowing components to be stored sparsely with optional values.
 * 
 * @tparam Component The type of the components stored in the array.
 * @tparam Allocator The allocator type used for memory management (defaults to `std::allocator<Component>`).
 */
template <typename Component, typename Allocator = std::allocator<Component>>
class SparseArray {
public:
    /// Type aliases for convenience
    using value_type = std::optional<Component>; /**< The type of value stored, wrapped in an `std::optional`. */
    using reference_type = value_type&; /**< Reference type to a value in the array. */
    using const_reference_type = const value_type&; /**< Const reference type to a value in the array. */
    using container_t = std::vector<value_type, Allocator>; /**< Internal storage container type. */
    using size_type = typename container_t::size_type; /**< Size type for the container. */
    using iterator = typename container_t::iterator; /**< Iterator type. */
    using const_iterator = typename container_t::const_iterator; /**< Const iterator type. */

    /**
     * @brief Default constructor.
     */
    SparseArray() = default;

    /**
     * @brief Copy constructor.
     * 
     * @param other The `SparseArray` to copy from.
     */
    SparseArray(const SparseArray& other) = default;

    /**
     * @brief Move constructor.
     * 
     * @param other The `SparseArray` to move from.
     */
    SparseArray(SparseArray&& other) noexcept = default;

    /**
     * @brief Destructor.
     */
    ~SparseArray() = default;

    /**
     * @brief Copy assignment operator.
     * 
     * @param other The `SparseArray` to copy from.
     * @return A reference to the current `SparseArray`.
     */
    SparseArray& operator=(const SparseArray& other) = default;

    /**
     * @brief Move assignment operator.
     * 
     * @param other The `SparseArray` to move from.
     * @return A reference to the current `SparseArray`.
     */
    SparseArray& operator=(SparseArray&& other) noexcept = default;

    /**
     * @brief Accesses the value at the given index.
     * 
     * @param idx The index to access.
     * @return A reference to the optional value at the specified index.
     */
    reference_type operator[](size_t idx);

    /**
     * @brief Accesses the value at the given index (const version).
     * 
     * @param idx The index to access.
     * @return A const reference to the optional value at the specified index.
     */
    const_reference_type operator[](size_t idx) const;

    /**
     * @brief Returns an iterator to the beginning of the array.
     * 
     * @return An iterator to the first element.
     */
    iterator begin();

    /**
     * @brief Returns a const iterator to the beginning of the array.
     * 
     * @return A const iterator to the first element.
     */
    const_iterator begin() const;

    /**
     * @brief Returns a const iterator to the beginning of the array.
     * 
     * @return A const iterator to the first element.
     */
    const_iterator cbegin() const;

    /**
     * @brief Returns an iterator to the end of the array.
     * 
     * @return An iterator to one past the last element.
     */
    iterator end();

    /**
     * @brief Returns a const iterator to the end of the array.
     * 
     * @return A const iterator to one past the last element.
     */
    const_iterator end() const;

    /**
     * @brief Returns a const iterator to the end of the array.
     * 
     * @return A const iterator to one past the last element.
     */
    const_iterator cend() const;

    /**
     * @brief Returns the size of the array.
     * 
     * @return The number of elements in the array.
     */
    size_type size() const;

    /**
     * @brief Inserts a component at a specific position.
     * 
     * @param pos The position to insert the component at.
     * @param component The component to insert.
     * @return A reference to the inserted component.
     */
    reference_type insert_at(size_type pos, const Component& component);

    /**
     * @brief Inserts a component at a specific position (move version).
     * 
     * @param pos The position to insert the component at.
     * @param component The component to insert (moved).
     * @return A reference to the inserted component.
     */
    reference_type insert_at(size_type pos, Component&& component);

    /**
     * @brief Constructs and inserts a component at a specific position.
     * 
     * @tparam Params The types of the parameters for the component constructor.
     * @param pos The position to insert the component at.
     * @param params The parameters for constructing the component.
     * @return A reference to the inserted component.
     */
    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params);

    /**
     * @brief Removes the component at a specific position.
     * 
     * @param pos The position of the component to erase.
     */
    void erase(size_type pos);

private:
    /**
     * @brief Ensures the internal storage is large enough to accommodate a given position.
     * 
     * @param pos The position to accommodate.
     */
    void ensure_size(size_type pos);

    container_t _data; /**< Internal storage for components. */
    Allocator _allocator; /**< Allocator for managing memory. */
};
