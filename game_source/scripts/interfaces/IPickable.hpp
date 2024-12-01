#pragma once

class GameObject;

/**
 * @class IPickable
 * @brief Interface for objects that can be picked up.
 */
class IPickable {
public:
    virtual void PickUp(GameObject *picker) = 0;
};