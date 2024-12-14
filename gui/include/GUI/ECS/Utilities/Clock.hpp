/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.hpp
*/

#pragma once
#include <SFML/System/Clock.hpp>
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Clock {
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


