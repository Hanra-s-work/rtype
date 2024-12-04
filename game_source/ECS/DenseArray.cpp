#include "DenseArray.hpp"
template <typename Component, typename Allocator>
DenseArray<Component, Allocator>::DenseArray() : _data(), _allocator() {}

template <typename Component, typename Allocator>
Component& DenseArray<Component, Allocator>::operator[](size_type idx) {
    assert(idx < _data.size() && "Index out of bounds");
    return _data[idx];
}

template <typename Component, typename Allocator>
const Component& DenseArray<Component, Allocator>::operator[](size_type idx) const {
    return const_cast<DenseArray*>(this)->operator[](idx);
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::size_type DenseArray<Component, Allocator>::size() const {
    return _data.size();
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::insert_at(size_type id, const Component& component) {
    ensure_sparse_size(id);
    _data[id] = component;
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::insert_at(size_type id, Component&& component) {
    ensure_sparse_size(id);
    _data[id] = std::move(component);
}

template <typename Component, typename Allocator>
template <typename... Params>
void DenseArray<Component, Allocator>::emplace_at(size_type id, Params&&... params) {
    ensure_sparse_size(id);
    _data[id].emplace(std::forward<Params>(params)...);
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::erase(size_type id) {
    if (id < _data.size()) {
        _data[id].reset();
    }
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::size_type
DenseArray<Component, Allocator>::get_index(const Component& component) const {
    for (size_type i = 0; i < _data.size(); ++i) {
        if (_data[i] && *_data[i] == component) {
            return i;
        }
    }
    return static_cast<size_type>(-1);
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::ensure_size(size_type pos) {
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
}
