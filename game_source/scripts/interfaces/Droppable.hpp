#pragma once

class GameObject;

/**
 * @class Droppable
 * @brief Interface for objects that can drop other objects upon destruction.
 */
class Droppable {
public:
    virtual GameObject *Drop(void) = 0;
};