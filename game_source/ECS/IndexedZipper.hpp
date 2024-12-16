#pragma once

#include "IndexedZipperIterator.hpp"

/**
 * @class IndexedZipper
 * @brief Combines multiple containers into a single iterable unit, iterating over corresponding elements from each container.
 * 
 * The `IndexedZipper` class allows simultaneous iteration over multiple containers. 
 * It provides an interface to iterate over a tuple of elements from the containers at the same index.
 * 
 * @tparam Containers Variadic template parameter for the types of containers to zip together.
 */
template <class... Containers>
class IndexedZipper {
public:
    /// Type alias for the iterator type.
    using iterator = IndexedZipperIterator<Containers...>; /**< Iterator for traversing the zipped containers. */
    /// Type alias for the tuple of iterators for the zipped containers.
    using iterator_tuple = typename iterator::iterator_tuple;

    /**
     * @brief Constructs an `IndexedZipper` with the given containers.
     * 
     * @param cs References to the containers to zip together.
     */
    IndexedZipper(Containers&... cs)
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
        return iterator(_end, _size);
    }

private:
    /**
     * @brief Computes the minimum size among the containers.
     * 
     * Ensures the zipper stops at the shortest container to avoid out-of-bounds access.
     * 
     * @param containers The containers to compute the size from.
     * @return The size of the smallest container.
     */
    static size_t _compute_size(Containers&... containers) {
        return std::min({containers.size()...});
    }

    /**
     * @brief Creates a tuple of iterators pointing to the beginning of each container.
     * 
     * @param containers The containers for which iterators are created.
     * @return A tuple of iterators to the beginning of each container.
     */
    static iterator_tuple create_iterators(Containers&... containers) {
        return std::make_tuple(std::begin(containers)...);
    }

    /**
     * @brief Creates a tuple of iterators pointing to the end of each container.
     * 
     * @param containers The containers for which end iterators are created.
     * @return A tuple of iterators to the end of each container.
     */
    static iterator_tuple create_end_iterators(Containers&... containers) {
        return std::make_tuple(std::end(containers)...);
    }

private:
    iterator_tuple _begin; /**< Tuple of iterators pointing to the beginning of the containers. */
    iterator_tuple _end; /**< Tuple of iterators pointing to the end of the containers. */
    size_t _size; /**< The minimum size of the containers being zipped. */
};
