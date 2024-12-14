/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.cpp
*/

#include "GUI/ECS/Utilities/Clock.hpp"

GUI::ECS::Utilities::Clock::Clock()
{
    sf::Clock clock;
    _clock = clock;
    _isRunning = true;
}

GUI::ECS::Utilities::Clock::~Clock() {}

void GUI::ECS::Utilities::Clock::reset()
{
    // if (not _clock) {
    //     _clock = sf::Clock();
    // }
    _clock.restart();
}

sf::Time GUI::ECS::Utilities::Clock::getElapsedTime() const
{
    return _clock.getElapsedTime();
}

void GUI::ECS::Utilities::Clock::start()
{
    _isRunning = true;
    _clock.restart();
}

void GUI::ECS::Utilities::Clock::stop()
{
    _isRunning = false;
}

bool GUI::ECS::Utilities::Clock::isRunning() const
{
    return _isRunning;
}
