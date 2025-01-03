/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Utilities.hpp
*/

/**
 * @file Utilities.hpp
 * @brief This is the file that links the utility children ressources.
 */

#pragma once
#include "GUI/ECS/Utilities/Key.hpp"
#include "GUI/ECS/Utilities/Font.hpp"
#include "GUI/ECS/Utilities/Clock.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Utilities/Window.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"
#include "GUI/ECS/Utilities/EventManager.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            enum class Key;
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
