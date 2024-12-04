#include "ZipperIterator.hpp"

template <class... Containers>
class IndexedZipper {
public:
    using iterator = ZipperIterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    IndexedZipper(Containers&... cs);

    iterator begin();
    iterator end();
private:
    static size_t _compute_size(Containers&... containers);
    static iterator_tuple create_iterators(Containers&... containers);
    static iterator_tuple create_end_iterators(Containers&... containers);
private:
    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};
