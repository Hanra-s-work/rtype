#pragma once

#include <vector>
#include <optional>
#include <variant>
#include <memory>
#include <cassert>
#include <algorithm>

template <typename Component, typename Allocator = std::allocator<Component>>
class ComponentContainer {
public:
    using value_type = Component;
    using optional_t = std::optional<Component>;
    using sparse_storage_t = std::vector<optional_t, Allocator>;
    using dense_storage_t = std::pair<std::vector<size_t>, std::vector<Component, Allocator>>;
    using size_type = typename sparse_storage_t::size_type;


    ComponentContainer();

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

