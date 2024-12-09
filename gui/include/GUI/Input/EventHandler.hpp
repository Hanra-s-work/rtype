/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventHandler.hpp
*/

#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
    namespace Input
    {
        class EventHandler {
            public:
            EventHandler();
            ~EventHandler();
            void update();
            bool isKeyPressed(sf::Keyboard::Key key);
            bool isMousePressed(sf::Mouse::Button button);
            sf::Vector2i getMousePosition();
            std::vector<sf::Keyboard::Key> getKeys();
            private:
            sf::Event _sfml_event;
        };
    }
}
