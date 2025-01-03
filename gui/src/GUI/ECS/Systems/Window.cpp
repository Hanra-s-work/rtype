/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.cpp
*/

#include "GUI/ECS/Systems/Window.hpp"

GUI::ECS::Systems::Window::Window(const std::uint32_t entityId, const std::uint32_t windowWidth, const std::uint32_t windowHeight, const std::string &windowName, unsigned int frameRateLimit)
    : EntityNode(entityId),
    _sfWindow(sf::VideoMode({ windowWidth, windowHeight }), windowName),
    _windowWidth(windowWidth),
    _windowHeight(windowHeight),
    _windowName(windowName)
{
    _sfWindow.setFramerateLimit(frameRateLimit);
}

GUI::ECS::Systems::Window::~Window() {}

void GUI::ECS::Systems::Window::clear(const GUI::ECS::Systems::Colour &color)
{
    std::any systemColour = color.getRenderColour();
    if (!systemColour.has_value()) {
        throw CustomExceptions::NoColour("<There was no content returned by getRenderColour when std::any (containing sf::Font was expected)>");
    }
    try {
        sf::Color result = std::any_cast<sf::Color>(systemColour);
        _sfWindow.clear(result);
    }
    catch (std::bad_any_cast &e) {
        throw CustomExceptions::NoColour("<The content returned by the getRenderColour function is not of type sf::Color>, system error: " + std::string(e.what()));
    }
}

void GUI::ECS::Systems::Window::display()
{
    _sfWindow.display();
}

bool GUI::ECS::Systems::Window::isOpen() const
{
    return _sfWindow.isOpen();
}

void GUI::ECS::Systems::Window::close()
{
    _sfWindow.close();
}

std::any GUI::ECS::Systems::Window::pollEvent()
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

void GUI::ECS::Systems::Window::setFramerateLimit(const unsigned int framerateLimit)
{
    _sfWindow.setFramerateLimit(framerateLimit);
}

void GUI::ECS::Systems::Window::setFullScreen(const bool fullScreen)
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

const bool GUI::ECS::Systems::Window::getFullScreen() const
{
    return _fullScreen;
}

const std::string GUI::ECS::Systems::Window::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Window:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Window Name: '" + _windowName + "'\n";
    result += indentation + "- Window Width: " + Recoded::myToString(_windowWidth) + "\n";
    result += indentation + "- Window Height: " + Recoded::myToString(_windowHeight) + "\n";
    result += indentation + "- Full Screen: " + Recoded::myToString(_fullScreen) + "\n";
    result += indentation + "- Desktop Mode: ( size: ( width: " + Recoded::myToString(_desktopMode.size.x) + ", height: " + Recoded::myToString(_desktopMode.size.y) + "), bits per pixel: " + Recoded::myToString(_desktopMode.bitsPerPixel) + ")\n";
    return result;
}


void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::TextComponent &text)
{
    if (!text.isVisible()) {
        return;
    }
    std::any textCapsule = text.render();
    if (!textCapsule.has_value()) {
        throw CustomExceptions::NoRenderableText();
    }
    try {
        sf::Text txt = std::any_cast<sf::Text>(textCapsule);
        _sfWindow.draw(txt);
    }
    catch (std::bad_any_cast &e) {
        std::string response = "<Unknown text, this is not a sf::Text>, any_cast error";
        response += e.what();
        throw CustomExceptions::NoRenderableText(response);
    }
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ShapeComponent &shape)
{
    if (!shape.isVisible()) {
        return;
    }
    std::optional<std::pair<GUI::ECS::Components::ActiveShape, std::any>> shapeCapsule = shape.render();
    if (!shapeCapsule.has_value()) {
        return;
        // throw CustomExceptions::NoRenderableShape("<std::pair not found in std::any, have you initialised the class with a shape?>");
    }
    std::pair<GUI::ECS::Components::ActiveShape, std::any> pairNode = shapeCapsule.value();
    GUI::ECS::Components::ActiveShape shapeType = pairNode.first;
    std::any shapeData = pairNode.second;
    if (shapeType == GUI::ECS::Components::ActiveShape::NONE) {
        PRETTY_WARNING << "There is no shape to render, skipping" << std::endl;
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::RECTANGLE) {
        if (!shapeData.has_value()) {
            throw CustomExceptions::NoRenderableShape("<There is no sf::RectangleShape located in std::any>");
        }
        try {
            sf::RectangleShape renderableShape = std::any_cast<sf::RectangleShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a RectangleShape>, any_cast error";
            response += e.what();
            throw CustomExceptions::InvalidShape(response);
        }
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CIRCLE) {
        if (!shapeData.has_value()) {
            throw CustomExceptions::NoRenderableShape("<There is no sf::CircleShape located in std::any>");
        }
        try {
            sf::CircleShape renderableShape = std::any_cast<sf::CircleShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a CircleShape>, any_cast error";
            response += e.what();
            throw CustomExceptions::InvalidShape(response);
        }
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CONVEX) {
        if (!shapeData.has_value()) {
            throw CustomExceptions::NoRenderableShape("<There is not an sf::ConvexShape located in std::any>");
        }
        try {
            sf::ConvexShape renderableShape = std::any_cast<sf::ConvexShape>(shapeData);
            _sfWindow.draw(renderableShape);
        }
        catch (std::bad_any_cast &e) {
            std::string response = "<Unknown shape, this is not a ConvexShape>, any_cast error";
            response += e.what();
            throw CustomExceptions::InvalidShape(response);
        }
        return;
    };
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ImageComponent &image)
{
    if (!image.isVisible()) {
        return;
    }
    std::any imageCapsule = image.render();
    if (!imageCapsule.has_value()) {
        throw CustomExceptions::NoRenderableImage("<sf::Sprite not found in std::any>");
    }
    std::optional<sf::Sprite> spriteCapsule = Utilities::unCast<sf::Sprite, CustomExceptions::NoRenderableImage>(imageCapsule, true, "<Unknown Image, this is not an sf::Sprite>, any_cast error");
    if (!spriteCapsule.has_value()) {
        throw CustomExceptions::NoRenderableImage("<Unknown Image, this is not an sf::Sprite>, any_cast error");
    }
    PRETTY_DEBUG << "Uncasting sprite" << std::endl;
    sf::Sprite sprite = spriteCapsule.value();
    PRETTY_DEBUG << "Sprite Un-casted" << std::endl;
    _sfWindow.draw(sprite);
    PRETTY_DEBUG << "Sprite drawn" << std::endl;
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::SpriteComponent &sprite)
{
    if (!sprite.isVisible()) {
        return;
    }
    std::any spriteNode = sprite.render();
    if (!spriteNode.has_value()) {
        throw CustomExceptions::NoRenderableImage("<sf::Sprite not found in std::any>");
    }
    std::optional<sf::Sprite> spriteCapsule = Utilities::unCast<sf::Sprite, CustomExceptions::NoRenderableImage>(spriteNode, true, "<Unknown Image, this is not an sf::Sprite>, any_cast error");
    if (!spriteCapsule.has_value()) {
        throw CustomExceptions::NoRenderableImage("<Unknown Sprite, this is not an sf::Sprite>, any_cast error");
    }
    PRETTY_DEBUG << "Uncasting sprite" << std::endl;
    sf::Sprite spr = spriteCapsule.value();
    PRETTY_DEBUG << "Sprite Un-casted" << std::endl;
    _sfWindow.draw(spr);
    PRETTY_DEBUG << "Sprite drawn" << std::endl;
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ButtonComponent &button)
{
    if (!button.isVisible()) {
        return;
    }
    std::unordered_map<std::type_index, std::any> buttonCapsule = button.render();

    std::any shapeCapsule = buttonCapsule[typeid(GUI::ECS::Components::ShapeComponent)];
    if (shapeCapsule.has_value()) {
        GUI::ECS::Components::ShapeComponent shape = std::any_cast<GUI::ECS::Components::ShapeComponent>(shapeCapsule);
        draw(shape);
    }

    std::any textCapsule = buttonCapsule[typeid(GUI::ECS::Components::TextComponent)];
    if (textCapsule.has_value()) {
        GUI::ECS::Components::TextComponent text = std::any_cast<GUI::ECS::Components::TextComponent>(textCapsule);
        draw(text);
    }
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Window &item)
{
    os << item.getInfo();
    return os;
}
