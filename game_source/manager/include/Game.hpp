#pragma once

#include <forward_list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameMessage.hpp"

class Registry;
class EventDispatcher;
class Queue;

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
     * This function returns a list of `std::string` objects.
     * These messages can be used to track game events or game state transitions.
     * 
     * @return A forward list of `std::string` objects.
     */
    std::forward_list<std::string> getGameEvents(void);

    /**
     * @brief Handles an event received from server.
     * 
     * This function processes incoming events from server.
     * 
     * @param event The game event to be processed, represented as a `std::string`.
     */
    void onServerEventReceived(std::string &event);

    /**
     * @brief Handles an event received during gameplay.
     *
     * This function processes incoming game events, allowing the game to respond to various triggers
     * such as player actions or system events.
     *
     * @param event The game event to be processed, represented as a `GameMessage`.
     */
    void onGameEventReceived(const GameMessage& event);

    /**
     * @brief Serializes a GameMessage object into a binary stream.
     *
     * This function writes the `GameMessage` object's data to the provided output stream in binary format.
     * The serialized data can later be read using the `deserialize` function.
     *
     * @param message The `GameMessage` object to serialize.
     * @param os The output stream to which the binary data will be written.
     */
    void serialize(const GameMessage& message, std::ostringstream& os);

    /**
     * @brief Deserializes a GameMessage object from a binary stream.
     *
     * This function reads binary data from the provided input stream and reconstructs a `GameMessage` object.
     * The binary data should have been written using the `serialize` function.
     *
     * @param is The input stream from which the binary data will be read.
     * @return GameMessage The reconstructed `GameMessage` object.
     */
    GameMessage deserialize(std::istringstream& is);

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
     * @brief The queue used to manage interaction with EventSystem.
     */
    Queue *_queue;

    /**
     * @brief A list of game events that have been received.
     */
    std::forward_list<GameMessage> _eventsFromGame;

    /**
     * @brief A list of events that have been received from server.
     */
    std::forward_list<GameMessage> _eventsFromServer;
};

