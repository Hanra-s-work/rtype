#pragma once

#include <Monster.hpp>
#include <Droppable.hpp>

/**
 * @class DroppableMonster
 * @brief Represents a monster that drops an item upon destruction.
 */
class DroppableMonster : public Monster, public IDroppable {
public:
    GameObject* drop;

    void OnDestroy() override { Drop(); }
    GameObject* Drop() override;
};