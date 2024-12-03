#include "SparseArray.hpp"

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::reference_type
SparseArray<Component, Allocator>::operator[](size_t idx) {
    assert(idx < _data.size() && "Index out of bounds");
    return _data[idx];
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::const_reference_type
SparseArray<Component, Allocator>::operator[](size_t idx) const {
    assert(idx < _data.size() && "Index out of bounds");
    return _data[idx];
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::iterator
SparseArray<Component, Allocator>::begin() {
    return _data.begin();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::const_iterator
SparseArray<Component, Allocator>::begin() const {
    return _data.begin();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::const_iterator
SparseArray<Component, Allocator>::cbegin() const {
    return _data.cbegin();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::iterator
SparseArray<Component, Allocator>::end() {
    return _data.end();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::const_iterator
SparseArray<Component, Allocator>::end() const {
    return _data.end();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::const_iterator
SparseArray<Component, Allocator>::cend() const {
    return _data.cend();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::size_type
SparseArray<Component, Allocator>::size() const {
    return _data.size();
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::reference_type
SparseArray<Component, Allocator>::insert_at(size_type pos, const Component& component) {
    ensure_size(pos);
    _data[pos] = component;
    return _data[pos];
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::reference_type
SparseArray<Component, Allocator>::insert_at(size_type pos, Component&& component) {
    ensure_size(pos);
    _data[pos] = std::move(component);
    return _data[pos];
}

template <typename Component, typename Allocator>
template <class... Params>
typename SparseArray<Component, Allocator>::reference_type
SparseArray<Component, Allocator>::emplace_at(size_type pos, Params&&... params) {
    ensure_size(pos);
    _data[pos].reset();
    std::allocator_traits<Allocator>::construct(
            _allocator, std::addressof(_data[pos]), std::forward<Params>(params)...);
    return _data[pos];
}

template <typename Component, typename Allocator>
void SparseArray<Component, Allocator>::erase(size_type pos) {
    if (pos < _data.size()) {
        _data[pos].reset();
    }
}

template <typename Component, typename Allocator>
typename SparseArray<Component, Allocator>::size_type
SparseArray<Component, Allocator>::get_index(const value_type& component) const {
    auto it = std::find(_data.begin(), _data.end(), component);
    return it != _data.end() ? std::distance(_data.begin(), it) : size_type(-1);
}

template <typename Component, typename Allocator>
void SparseArray<Component, Allocator>::ensure_size(size_type pos) {
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
}