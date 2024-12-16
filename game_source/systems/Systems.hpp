#pragma once

class Registry;

/**
 * @brief Sets up all the necessary systems for the game.
 * 
 * This function initializes and configures all the game systems that will run during the game's update loop. 
 * It registers systems for handling different components, such as AI, movement, collision detection, 
 * weapon management, and entity spawning. It prepares the game state for processing during each frame.
 * 
 * @param r The `Registry` that contains all the game entities and their components, used to register 
 *        systems and access components.
 */
void setup_systems(Registry &r);
void setup_components(Registry &r);

