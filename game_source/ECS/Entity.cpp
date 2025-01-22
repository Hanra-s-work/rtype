#include "Entity.hpp"

Entity::Entity(std::size_t id) : _id(id) {}

Entity::operator std::size_t() const {
    return _id;
}

std::size_t Entity::getID() const {
    return _id;
}