#pragma once

/**
 * @struct Weapon
 * @brief Represents a weapon and its attributes in the game.
 * 
 * This structure is used to define the properties of a weapon, including its damage,
 * fire rate, and cooldown time. It can be applied to various types of weapons, such as guns or
 * other ranged items, to control how they behave in the game.
 */
struct Weapon {
    int damage;       /**< The damage dealt by the weapon on each shot. */
    float fire_rate;  /**< The rate at which the weapon can fire, in shots per second. */
    float cooldown;   /**< The time, in seconds, before the weapon can fire again after each shot. */
    bool shot;        /**< The state of the firing */
};
