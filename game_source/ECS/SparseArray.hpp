#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <cassert>

template <typename Component, typename Allocator = std::allocator<Component>>
class SparseArray {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = const value_type&;
    using container_t = std::vector<value_type, Allocator>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    SparseArray() = default;
    SparseArray(const SparseArray& other) = default;
    SparseArray(SparseArray&& other) noexcept = default;
    ~SparseArray() = default;

    SparseArray& operator=(const SparseArray& other) = default;
    SparseArray& operator=(SparseArray&& other) noexcept = default;
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    size_type size() const;
    reference_type insert_at(size_type pos, const Component& component);
    reference_type insert_at(size_type pos, Component&& component);
    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params);
    void erase(size_type pos);

private:
    void ensure_size(size_type pos);

    container_t _data;
    Allocator _allocator;
};