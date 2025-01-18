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
            class Orchestrator {
                public:
                Orchestrator() = default;

                ~Orchestrator() = default;

                void initialiseClass(std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

                void start();

                void stop();

                void reset();

                void tick();

                void render();

                const bool isGameOver() const;

                const bool isGameWon() const;

                private:
                void _spawn();

                void _kill();

                void _spawnEnemy(const std::pair<float, float> pos);

                const int _randInt(int min = 0, int max = 5);

                void _setTheScene();

                bool _playing = false;
                bool _gameWon = false;
                bool _gameOver = false;
                int _stepUp = -10;
                int _stepDown = 10;
                int _stepLeft = -10;
                int _stepRight = 10;
                float _screenPosXOffset = 75;
                float _screenPosYOffset = 45;
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
        }
    }
}
