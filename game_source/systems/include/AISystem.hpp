#pragma once

#include "Registry.hpp"
#include "Behaviour.hpp"
#include "Velocity.hpp"

#define AI_TIMER 2.0f

/**
 * @brief AI system that updates the behaviour and velocity of entities.
 * 
 * This function implements the AI logic for entities, updating their `Behaviour` and `Velocity`
 * components based on the time elapsed (`delta_time`). The AI may change the entity's state or
 * move it depending on its behaviour.
 * 
 * @param r The `Registry` that holds all the game entities and their components.
 * @param behaviours The container of the component `Behaviour`.
 * @param velocities The container of the component `Velocity`.
 */
void ai_system(Registry &r, ComponentContainer<Behaviour> &behaviours, ComponentContainer<Velocity> &velocities);
