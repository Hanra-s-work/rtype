#pragma once

#include <cstddef>

class Entity {
public:
    explicit Entity(size_t id);
    operator size_t() const;
    size_t getID() const;

private:
    size_t _id;
};
