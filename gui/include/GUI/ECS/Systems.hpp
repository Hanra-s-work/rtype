/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Systems.hpp
*/

/**
 * @file Systems.hpp
 * @brief This is the file that links the utility children ressources.
 */

#pragma once
#include "GUI/ECS/Systems/Key.hpp"
#include "GUI/ECS/Systems/Font.hpp"
#include "GUI/ECS/Systems/Clock.hpp"
#include "GUI/ECS/Systems/Colour.hpp"
#include "GUI/ECS/Systems/Window.hpp"
#include "GUI/ECS/Systems/MouseInfo.hpp"
#include "GUI/ECS/Systems/EventManager.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            enum class Key;
            enum class MouseWheel;
            class KeyMapper;
            class Font;
            class Clock;
            class Colour;
            class EventManager;
            class MouseInfo;
            class Window;
        }
    }
}
