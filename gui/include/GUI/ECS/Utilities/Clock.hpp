/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.hpp
*/

/**
 * @file Clock.hpp
 * @brief This is the file that contains the Clock class
 */

#pragma once
#include <SFML/System/Clock.hpp>
#include "Debug.hpp"
#include "EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Clock : EntityNode {
                public:
                Clock();
                ~Clock();
                void reset();
                sf::Time getElapsedTime() const;
                void stop();
                void start();
                bool isRunning() const;

                private:
                bool _isRunning;
                sf::Clock _clock;
            };
        }
    }
}


