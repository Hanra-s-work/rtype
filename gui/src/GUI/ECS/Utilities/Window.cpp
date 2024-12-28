/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.cpp
*/

#include "GUI/ECS/Utilities/Window.hpp"

GUI::ECS::Utilities::Window::Window(const std::uint32_t entityId, const std::uint32_t windowWidth, const std::uint32_t windowHeight, const std::string &windowName, unsigned int frameRateLimit)
    : EntityNode(entityId),
    _sfWindow(sf::VideoMode({ windowWidth, windowHeight }), windowName),
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

std::optional<sf::Event> GUI::ECS::Utilities::Window::pollEvent()
{
    return _sfWindow.pollEvent();
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
        _sfWindow.create(_desktopMode, _windowName, sf::Style::None);
    } else {
        _sfWindow.create(sf::VideoMode({ _windowWidth, _windowHeight }), _windowName, sf::Style::Close);
    }
}

const bool GUI::ECS::Utilities::Window::getFullScreen() const
{
    return _fullScreen;
}

const std::string GUI::ECS::Utilities::Window::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Window:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Window Name: '" + _windowName + "'\n";
    result += indentation + "- Window Width: " + MyRecodes::myToString(_windowWidth) + "\n";
    result += indentation + "- Window Height: " + MyRecodes::myToString(_windowHeight) + "\n";
    result += indentation + "- Full Screen: " + MyRecodes::myToString(_fullScreen) + "\n";
    result += indentation + "- Desktop Mode: ( size: ( width: " + MyRecodes::myToString(_desktopMode.size.x) + ", height: " + MyRecodes::myToString(_desktopMode.size.y) + "), bits per pixel: " + MyRecodes::myToString(_desktopMode.bitsPerPixel) + ")\n";
    return result;
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

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::Window &item)
{
    os << item.getInfo();
    return os;
}
