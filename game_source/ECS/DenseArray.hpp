#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <cassert>
#include <algorithm>

template <typename Component, typename Allocator = std::allocator<Component>>
class DenseArray {
public:
    using value_type = Component;
    using reference_type = value_type&;
    using const_reference_type = const value_type&;
    using id_type = size_t;
    using id_container_t = std::vector<id_type>;
    using component_container_t = std::vector<value_type, Allocator>;
    using size_type = typename component_container_t::size_type;
    using iterator = typename component_container_t::iterator;
    using const_iterator = typename component_container_t::const_iterator;

    DenseArray() = default;
    DenseArray(const DenseArray& other) = default;
    DenseArray(DenseArray&& other) noexcept = default;
    ~DenseArray() = default;

    DenseArray& operator=(const DenseArray& other) = default;
    DenseArray& operator=(DenseArray&& other) noexcept = default;
    reference_type operator[](size_type idx);
    const_reference_type operator[](size_type idx) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    size_type size() const;
    void insert_at(size_type id, const Component& component);
    void insert_at(size_type id, Component&& component);

    template <typename... Params>
    void emplace_at(size_type id, Params&&... params);
    void erase(size_type id);
    id_type get_index(const value_type& component) const;

private:
    void ensure_size(size_type pos);

    id_container_t _ids;
    component_container_t _components;
    Allocator _allocator;
};