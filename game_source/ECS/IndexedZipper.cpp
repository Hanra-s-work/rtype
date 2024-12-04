#include "IndexedZipper.hpp"

template <class... Containers>
IndexedZipper<Containers...>::IndexedZipper(Containers &...cs)
    : _begin(create_iterators(cs...)), _end(create_end_iterators(cs...)),
      _size(_compute_size(cs...)) {}

template <class... Containers>
IndexedZipper<Containers...>::iterator IndexedZipper<Containers...>::begin()
{
    return iterator(_begin, _size);
}

template <class... Containers>
IndexedZipper<Containers...>::iterator IndexedZipper<Containers...>::end()
{
    return iterator(_end, _size);
}

template <class... Containers>
size_t IndexedZipper<Containers...>::_compute_size(Containers &...containers)
{
    return std::min({containers.size()...});
}

template <class... Containers>
IndexedZipper<Containers...>::iterator_tuple IndexedZipper<Containers...>::create_iterators(Containers &...containers)
{
    return std::make_tuple(containers.begin()...);
}

template <class... Containers>
IndexedZipper<Containers...>::iterator_tuple IndexedZipper<Containers...>::create_end_iterators(Containers &...containers)
{
    return std::make_tuple(containers.end()...);
}
