#pragma once

class GameObject;

/**
 * @class Pickable
 * @brief Interface for objects that can be picked up.
 */
class Pickable {
public:
    virtual void PickUp(GameObject *picker) = 0;
};