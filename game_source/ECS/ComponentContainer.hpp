#pragma once

#include <vector>
#include <optional>
#include <variant>
#include <memory>
#include <cassert>
#include <algorithm>

#include "DenseArray.hpp"
#include "SparseArray.hpp"

template <typename Component, typename Allocator = std::allocator<Component>>
class ComponentContainer {
public:
    using value_type = Component;
    using optional_t = std::optional<Component>;
    using sparse_storage_t = SparseArray<Component, Allocator>;
    using dense_storage_t = DenseArray<Component, Allocator>;
    using size_type = typename sparse_storage_t::size_type;

    using reference = std::optional<Component>&;
    using const_reference = const std::optional<Component>&;
    using iterator = std::variant<typename sparse_storage_t::iterator, typename dense_storage_t::iterator>;
    using const_iterator = std::variant<typename sparse_storage_t::const_iterator, typename dense_storage_t::const_iterator>;

    ComponentContainer();

    reference operator[](size_t idx);
    const_reference operator[](size_t idx) const;

    void insert(size_type id, const Component& component);
    std::optional<Component> get(size_type id) const;
    void ComponentContainer::erase(size_type id);
    void resize(size_type new_size);
    void optimize_storage(size_type sparse_threshold, size_type dense_threshold);

private:
    using ComponentStorage = std::variant<sparse_storage_t, dense_storage_t>;
    ComponentStorage _storage;

    template <typename NewContainer>
    void migrate_storage(NewContainer& new_storage);
};

