/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Orchestrator.hpp
*/

#pragma once
#include <any>
#include <vector>
#include <memory>
#include <random>
#include <unordered_map>
#include "Log.hpp"
#include "Recoded.hpp"
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
            class Orchestrator : public EntityNode {
                public:
                Orchestrator(const std::uint32_t entityId = 0);

                ~Orchestrator() = default;

                void initialiseClass(std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

                void start();

                void stop();

                void reset();

                void tick();

                void render();

                const bool isGameOver() const;

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
                void _spawn();

                void _kill();

                void _spawnEnemy(const std::pair<float, float> pos);

                const int _randInt(int min = 0, int max = 5);

                void _setTheScene();

                void _setTextComponents();

                bool _playing = false;
                bool _gameWon = false;
                bool _gameOver = false;
                int _stepUp = -10;
                int _stepDown = 10;
                int _stepLeft = -10;
                int _stepRight = 10;
                float _screenPosXOffset = 75;
                float _screenPosYOffset = 45;
                std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> _titleHealth;
                std::optional<std::shared_ptr<GUI::ECS::Components::TextComponent>> _remainingEnemies;
                std::optional<std::shared_ptr<GUI::ECS::Components::ImageComponent>> _backgroundItem;
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteBullet;
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteBulletEnemy;
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spritePlayer;
                std::shared_ptr<GUI::ECS::Components::SpriteComponent> _spriteEnemy;
                std::vector<GUI::ECS::Demo::Bullet> _bullets;
                std::shared_ptr<GUI::ECS::Systems::Window> _window;
                std::shared_ptr<GUI::ECS::Systems::EventManager> _event;
                std::shared_ptr<GUI::ECS::Demo::PlayerBrain> _playerBrain;
                std::vector<std::shared_ptr<GUI::ECS::Demo::EnemyBrain>> _enemyBrain;
                std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;
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
