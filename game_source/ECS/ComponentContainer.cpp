#include "ComponentContainer.hpp"

template <typename Component, typename Allocator>
ComponentContainer<Component, Allocator>::ComponentContainer() : _storage(sparse_storage_t()) {}

template <typename Component, typename Allocator>
void ComponentContainer<Component, Allocator>::insert(size_type id, const Component& component) {
    if (std::holds_alternative<sparse_storage_t>(_storage)) {
        auto& sparse = std::get<sparse_storage_t>(_storage);
        if (id >= sparse.size()) {
            sparse.resize(id + 1);
        }
        sparse[id] = component;
    } else {
        auto& dense = std::get<dense_storage_t>(_storage);
        dense.first.push_back(id);
        dense.second.push_back(component);
    }
}

template <typename Component, typename Allocator>
std::optional<Component> ComponentContainer<Component, Allocator>::get(size_type id) const {
    if (std::holds_alternative<sparse_storage_t>(_storage)) {
        const auto& sparse = std::get<sparse_storage_t>(_storage);
        if (id < sparse.size()) {
            return sparse[id];
        }
    } else {
        const auto& dense = std::get<dense_storage_t>(_storage);
        auto it = std::find(dense.first.begin(), dense.first.end(), id);
        if (it != dense.first.end()) {
            size_type index = std::distance(dense.first.begin(), it);
            return dense.second[index];
        }
    }
    return std::nullopt;
}

template <typename Component, typename Allocator>
void ComponentContainer<Component, Allocator>::erase(size_type id)
{
    std::visit([id](auto& storage) {
        using T = std::decay_t<decltype(storage)>;
        if constexpr (std::is_same_v<T, sparse_storage_t>) {
            if (id < storage.size()) {
                storage[id].reset();
            }
        } else if constexpr (std::is_same_v<T, dense_storage_t>) {
            auto& [ids, components] = storage;
            auto it = std::find(ids.begin(), ids.end(), id);
            if (it != ids.end()) {
                size_t index = std::distance(ids.begin(), it);
                ids.erase(it);
                components.erase(components.begin() + index);
            }
        }
    }, _storage);
}

template <typename Component, typename Allocator>
void ComponentContainer<Component, Allocator>::resize(size_type new_size) {
    if (std::holds_alternative<sparse_storage_t>(_storage)) {
        auto& sparse = std::get<sparse_storage_t>(_storage);
        sparse.resize(new_size);
    } else {}
}

template <typename Component, typename Allocator>
void ComponentContainer<Component, Allocator>::optimize_storage(size_type sparse_threshold, size_type dense_threshold) {
    if (std::holds_alternative<sparse_storage_t>(_storage)) {
        auto& sparse = std::get<sparse_storage_t>(_storage);
        size_type filled = std::count_if(sparse.begin(), sparse.end(), [](const auto& opt) { return opt.has_value(); });
        if (filled >= dense_threshold) {
            dense_storage_t dense;
            migrate_storage(dense);
            _storage = std::move(dense);
        }
    } else {
        auto& dense = std::get<dense_storage_t>(_storage);
        if (dense.first.size() <= sparse_threshold) {
            sparse_storage_t sparse;
            migrate_storage(sparse);
            _storage = std::move(sparse);
        }
    }
}

template <typename Component, typename Allocator>
template <typename NewContainer>
void ComponentContainer<Component, Allocator>::migrate_storage(NewContainer& new_storage) {
    if (std::holds_alternative<sparse_storage_t>(_storage)) {
        const auto& sparse = std::get<sparse_storage_t>(_storage);
        for (size_type i = 0; i < sparse.size(); ++i) {
            if (sparse[i]) {
                new_storage.first.push_back(i);
                new_storage.second.push_back(*sparse[i]);
            }
        }
    } else {
        const auto& dense = std::get<dense_storage_t>(_storage);
        size_type max_id = *std::max_element(dense.first.begin(), dense.first.end());
        new_storage.resize(max_id + 1);
        for (size_type i = 0; i < dense.first.size(); ++i) {
            new_storage[dense.first[i]] = dense.second[i];
        }
    }
}
