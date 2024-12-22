/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.cpp
*/

#include "GUI/ECS/Utilities/Window.hpp"

GUI::ECS::Utilities::Window::Window(const std::uint32_t windowWidth, const std::uint32_t windowHeight, const std::string &windowName, unsigned int frameRateLimit)
    : _sfWindow(sf::VideoMode(windowWidth, windowHeight), windowName),
    _windowWidth(windowWidth),
    _windowHeight(windowHeight),
    _windowName(windowName)
{
    _sfWindow.setFramerateLimit(frameRateLimit);
}

GUI::ECS::Utilities::Window::~Window() {}

void GUI::ECS::Utilities::Window::clear(const sf::Color &color)
{
    _sfWindow.clear(color);
}

void GUI::ECS::Utilities::Window::display()
{
    _sfWindow.display();
}

bool GUI::ECS::Utilities::Window::isOpen() const
{
    return _sfWindow.isOpen();
}

void GUI::ECS::Utilities::Window::close()
{
    _sfWindow.close();
}

sf::RenderWindow &GUI::ECS::Utilities::Window::getWindow()
{
    return _sfWindow;
}

bool GUI::ECS::Utilities::Window::pollEvent(sf::Event &event)
{
    return _sfWindow.pollEvent(event);
}

void GUI::ECS::Utilities::Window::setFramerateLimit(const unsigned int framerateLimit)
{
    _sfWindow.setFramerateLimit(framerateLimit);
}

void GUI::ECS::Utilities::Window::setFullScreen(const bool fullScreen)
{
    _fullScreen = fullScreen;

    if (_sfWindow.isOpen()) {
        _sfWindow.close();
    }

    if (_fullScreen) {
        _sfWindow.create(_desktopMode, _windowName, sf::Style::Fullscreen);
    } else {
        _sfWindow.create(sf::VideoMode(_windowWidth, _windowHeight), _windowName, sf::Style::Close);
    }
}

bool GUI::ECS::Utilities::Window::getFullScreen() const
{
    return _fullScreen;
}


void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::TextComponent &text)
{
    text.render(_sfWindow);
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::ShapeComponent &shape)
{
    shape.render(_sfWindow);
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::ButtonComponent &button)
{
    button.render(_sfWindow);
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::SpriteComponent &sprite)
{
    sprite.render(_sfWindow);
}
