#pragma once

#include <tuple>
#include <optional>
#include <type_traits>
#include <iterator>
#include <iostream>

template <class... Containers>
class IndexedZipperIterator {
    template <class Container>
    using iterator_t = typename Container::iterator;
    
    template <class Container>
    using it_reference_t = decltype(std::declval<Container>()[0]);

public:
    using value_type = std::tuple<size_t, it_reference_t<Containers>...>;
    using reference = value_type &;
    using pointer = void;
    using difference_type = size_t;
    using iterator_category = std::forward_iterator_tag;

    using iterator_tuple = std::tuple<size_t, it_reference_t<Containers>...>;

    IndexedZipperIterator(iterator_tuple current, size_t idx);
    IndexedZipperIterator(const IndexedZipperIterator &z);

    IndexedZipperIterator& operator++();
    IndexedZipperIterator operator++(int);
    value_type operator*();
    value_type* operator->();
    friend bool operator!=(const IndexedZipperIterator &lhs, const IndexedZipperIterator &rhs);
    friend bool operator==(const IndexedZipperIterator &lhs, const IndexedZipperIterator &rhs);
private:
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>);

    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>);

    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>);
private:
    iterator_tuple _current;
    size_t _max;
    size_t _idx;
    static constexpr std::index_sequence_for<Containers...> _seq{};
};