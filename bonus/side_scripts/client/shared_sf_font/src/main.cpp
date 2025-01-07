/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** main.cpp
*/

// #include <SFML/System.hpp>
// #include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }, 32), "R-Type");
    window.setFramerateLimit(60);

    std::shared_ptr<sf::Font> node = std::make_shared<sf::Font>("./assets/Blox.ttf");

    sf::Text sample(*node, "Hello World", 30);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            // Close window : exit
            if (event->is<sf::Event::Closed>())
                window.close();
            // Check if the escape key was the one pressed
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }
        window.clear(sf::Color::Black);
        window.draw(sample);
        window.display();
    }
}
