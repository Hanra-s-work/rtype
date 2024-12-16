/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.hpp
*/

#pragma once

#include <string>
#include <cstring>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Window : EntityNode {
                public:
                Window(const std::uint32_t windowWidth = 800, const std::uint32_t windowHeight = 600, const std::string &windowName = "R-Type");
                ~Window();

                void clear(const sf::Color &color = sf::Color::Black);
                void display();
                bool isOpen() const;
                void close();
                bool pollEvent(sf::Event &event);

                sf::RenderWindow &getWindow();

                private:
                sf::RenderWindow _window;
                std::uint32_t _windowWidth;
                std::uint32_t _windowHeight;
                std::string _windowName;
            };
        }
    }
}
