#include "DenseArray.hpp"

template <typename Component, typename Allocator>
DenseArray<Component, Allocator>::DenseArray() : _ids(), _components(), _allocator() {}

template <typename Component, typename Allocator>
Component& DenseArray<Component, Allocator>::operator[](size_type idx) {
    assert(idx < _components.size() && "Index out of bounds");
    return _components[idx];
}

template <typename Component, typename Allocator>
const Component& DenseArray<Component, Allocator>::operator[](size_type idx) const {
    return _components[idx];
}


template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::iterator DenseArray<Component, Allocator>::begin() {
    return _components.begin();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::const_iterator DenseArray<Component, Allocator>::begin() const {
    return _components.begin();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::const_iterator DenseArray<Component, Allocator>::cbegin() const {
    return _components.cbegin();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::iterator DenseArray<Component, Allocator>::end() {
    return _components.end();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::const_iterator DenseArray<Component, Allocator>::end() const {
    return _components.end();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::const_iterator DenseArray<Component, Allocator>::cend() const {
    return _components.cend();
}

template <typename Component, typename Allocator>
typename DenseArray<Component, Allocator>::size_type DenseArray<Component, Allocator>::size() const {
    return _components.size();
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::insert_at(size_type id, const Component& component) {
    ensure_size(id);
    _ids.push_back(id);
    _components.push_back(component);
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::insert_at(size_type id, Component&& component) {
    ensure_size(id);
    _ids.push_back(id);
    _components[id] = std::move(component);
}

template <typename Component, typename Allocator>
template <typename... Params>
void DenseArray<Component, Allocator>::emplace_at(size_type id, Params&&... params) {
    ensure_size(id);
    _ids.push_back(id);
    _components.emplace_back(std::forward<Params>(params)...);
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::erase(size_type id) {
    _ids.erase(_ids.begin() + id);
    _components.erase(_components.begin() + id);
}

template <typename Component, typename Allocator>
DenseArray<Component, Allocator>::id_type DenseArray<Component, Allocator>::get_index(const Component& component) const {
    for (size_type i = 0; i < _data.size(); ++i) {
        if (_data[i] && *_data[i] == component) {
            return i;
        }
    }
    return static_cast<size_type>(-1);
}

template <typename Component, typename Allocator>
void DenseArray<Component, Allocator>::ensure_size(size_type pos) {
    if (pos >= _components.size()) {
        _ids.resize(pos + 1);
        _components.resize(pos + 1);
    }
}
