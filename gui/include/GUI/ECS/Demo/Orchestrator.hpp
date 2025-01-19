/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Orchestrator.hpp
*/

/**
 * @file Orchestrator.hpp
 *
 * @brief Declaration of the Orchestrator class and its related functionality.
 *
 * @details This file defines the Orchestrator class, which acts as the main orchestrator for managing the game logic, rendering, and entity interactions in the ECS architecture.
 */

#pragma once
#include <any>
#include <vector>
#include <memory>
#include <random>
#include <unordered_map>
#include "Log.hpp"
#include "Recoded.hpp"
#include "SoundLib.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Demo/Bullet.hpp"
#include "GUI/ECS/Demo/EnemyBrain.hpp"
#include "GUI/ECS/Demo/PlayerBrain.hpp"
#include "GUI/ECS/Systems.hpp"
#include "GUI/ECS/Components.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Demo
        {
            /**
             * @brief The Orchestrator class manages the overall game state, including entity creation, updates, and rendering.
             *
             * @details This class inherits from EntityNode and coordinates various systems and entities in the ECS architecture.
             * It also handles sound effects, game progression, and scene setup.
             */
            class Orchestrator : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * @param entityId The unique ID of the entity. Default is 0.
                 */
                Orchestrator(const std::uint32_t entityId = 0);

                /**
                 * @brief Destructor.
                 */
                ~Orchestrator() = default;

                /**
                 * @brief Initializes the ECS entities managed by the orchestrator.
                 *
                 * @param ecsEntities A map of type-indexed vectors containing entity data.
                 */
                void initialiseClass(std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

                /**
                 * @brief Starts the game logic and sets the game to a playing state.
                 */
                void start();

                /**
                 * @brief Stops the game logic and resets the playing state.
                 */
                void stop();

                /**
                 * @brief Resets the game state, clearing all entities and resetting conditions.
                 */
                void reset();

                /**
                 * @brief Updates the game state for the current frame.
                 */
                void tick();

                /**
                 * @brief Renders the game entities to the window.
                 */
                void render();

                /**
                 * @brief Checks if the game is over.
                 *
                 * @return True if the game is over, false otherwise.
                 */
                const bool isGameOver() const;

                /**
                 * @brief Checks if the game has been won.
                 *
                 * @return True if the game is won, false otherwise.
                 */
                const bool isGameWon() const;


                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                private:

                /**
                 * @brief Plays the shooting sound effect.
                 */
                void _shootSound();
                /**
                 * @brief Plays the damage sound effect.
                 */
                void _damageSound();
                /**
                 * @brief Plays the sound effect when an entity dies.
                 */
                void _deadSound();
                /**
                 * @brief Plays the button interaction sound effect.
                 */
                void _buttonSound();
                /**
                 * @brief Plays the sound effect when the game is over.
                 */
                void _gameOverSound();
                /**
                 * @brief Plays the sound effect when the game is won.
                 */
                void _winSound();

                /**
                 * @brief Spawns a new entity in the game.
                 */
                void _spawn();

                /**
                 * @brief Handles logic for removing or "killing" an entity.
                 */
                void _kill();

                /**
                 * @brief Spawns an enemy at the specified position.
                 *
                 * @param pos The position as a pair of (x, y) coordinates.
                 */
                void _spawnEnemy(const std::pair<float, float> pos);

                /**
                 * @brief Generates a random integer within a specified range.
                 *
                 * @param min The minimum value (inclusive). Default is 0.
                 * @param max The maximum value (inclusive). Default is 5.
                 *
                 * @return A random integer within the range.
                 */
                const int _randInt(int min = 0, int max = 5);

                /**
                 * @brief Sets up the initial game scene, including background and entities.
                 */
                void _setTheScene();

                /**
                 * @brief Sets up the text components for the game UI.
                 */
                void _setTextComponents();

                bool _playing = false;                                                                 //!< Indicates whether the game is currently playing.
                bool _gameWon = false;                                                                 //!< Indicates if the game has been won.
                bool _gameOver = false;                                                                //!< Indicates if the game is over.
                int _stepUp = -10;                                                                     //!< Step size for upward movement.
                int _stepDown = 10;                                                                    //!< Step size for downward movement.
                int _stepLeft = -10;                                                                   //!< Step size for leftward movement.
                int _stepRight = 10;                                                                   //!< Step size for rightward movement.
                float _screenPosXOffset = 75;                                                          //!< Horizontal screen offset for positioning.
                float _screenPosYOffset = 45;                                                          //!< Vertical screen offset for positioning.
                long int _activeEnemies = 0;                                                           //!< Count of active enemies in the game.
                std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> _titleHealth;      //!< UI component for displaying health.
                std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> _remainingEnemies; //!< UI component for displaying remaining enemies.
                std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> _backgroundItem;  //!< UI component for the background image.
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteBullet;                  //!< Sprite component for player bullets.
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteBulletEnemy;             //!< Sprite component for enemy bullets.
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spritePlayer;                  //!< Sprite component for the player.
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteEnemy;                   //!< Sprite component for enemies.
                std::vector<GUI::ECS::Demo::Bullet> _bullets;                                          //!< Container for all bullets in the game.
                std::shared_ptr<GUI::ECS::Systems::Window> _window;                                    //!< Pointer to the window system.
                std::shared_ptr<GUI::ECS::Systems::EventManager> _event;                               //!< Pointer to the event manager system.
                std::shared_ptr<GUI::ECS::Demo::PlayerBrain> _playerBrain;                             //!< Pointer to the player's brain logic.
                std::vector<std::shared_ptr<GUI::ECS::Demo::EnemyBrain>> _enemyBrain;                  //!< Container for enemy brains.
                std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;               //!< ECS entities managed by the orchestrator.
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             *
             * @param os The output stream.
             * @param item The sprite to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Orchestrator &item);
        }
    }
}
