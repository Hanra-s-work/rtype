#pragma once

#include "Scene.hpp"

/**
 * @class Game
 * @brief A central class for managing the current state of the game.
 *
 * The Game class provides access to the current scene, acting as a static entry point 
 * for managing and interacting with the active game environment.
 * 
 * There are definetly more things to do here
 */
class Game {
public:
    static Scene currentScene;
};