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
    using container_t = std::vector<std::optional<Component>, Allocator>;
    using size_type = typename container_t::size_type;

    DenseArray() = default;
    DenseArray(const DenseArray& other) = default;
    DenseArray(DenseArray&& other) noexcept = default;
    ~DenseArray() = default;

    DenseArray& operator=(const DenseArray& other) = default;
    DenseArray& operator=(DenseArray&& other) noexcept = default;
    Component& operator[](size_type idx);
    const Component& operator[](size_type idx) const;

    typename container_t::iterator begin();
    typename container_t::const_iterator begin() const;
    typename container_t::const_iterator cbegin() const;
    typename container_t::iterator end();
    typename container_t::const_iterator end() const;
    typename container_t::const_iterator cend() const;

    size_type size() const;
    void insert_at(size_type id, const Component& component);
    void insert_at(size_type id, Component&& component);

    template <typename... Params>
    void emplace_at(size_type id, Params&&... params);
    void erase(size_type id);
    size_type get_index(const value_type& component) const;

private:
    void ensure_size(size_type pos);

    container_t _data;
    Allocator _allocator;
};