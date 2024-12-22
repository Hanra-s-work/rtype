/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.cpp
*/

/**
 * @file Clock.cpp
 * @brief This is the file in charge of managing the clock ticking.
 */

#include "GUI/ECS/Utilities/Clock.hpp"

GUI::ECS::Utilities::Clock::Clock(const std::uint32_t entityId)
    : EntityNode(entityId)
{
    sf::Clock clock;
    _clock = clock;
    _isRunning = true;
}

GUI::ECS::Utilities::Clock::~Clock() {}

void GUI::ECS::Utilities::Clock::reset()
{
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
