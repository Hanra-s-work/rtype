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

#include "GUI/ECS/Utilities/Clock.hpp"

GUI::ECS::Utilities::Clock::Clock(const std::uint32_t entityId)
    : EntityNode(entityId)
{
    _clock.restart();
    _isRunning = true;
}

GUI::ECS::Utilities::Clock::~Clock() {}

const std::int64_t GUI::ECS::Utilities::Clock::reset()
{
    std::int64_t node = 0;
    if (_isRunning) {
        node = _clock.restart().asMicroseconds();
    } else {
        node = _clock.reset().asMicroseconds();
    }
    return node;
}

const std::int64_t GUI::ECS::Utilities::Clock::getElapsedTime() const
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

const bool GUI::ECS::Utilities::Clock::isRunning() const
{
    return _isRunning;
}


const std::string GUI::ECS::Utilities::Clock::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Clock:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Is Running: " + MyRecodes::myToString(isRunning()) + "\n";
    result += indentation + "- Elapsed Time: " + MyRecodes::myToString(getElapsedTime()) + "\n";
    return result;
}

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::Clock &item)
{
    os << item.getInfo();
    return os;
}
