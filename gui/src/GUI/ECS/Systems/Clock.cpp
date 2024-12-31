/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.cpp
*/

/**
 * @file Clock.cpp
 * @brief This file contains the implementation of the Clock class for time management.
 */

#include "GUI/ECS/Systems/Clock.hpp"

GUI::ECS::Systems::Clock::Clock(const std::uint32_t entityId)
    : EntityNode(entityId)
{
    _clock.restart();
    _isRunning = true;
}

GUI::ECS::Systems::Clock::~Clock() {}

const std::int64_t GUI::ECS::Systems::Clock::reset()
{
    std::int64_t node = 0;
    if (_isRunning) {
        node = _clock.restart().asMicroseconds();
    } else {
        node = _clock.reset().asMicroseconds();
    }
    return node;
}

const std::int64_t GUI::ECS::Systems::Clock::getElapsedTime() const
{
    return _clock.getElapsedTime().asMicroseconds();
}

void GUI::ECS::Systems::Clock::start()
{
    _clock.start();
    _isRunning = true;
}

void GUI::ECS::Systems::Clock::stop()
{
    _clock.stop();
    _isRunning = false;
}

const bool GUI::ECS::Systems::Clock::isRunning() const
{
    return _isRunning;
}


const std::string GUI::ECS::Systems::Clock::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Clock:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Is Running: " + Recoded::myToString(isRunning()) + "\n";
    result += indentation + "- Elapsed Time: " + Recoded::myToString(getElapsedTime()) + "\n";
    return result;
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Clock &item)
{
    os << item.getInfo();
    return os;
}
