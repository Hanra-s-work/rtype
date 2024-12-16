#pragma once

#include "Registry.hpp"
#include "Behaviour.hpp"
#include "Velocity.hpp"
#include "Zipper.hpp"

#define AI_TIMER 2f

/**
 * @brief AI system that updates the behaviour and velocity of entities.
 * 
 * This function implements the AI logic for entities, updating their `Behaviour` and `Velocity`
 * components based on the time elapsed (`delta_time`). The AI may change the entity's state or
 * move it depending on its behaviour.
 * 
 * @param r The `Registry` that holds all the game entities and their components.
 * @param delta_time The time elapsed since the last update, used to scale updates based on frame rate.
 */
void ai_system(Registry &r, float delta_time);
