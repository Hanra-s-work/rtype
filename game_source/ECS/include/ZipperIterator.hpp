#pragma once

#include <algorithm>
#include <tuple>
#include <optional>
#include <type_traits>
#include <iterator>
#include <iostream>

/**
 * @class ZipperIterator
 * @brief Iterator for traversing multiple zipped containers simultaneously.
 * 
 * The `ZipperIterator` class enables simultaneous iteration over multiple containers.
 * It returns a tuple containing references to the elements at the same position in the zipped containers.
 * 
 * @tparam Containers Variadic template parameter for the types of containers being iterated over.
 */
template <class... Containers>
class ZipperIterator {
    /// Type alias for the iterator type of a single container.
    template <class Container>
    using iterator_t = typename Container::iterator;

    /// Type alias for the reference type of a single container's element.
    template <class Container>
    using it_reference_t = decltype(std::declval<Container>()[0]);

public:
    /// Type alias for the value type returned by the iterator.
    using value_type = std::tuple<it_reference_t<Containers>...>;
    using reference = value_type&; /**< Reference type for the value. */
    using pointer = void; /**< Pointer type (not applicable for this iterator). */
    using difference_type = std::size_t; /**< Difference type for iterator arithmetic. */
    using iterator_category = std::input_iterator_tag; /**< Iterator category. */

    /// Type alias for the tuple of iterators used in the zipped containers.
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;

    /**
     * @brief Constructs a `ZipperIterator` with the provided iterator tuple and maximum iteration count.
     * 
     * @param it_tuple A tuple of iterators pointing to the current positions in the containers.
     * @param max The maximum number of elements to iterate over (determined by the smallest container size).
     */
    ZipperIterator(iterator_tuple const& it_tuple, std::size_t max, std::size_t idx = 0) : _current(it_tuple), _max(max), _idx(idx) {}

    /**
     * @brief Copy constructor.
     * 
     * @param z The `ZipperIterator` to copy.
     */
    ZipperIterator(const ZipperIterator& z) : _current(z._current), _max(z._max), _idx(z._idx) {}

    /**
     * @brief Pre-increment operator.
     * 
     * Advances the iterator to the next position in all containers.
     * 
     * @return A reference to the incremented iterator.
     */
    ZipperIterator& operator++() {
        incr_all(std::index_sequence_for<Containers...>{});
        return *this;
    }

    /**
     * @brief Post-increment operator.
     * 
     * Advances the iterator to the next position in all containers.
     * 
     * @return A copy of the iterator before incrementing.
     */
    ZipperIterator operator++(int) {
        ZipperIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    /**
     * @brief Dereference operator.
     * 
     * Returns a tuple containing references to the elements of the containers at the current position.
     * 
     * @return A tuple of references to the container elements at the current position.
     */
    value_type operator*() {
        return to_value(std::index_sequence_for<Containers...>{});
    }

    /**
     * @brief Member access operator.
     * 
     * Provides a pointer-like interface to the iterator's value.
     * 
     * @return A pointer to the value tuple.
     */
    value_type* operator->() {
        return &(*this);
    }

    /**
     * @brief Equality operator.
     * 
     * Compares two iterators for equality.
     * 
     * @param lhs Left-hand side iterator.
     * @param rhs Right-hand side iterator.
     * @return `true` if the iterators are equal; otherwise `false`.
     */
    friend bool operator==(const ZipperIterator<Containers...>& lhs, const ZipperIterator<Containers...>& rhs) {
        return lhs._idx == rhs._idx;
    }

    /**
     * @brief Inequality operator.
     * 
     * Compares two iterators for inequality.
     * 
     * @param lhs Left-hand side iterator.
     * @param rhs Right-hand side iterator.
     * @return `true` if the iterators are not equal; otherwise `false`.
     */
    friend bool operator!=(const ZipperIterator<Containers...>& lhs, const ZipperIterator<Containers...>& rhs) {
        return lhs._idx != rhs._idx;
    }

private:
    /**
     * @brief Helper function to increment all iterators in the tuple.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     */
    template <std::size_t... Is>
    void incr_all(std::index_sequence<Is...>) {
        (++std::get<Is>(_current), ...);
        ++_idx;

        while (_idx < _max && !all_set(std::index_sequence<Is...>{})) {
            (++std::get<Is>(_current), ...);
            ++_idx;
        }
    }

    /**
     * @brief Helper function to check if all iterators are valid.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     * @return `true` if all iterators are valid; otherwise `false`.
     */
    template <std::size_t... Is>
    bool all_set(std::index_sequence<Is...>) {
        return (... && std::get<Is>(_current)[0].has_value());
    }

    /**
     * @brief Helper function to construct the value tuple for the current iteration.
     * 
     * @tparam Is Index sequence for accessing the iterators in the tuple.
     * @return A tuple containing references to the container elements at the current position.
     */
    template <std::size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
        return std::tuple<it_reference_t<Containers>...>(*(std::get<Is>(_current))...);
    }

private:
    iterator_tuple _current; /**< Tuple of iterators pointing to the current positions in the containers. */
    std::size_t _max; /**< The maximum number of elements to iterate over (smallest container size). */
    std::size_t _idx; /**< Current index in the iteration. */
    static constexpr std::index_sequence_for<Containers...> _seq{}; /**< Index sequence for accessing tuple elements. */
};
