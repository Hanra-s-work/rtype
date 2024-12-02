#include "DroppableMonster.hpp"

DroppableMonster::DroppableMonster(const int initialHealth, GameObject *drop_pointer) : Monster(initialHealth) {}

GameObject *DroppableMonster::Drop()
{
    return this->drop;
}