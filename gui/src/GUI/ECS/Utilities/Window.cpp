/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.cpp
*/

#include "GUI/ECS/Utilities/Window.hpp"

GUI::ECS::Utilities::Window::Window(const std::uint32_t windowWidth, const std::uint32_t windowHeight, const std::string &windowName)
    : _window(sf::VideoMode(windowWidth, windowHeight), windowName),
    _windowWidth(windowWidth),
    _windowHeight(windowHeight),
    _windowName(windowName)
{
}

GUI::ECS::Utilities::Window::~Window() {}

void GUI::ECS::Utilities::Window::clear(const sf::Color &color)
{
    _window.clear(color);
}

void GUI::ECS::Utilities::Window::display()
{
    _window.display();
}

bool GUI::ECS::Utilities::Window::isOpen() const
{
    return _window.isOpen();
}

void GUI::ECS::Utilities::Window::close()
{
    _window.close();
}

sf::RenderWindow &GUI::ECS::Utilities::Window::getWindow()
{
    return _window;
}

bool GUI::ECS::Utilities::Window::pollEvent(sf::Event &event)
{
    return _window.pollEvent(event);
}
