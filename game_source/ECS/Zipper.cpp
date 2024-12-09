#include "Zipper.hpp"

template <class... Containers>
Zipper<Containers...>::Zipper(Containers &...cs)
    : _begin(create_iterators(cs...)), _end(create_end_iterators(cs...)),
      _size(_compute_size(cs...)) {}

template <class... Containers>
Zipper<Containers...>::iterator Zipper<Containers...>::begin()
{
    return iterator(_begin, _size);
}

template <class... Containers>
Zipper<Containers...>::iterator Zipper<Containers...>::end()
{
    return iterator(_end, _size);
}

template <class... Containers>
size_t Zipper<Containers...>::_compute_size(Containers &...containers)
{
    return std::min({containers.size()...});
}

template <class... Containers>
Zipper<Containers...>::iterator_tuple Zipper<Containers...>::create_iterators(Containers &...containers)
{
    return std::make_tuple(containers.begin()...);
}

template <class... Containers>
Zipper<Containers...>::iterator_tuple Zipper<Containers...>::create_end_iterators(Containers &...containers)
{
    return std::make_tuple(containers.end()...);
}
