#pragma once

class GameObject;

/**
 * @class IDroppable
 * @brief Interface for objects that can drop other objects upon destruction.
 */
class IDroppable {
public:
    virtual GameObject *Drop(void) = 0;
};