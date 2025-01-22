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
    using iterator_t = typename iterator::iterator_tuple;

    /**
     * @brief Constructs a `Zipper` with the provided containers.
     * 
     * @param cs References to the containers to be zipped together.
     */
    Zipper(Containers&... cs)
        : _begin(create_iterators(cs...)), _end(create_end_iterators(cs...)),
        _size(_compute_size(cs...)) {}

    /**
     * @brief Returns an iterator to the beginning of the zipped containers.
     * 
     * @return An iterator pointing to the first tuple of elements from the zipped containers.
     */
    iterator begin() {
        return iterator(_begin, _size);
    }

    /**
     * @brief Returns an iterator to the end of the zipped containers.
     * 
     * @return An iterator pointing past the last tuple of elements from the zipped containers.
     */
    iterator end() {
        return iterator(_end, _size, _size);
    }

private:
    /**
     * @brief Computes the minimum size among the provided containers.
     * 
     * Ensures the iteration stops at the shortest container to prevent out-of-bounds access.
     * 
     * @param containers The containers to calculate the size from.
     * @return The size of the smallest container.
     */
    static std::size_t _compute_size(Containers&... containers) {
        return std::min({containers.size()...});
    }

    /**
     * @brief Creates a tuple of iterators pointing to the beginning of each container.
     * 
     * @param containers The containers for which iterators are created.
     * @return A tuple of iterators pointing to the beginning of each container.
     */
    static iterator_t create_iterators(Containers&... containers) {
        return iterator_t(containers.begin()...);
    }

    /**
     * @brief Creates a tuple of iterators pointing to the end of each container.
     * 
     * @param containers The containers for which end iterators are created.
     * @return A tuple of iterators pointing to the end of each container.
     */
    static iterator_t create_end_iterators(Containers&... containers) {
        return iterator_t(containers.end()...);
    }

private:
    iterator_t _begin; /**< Tuple of iterators pointing to the beginning of the containers. */
    iterator_t _end; /**< Tuple of iterators pointing to the end of the containers. */
    std::size_t _size; /**< The minimum size of the containers being zipped. */
};
