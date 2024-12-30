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
    _sfSharedWindow = std::make_shared<sf::RenderWindow>(_sfWindow);
    _sfAnySharedWindow = std::make_any<std::shared_ptr<sf::RenderWindow>>(std::shared_ptr<sf::RenderWindow>(_sfSharedWindow));
}

GUI::ECS::Utilities::Window::~Window() {}

void GUI::ECS::Utilities::Window::clear(const GUI::ECS::Utilities::Colour &color)
{
    _sfWindow.clear(color.toSFMLColour());
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

std::any &GUI::ECS::Utilities::Window::getWindow()
{
    return _sfAnySharedWindow;
}

std::any GUI::ECS::Utilities::Window::pollEvent()
{
    std::any response;
    std::optional<sf::Event> node = _sfWindow.pollEvent();
    if (node.has_value()) {
        sf::Event evt = node.value();
        std::any tmp(static_cast<sf::Event>(evt));
        response = tmp;
    }
    return response;
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
    if (!text.isVisible()) {
        return;
    }
    std::any textCapsule = text.render();
    if (!textCapsule.has_value()) {
        throw MyException::NoRenderableText();
    }
    try {
        sf::Text txt = std::any_cast<sf::Text>(textCapsule);
        _sfWindow.draw(txt);
    }
    catch (std::bad_any_cast &e) {
        std::string response = "<Unknown text, this is not a sf::Text>, any_cast error";
        response += e.what();
        throw MyException::NoRenderableText(response);
    }
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::ShapeComponent &shape)
{
    if (!shape.isVisible()) {
        return;
    }
    std::optional<std::pair<GUI::ECS::Components::ActiveShape, std::any>> shapeCapsule = shape.render();
    if (!shapeCapsule.has_value()) {
        return;
        // throw MyException::NoRenderableShape("<std::pair not found in std::any, have you initialised the class with a shape?>");
    }
    std::pair<GUI::ECS::Components::ActiveShape, std::any> pairNode = shapeCapsule.value();
    GUI::ECS::Components::ActiveShape shapeType = pairNode.first;
    std::any shapeData = pairNode.second;
    if (shapeType == GUI::ECS::Components::ActiveShape::NONE) {
        Debug::getInstance() << "There is no shape to render, skipping" << std::endl;
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::RECTANGLE) {
        if (!shapeData.has_value()) {
            throw MyException::NoRenderableShape("<There is no sf::RectangleShape located in std::any>");
        }
        try {
            sf::RectangleShape renderableShape = std::any_cast<sf::RectangleShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a RectangleShape>, any_cast error";
            response += e.what();
            throw MyException::InvalidShape(response);
        }
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CIRCLE) {
        if (!shapeData.has_value()) {
            throw MyException::NoRenderableShape("<There is no sf::CircleShape located in std::any>");
        }
        try {
            sf::CircleShape renderableShape = std::any_cast<sf::CircleShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a CircleShape>, any_cast error";
            response += e.what();
            throw MyException::InvalidShape(response);
        }
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CONVEX) {
        if (!shapeData.has_value()) {
            throw MyException::NoRenderableShape("<There is not an sf::ConvexShape located in std::any>");
        }
        try {
            sf::ConvexShape renderableShape = std::any_cast<sf::ConvexShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a ConvexShape>, any_cast error";
            response += e.what();
            throw MyException::InvalidShape(response);
        }
        return;
    };
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::ImageComponent &image)
{
    if (!image.isVisible()) {
        return;
    }
    std::any imageCapsule = image.render();
    if (!imageCapsule.has_value()) {
        throw MyException::NoRenderableImage("<sf::Sprite not found in std::any>");
    }
    try {
        sf::Sprite sprite = std::any_cast<sf::Sprite>(imageCapsule);
        _sfWindow.draw(sprite);
    }
    catch (std::bad_any_cast &e) {
        std::string response = "<Unknown Image, this is not an sf::Sprite>, any_cast error";
        response += e.what();
        throw MyException::NoRenderableImage(response);
    }
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::SpriteComponent &sprite)
{
    if (!sprite.isVisible()) {
        return;
    }
    std::any spriteCapsule = sprite.render();
    if (!spriteCapsule.has_value()) {
        throw MyException::NoRenderableSprite("<sf::Sprite not found in std::any>");
    }
    try {
        sf::Sprite spr = std::any_cast<sf::Sprite>(spriteCapsule);
        _sfWindow.draw(spr);
    }
    catch (std::bad_any_cast &e) {
        std::string response = "<Unknown Sprite, this is not an sf::Sprite>, any_cast error";
        response += e.what();
        throw MyException::NoRenderableSprite(response);
    }
}

void GUI::ECS::Utilities::Window::draw(const GUI::ECS::Components::ButtonComponent &button)
{
    if (!button.isVisible()) {
        return;
    }
    std::unordered_map<std::type_index, std::any> buttonCapsule = button.render();

    std::any textCapsule = buttonCapsule[typeid(GUI::ECS::Components::TextComponent)];
    if (textCapsule.has_value()) {
        GUI::ECS::Components::TextComponent text = std::any_cast<GUI::ECS::Components::TextComponent>(textCapsule);
        draw(text);
    }

    std::any shapeCapsule = buttonCapsule[typeid(GUI::ECS::Components::ShapeComponent)];
    if (shapeCapsule.has_value()) {
        GUI::ECS::Components::ShapeComponent shape = std::any_cast<GUI::ECS::Components::ShapeComponent>(shapeCapsule);
        draw(shape);
    }
}

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::Window &item)
{
    os << item.getInfo();
    return os;
}
