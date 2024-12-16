#pragma once

#include "ZipperIterator.hpp"

/**
 * @class Zipper
 * @brief Combines multiple containers into a single iterable unit, iterating over corresponding elements from each container.
 * 
 * The `Zipper` class allows simultaneous iteration over multiple containers. 
 * It provides an interface to iterate over a tuple of elements from the containers at the same position.
 * 
 * @tparam Containers Variadic template parameter for the types of containers to zip together.
 */
template <class... Containers>
class Zipper {
public:
    /// Type alias for the iterator type used to traverse the zipped containers.
    using iterator = ZipperIterator<Containers...>;
    /// Type alias for the tuple of iterators used in the zipped containers.
    using iterator_tuple = typename iterator::iterator_tuple;

    /**
     * @brief Constructs a `Zipper` with the provided containers.
     * 
     * @param cs References to the containers to be zipped together.
     */
    Zipper(Containers&... cs);

    /**
     * @brief Returns an iterator to the beginning of the zipped containers.
     * 
     * @return An iterator pointing to the first tuple of elements from the zipped containers.
     */
    iterator begin();

    /**
     * @brief Returns an iterator to the end of the zipped containers.
     * 
     * @return An iterator pointing past the last tuple of elements from the zipped containers.
     */
    iterator end();

private:
    /**
     * @brief Computes the minimum size among the provided containers.
     * 
     * Ensures the iteration stops at the shortest container to prevent out-of-bounds access.
     * 
     * @param containers The containers to calculate the size from.
     * @return The size of the smallest container.
     */
    static size_t _compute_size(Containers&... containers);

    /**
     * @brief Creates a tuple of iterators pointing to the beginning of each container.
     * 
     * @param containers The containers for which iterators are created.
     * @return A tuple of iterators pointing to the beginning of each container.
     */
    static iterator_tuple create_iterators(Containers&... containers);

    /**
     * @brief Creates a tuple of iterators pointing to the end of each container.
     * 
     * @param containers The containers for which end iterators are created.
     * @return A tuple of iterators pointing to the end of each container.
     */
    static iterator_tuple create_end_iterators(Containers&... containers);

private:
    iterator_tuple _begin; /**< Tuple of iterators pointing to the beginning of the containers. */
    iterator_tuple _end; /**< Tuple of iterators pointing to the end of the containers. */
    size_t _size; /**< The minimum size of the containers being zipped. */
};
