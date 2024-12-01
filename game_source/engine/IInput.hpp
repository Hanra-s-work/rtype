#pragma once

/**
 * @interface IInput
 * @brief Defines an interface for handling input actions.
 *
 * The IInput interface provides a contract for input-related actions such as movement and firing.
 * Any class that derives from IInput must implement the pure virtual methods `OnMovement` and `OnFire`.
 */
class IInput {
public:
    virtual void OnMovement(void) = 0;
    virtual void OnFire(void) = 0;
};