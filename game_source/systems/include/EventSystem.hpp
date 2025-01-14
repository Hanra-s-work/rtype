#pragma once

#include "Registry.hpp"

/**
 * @brief Processes events from the queue and performs actions.
 * 
 * This function continuously checks the event queue in the provided `Registry` 
 * instance and processes the events one by one. Each event is validated and, 
 * if valid, an action is performed based on the event type.
 * 
 * @param r Reference to the `Registry` instance where the event queue is located.
 */
void event_system(Registry &r);

/**
 * @brief Validates the action associated with the event.
 * 
 * This function checks whether the action in the given event is valid.
 * 
 * @param event The `GameMessage` event to be validated.
 * @param r Reference to the `Registry` instance.
 * 
 * @return `true` if the action is valid, otherwise `false`.
 */
bool validateAction(const GameMessage& event, Registry& r);

/**
 * @brief Performs the action associated with the event.
 * 
 * This function performs the appropriate action based on the event type.
 * 
 * @param event The `GameMessage` event that dictates the action.
 * @param r Reference to the `Registry` instance.
 * 
 * @return `true` if the action was successfully performed, otherwise `false`.
 */
bool performAction(const GameMessage& event, Registry& r);