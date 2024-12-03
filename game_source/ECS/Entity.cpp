#include "Entity.hpp"

Entity::Entity(size_t id) : _id(id) {}

Entity::operator size_t() const {
    return _id;
}

size_t Entity::getID() const {
    return _id;
}