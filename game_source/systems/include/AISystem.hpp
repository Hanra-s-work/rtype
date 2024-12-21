#pragma once

class Registry;

#define AI_TIMER 2.0f

/**
 * @brief AI system that updates the behaviour and velocity of entities.
 * 
 * This function implements the AI logic for entities, updating their `Behaviour` and `Velocity`
 * components based on the time elapsed (`delta_time`). The AI may change the entity's state or
 * move it depending on its behaviour.
 * 
 * @param r The `Registry` that holds all the game entities and their components.
 */
void ai_system(Registry &r);
