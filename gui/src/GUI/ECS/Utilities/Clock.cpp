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
    _clock.restart();
    _isRunning = true;
}

GUI::ECS::Utilities::Clock::~Clock() {}

std::int64_t GUI::ECS::Utilities::Clock::reset()
{
    std::int64_t node = 0;
    if (_isRunning) {
        node = _clock.restart().asMicroseconds();
    } else {
        node = _clock.reset().asMicroseconds();
    }
    return node;
}

std::int64_t GUI::ECS::Utilities::Clock::getElapsedTime() const
{
    return _clock.getElapsedTime().asMicroseconds();
}

void GUI::ECS::Utilities::Clock::start()
{
    _clock.start();
    _isRunning = true;
}

void GUI::ECS::Utilities::Clock::stop()
{
    _clock.stop();
    _isRunning = false;
}

bool GUI::ECS::Utilities::Clock::isRunning() const
{
    return _isRunning;
}
