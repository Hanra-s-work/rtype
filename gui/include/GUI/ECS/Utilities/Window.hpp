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
                Window(const std::uint32_t windowWidth = 800, const std::uint32_t windowHeight = 600, const std::string &windowName = "R-Type", unsigned int frameRateLimit = 60);
                ~Window();

                void clear(const sf::Color &color = sf::Color::Black);
                void display();
                bool isOpen() const;
                void close();
                bool pollEvent(sf::Event &event);
                void setFramerateLimit(const unsigned int framerateLimit);
                void setFullScreen(const bool fullScreen);
                bool getFullScreen() const;

                sf::RenderWindow &getWindow();

                private:
                bool _fullScreen;
                std::string _windowName;
                sf::RenderWindow _window;
                std::uint32_t _windowWidth;
                std::uint32_t _windowHeight;
                sf::VideoMode _desktopMode = sf::VideoMode::getDesktopMode();
            };
        }
    }
}
