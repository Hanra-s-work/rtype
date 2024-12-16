#pragma once

#include <tuple>
#include <optional>
#include <type_traits>
#include <iterator>
#include <iostream>

/**
 * @class IndexedZipperIterator
 * @brief Iterator for traversing the elements of multiple zipped containers, paired with their indices.
 * 
 * The `IndexedZipperIterator` class facilitates iterating over a collection of containers, 
 * returning a tuple of the current index and references to the elements of the containers.
 * 
 * @tparam Containers Variadic template parameter for the types of containers being iterated over.
 */
template <class... Containers>
class IndexedZipperIterator {
    /// Type alias for the iterator type of a single container.
    template <class Container>
    using iterator_t = typename Container::iterator;

    /// Type alias for the reference type of a single container's element.
    template <class Container>
    using it_reference_t = decltype(std::declval<Container>()[0]);

public:
    /// Type alias for the value type returned by the iterator.
    using value_type = std::tuple<size_t, it_reference_t<Containers>...>;
    using reference = value_type&; /**< Reference type for the value. */
    using pointer = void; /**< Pointer type (not applicable for this iterator). */
    using difference_type = size_t; /**< Difference type for iterator arithmetic. */
    using iterator_category = std::forward_iterator_tag; /**< Iterator category. */

    /// Type alias for the tuple of iterators for the containers being iterated.
    using iterator_tuple = std::tuple<size_t, it_reference_t<Containers>...>;

    /**
     * @brief Constructs an `IndexedZipperIterator` with the current iterator positions and index.
     * 
     * @param current Tuple of iterators for the containers.
     * @param idx Current index in the iteration.
     */
    IndexedZipperIterator(iterator_tuple current, size_t idx);

    /**
     * @brief Copy constructor.
     * 
     * @param z The `IndexedZipperIterator` to copy.
     */
    IndexedZipperIterator(const IndexedZipperIterator& z);

    /**
     * @brief Pre-increment operator.
     * 
     * Advances the iterator to the next element in the containers.
     * 
     * @return A reference to the incremented iterator.
     */
    IndexedZipperIterator& operator++();

    /**
     * @brief Post-increment operator.
     * 
     * Advances the iterator to the next element in the containers.
     * 
     * @return A copy of the iterator before incrementing.
     */
    IndexedZipperIterator operator++(int);

    /**
     * @brief Dereference operator.
     * 
     * Returns the current index and references to the elements of the containers.
     * 
     * @return A tuple of the current index and references to the container elements.
     */
    value_type operator*();

    /**
     * @brief Member access operator.
     * 
     * Provides a pointer-like interface to the iterator's value.
     * 
     * @return A pointer to the value tuple.
     */
    value_type* operator->();

    /**
     * @brief Inequality operator.
     * 
     * Compares two iterators for inequality.
     * 
     * @param lhs Left-hand side iterator.
     * @param rhs Right-hand side iterator.
     * @return `true` if the iterators are not equal; otherwise `false`.
     */
    friend bool operator!=(const IndexedZipperIterator& lhs, const IndexedZipperIterator& rhs);

    /**
     * @brief Equality operator.
     * 
     * Compares two iterators for equality.
     * 
     * @param lhs Left-hand side iterator.
     * @param rhs Right-hand side iterator.
     * @return `true` if the iterators are equal; otherwise `false`.
     */
    friend bool operator==(const IndexedZipperIterator& lhs, const IndexedZipperIterator& rhs);

private:
    /**
     * @brief Helper function to increment all iterators.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     */
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>);

    /**
     * @brief Helper function to check if all iterators have reached their end.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     * @return `true` if all iterators have reached their end; otherwise `false`.
     */
    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>);

    /**
     * @brief Helper function to construct the value tuple for the current iteration.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     * @return A tuple of the current index and references to the container elements.
     */
    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>);

private:
    iterator_tuple _current; /**< Current iterators for the containers. */
    size_t _max; /**< Maximum number of elements to iterate over. */
    size_t _idx; /**< Current index in the iteration. */
    static constexpr std::index_sequence_for<Containers...> _seq{}; /**< Index sequence for accessing tuple elements. */
};
