/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.hpp
*/

#pragma once
#include <map>
#include <string>
#include <functional>
namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class EventManager {
                public:
                EventManager();
                ~EventManager();
                void addEvent(const std::string &name, const std::function<void()> &callback);
                void removeEvent(const std::string &name);
                void triggerEvent(const std::string &name);
                void clearEvents();
                private:
                std::map<std::string, std::function<void()>> _events;
            };
        }
    }
}


