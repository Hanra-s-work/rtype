#pragma once

#include <tuple>
#include <optional>
#include <type_traits>
#include <iterator>
#include <iostream>

template <class... Containers>
class ZipperIterator {
    template <class Container>
    using iterator_t = typename Container::iterator;

    template <class Container>
    using it_reference_t = decltype(std::declval<Container>()[0]);

public:
    using value_type = std::tuple<it_reference_t<Containers>...>;
    using reference = value_type &;
    using pointer = void;
    using difference_type = size_t;
    using iterator_category = std::input_iterator_tag;

    using iterator_tuple = std::tuple<iterator_t<Containers>...>;

    friend class Zipper<Containers...>;

    ZipperIterator(iterator_tuple const &it_tuple, size_t max);
    ZipperIterator(const ZipperIterator &z);

    ZipperIterator& operator++();
    ZipperIterator operator++(int);
    value_type operator*();
    value_type* operator->();
    friend bool operator==(const ZipperIterator &lhs, const ZipperIterator &rhs);
    friend bool operator!=(const ZipperIterator &lhs, const ZipperIterator &rhs);
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
