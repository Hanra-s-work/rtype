/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** Clock.hpp
*/

#pragma once
#include <SFML/System/Clock.hpp>

namespace GUI
{
    namespace Utilities
    {
        class Clock {
            public:
            Clock();
            ~Clock();
            void stop();
            void start();
            void reset();
            void restart();
            sf::Time getElapsedTime();
            bool isRunning();
            private:
            sf::Clock _sfml_clock;
        };
    }
}
