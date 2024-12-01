#pragma once

/**
 * @interface Input
 * @brief Defines an interface for handling input actions.
 *
 * The Input interface provides a contract for input-related actions such as movement and firing.
 * Any class that derives from Input must implement the pure virtual methods `OnMovement` and `OnFire`.
 */
class Input {
public:
    virtual void OnMovement(void) = 0;
    virtual void OnFire(void) = 0;
};