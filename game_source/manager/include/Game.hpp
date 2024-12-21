#pragma once

#include <forward_list>
#include "GameMessage.hpp"

class Registry;
class EventDispatcher;

/**
 * @brief Represents the main game logic and state management.
 * 
 * The `Game` class manages the overall game state, handles events, and updates the game loop. It integrates 
 * with a `Registry` to manage game entities and their components and uses an `EventDispatcher` to handle 
 * game events. The class allows for event handling and periodic updates based on the elapsed time.
 */
class Game {
public:
    /**
     * @brief Constructs a new `Game` object.
     * 
     * Initializes the game state, the `Registry`, and the `EventDispatcher` to set up the game environment.
     */
    Game();

    /**
     * @brief Destroys the `Game` object.
     * 
     * Cleans up resources used by the game, including the `Registry` and `EventDispatcher`.
     */
    ~Game();

    /**
     * @brief Updates the game state for the current frame.
     * 
     * This function processes the game loop, updating game logic, entities, and handling events.
     * It is typically called once per frame, with `deltaTime` representing the time elapsed 
     * since the last frame to ensure smooth and consistent gameplay.
     * 
     * @param _deltaTime The time elapsed since the last frame, used to update game entities and logic.
     */
    void update(float _deltaTime);

    /**
     * @brief Retrieves game messages.
     * 
     * This function returns a reference to a list of `GameMessage` objects.
     * These messages can be used to track game events or game state transitions.
     * 
     * @return A reference to a forward list of `GameMessage` objects.
     */
    std::forward_list<GameMessage> &getGameEvents(void);

    /**
     * @brief Handles an event received during gameplay.
     * 
     * This function processes incoming game events, allowing the game to respond to various triggers 
     * such as player actions or system events.
     * 
     * @param event The game event to be processed, represented as a `GameMessage`.
     */
    void onEventReceived(const GameMessage& event);

private:
    /**
     * @brief The game's entity and component registry, used to manage game state.
     */
    Registry *_game;

    /**
     * @brief The event dispatcher used to manage and dispatch game events.
     */
    EventDispatcher *_dispatcher;

    /**
     * @brief A list of game events that have been received.
     */
    std::forward_list<GameMessage> _events;
};

