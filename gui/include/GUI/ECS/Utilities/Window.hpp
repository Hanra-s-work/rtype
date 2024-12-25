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
#include "GUI/ECS/Components.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent;
            class ShapeComponent;
            class ButtonComponent;
            class SpriteComponent;
        }
        namespace Utilities
        {
            class Window : public EntityNode {
                public:
                Window(const std::uint32_t entityId = 0, const std::uint32_t windowWidth = 800, const std::uint32_t windowHeight = 600, const std::string &windowName = "R-Type", unsigned int frameRateLimit = 60);
                ~Window();

                void clear(const sf::Color &color = sf::Color::Black);
                void display();
                bool isOpen() const;
                void close();

                std::optional<sf::Event> pollEvent();
                void setFramerateLimit(const unsigned int framerateLimit);
                void setFullScreen(const bool fullScreen);
                bool getFullScreen() const;

                void draw(const GUI::ECS::Components::TextComponent &text);
                void draw(const GUI::ECS::Components::ShapeComponent &shape);
                void draw(const GUI::ECS::Components::ButtonComponent &button);
                void draw(const GUI::ECS::Components::SpriteComponent &texture);

                sf::RenderWindow &getWindow();

                private:
                bool _fullScreen;
                std::string _windowName;
                sf::RenderWindow _sfWindow;
                std::uint32_t _windowWidth;
                std::uint32_t _windowHeight;
                sf::VideoMode _desktopMode = sf::VideoMode::getDesktopMode();
            };
        }
    }
}
