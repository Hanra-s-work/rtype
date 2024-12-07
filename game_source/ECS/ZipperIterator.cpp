#include "ZipperIterator.hpp"

template <class... Containers>
ZipperIterator<Containers...>::ZipperIterator(iterator_tuple const &it_tuple, size_t max)
    : _current(it_tuple), _max(max), _idx(0) {}

template <class... Containers>
ZipperIterator<Containers...>::ZipperIterator(const ZipperIterator &z)
    : _current(z._current), _max(z._max), _idx(z._idx) {}

template <class... Containers>
ZipperIterator<Containers...> &ZipperIterator<Containers...>::operator++()
{
    incr_all(std::index_sequence_for<Containers...>{});
    return *this;
}

template <class... Containers>
ZipperIterator<Containers...> ZipperIterator<Containers...>::operator++(int)
{
    ZipperIterator tmp(*this);
    ++(*this);
    return tmp;
}

template <class... Containers>
ZipperIterator<Containers...>::value_type ZipperIterator<Containers...>::operator*()
{
    return to_value(std::index_sequence_for<Containers...>{});
}

template <class... Containers>
ZipperIterator<Containers...>::value_type *ZipperIterator<Containers...>::operator->()
{
    return &(*this);
}

template <class... Containers>
bool operator==(const ZipperIterator<Containers...> &lhs, const ZipperIterator<Containers...> &rhs)
{
    return lhs._idx == rhs._idx;
}

template <class... Containers>
bool operator!=(const ZipperIterator<Containers...> &lhs, const ZipperIterator<Containers...> &rhs)
{
    return lhs._idx != rhs._idx;
}

template <class... Containers>
template <size_t... Is>
void ZipperIterator<Containers...>::incr_all(std::index_sequence<Is...>)
{
    (++std::get<Is>(_current), ...);

    while (!all_set(std::index_sequence<Is...>{})) {
        (++std::get<Is>(_current), ...);
    }

    ++_idx;
}

template <class... Containers>
template <size_t... Is>
bool ZipperIterator<Containers...>::all_set(std::index_sequence<Is...>)
{
    return (... && (std::get<Is>(_current) != std::get<Is>(_current)));
}

template <class... Containers>
template <size_t... Is>
ZipperIterator<Containers...>::value_type ZipperIterator<Containers...>::to_value(std::index_sequence<Is...>)
{
    return std::tuple<it_reference_t<Containers>...>(*(std::get<Is>(_current))...);
}
