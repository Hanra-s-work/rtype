/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.cpp
*/

/**
 * @file Window.cpp
 *
 * @brief File in charge of containing the logic for the window class
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

void GUI::ECS::Systems::Window::setPosition(const std::pair<int, int> &position)
{
    PRETTY_DEBUG << "Setting the position of the window to: " << Recoded::myToString(position) << std::endl;
    _sfWindow.setPosition({ position.first, position.second });
    PRETTY_SUCCESS << "Position set to: " << Recoded::myToString(position) << std::endl;
}

void GUI::ECS::Systems::Window::setIcon(const GUI::ECS::Components::ImageComponent &icon)
{
    PRETTY_DEBUG << "Setting window Icon" << std::endl;
    const GUI::ECS::Components::TextureComponent iconTexture = icon.getImage();
    const std::any textureCast = iconTexture.getTexture();
    const std::optional<sf::Texture> textureCapsule = Utilities::unCast<sf::Texture, CustomExceptions::NoTexture>(textureCast, true, "<No instance of sf::Texture in the provided texture (extracted from ImageComponent>, system error: ");
    if (!textureCapsule.has_value()) {
        PRETTY_CRITICAL << "There is no texture to work with (gathered from ImageComponent)." << std::endl;
        throw CustomExceptions::NoTexture("<No instance of sf::Texture in the provided texture (extracted from ImageComponent>");
    }
    const sf::Texture texture = textureCapsule.value();
    const sf::Image image = texture.copyToImage();
    if (image.getSize().x == 0 || image.getSize().y == 0) {
        PRETTY_CRITICAL << "Image extracted from texture is invalid." << std::endl;
        throw CustomExceptions::NoIcon("Invalid image size (extracted from sf::Texture for setting the icon of the window).");
    }
    const std::uint8_t *pixelData = image.getPixelsPtr();
    const sf::Vector2u size = image.getSize();
    _sfWindow.setIcon(size, pixelData);
    PRETTY_SUCCESS << "Image icon set." << std::endl;
}

void GUI::ECS::Systems::Window::setTitle(const std::string &title)
{
    PRETTY_DEBUG << "Setting the window title to: '" << title << "'." << std::endl;
    _sfWindow.setTitle(title);
    _windowName = title;
    PRETTY_SUCCESS << "Title set to: '" << title << "'" << std::endl;
}

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

const std::string GUI::ECS::Systems::Window::getTitle() const
{
    return _windowName;
}

const std::pair<int, int> GUI::ECS::Systems::Window::getDimensions() const
{
    sf::Vector2u dim = _sfWindow.getSize();
    return std::make_pair<int>(dim.x, dim.y);
}

const std::pair<int, int> GUI::ECS::Systems::Window::getPosition() const
{
    sf::Vector2i pos = _sfWindow.getPosition();
    return std::pair<int, int>(pos.x, pos.y);
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
    const std::any textCapsule = text.render();
    const std::optional<sf::Text> txt = Utilities::unCast<sf::Text, CustomExceptions::NoRenderableText>(textCapsule, true, "<Unknown or empty text component, this is not a sf::Text>, any_cast error: ");
    if (!txt.has_value()) {
        PRETTY_CRITICAL << "<There is not sf::Text component to render, component id: '" << Recoded::myToString(text.getEntityNodeId()) << "'\n" << std::endl;
        throw CustomExceptions::NoRenderableText("<There is no sf::Text component to render>");
    }
    _sfWindow.draw(txt.value());
    PRETTY_SUCCESS << "Text component, entity id: '" << Recoded::myToString(text.getEntityNodeId()) << "', is drawn." << std::endl;
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ShapeComponent &shape)
{
    if (!shape.isVisible()) {
        PRETTY_WARNING << "Shape is hidden, id: '"
            << Recoded::myToString(shape.getEntityNodeId())
            << "', name: '" << shape.getShapeTypeString() << "'." << std::endl;
        return;
    }
    const std::optional<std::pair<GUI::ECS::Components::ActiveShape, std::any>> shapeCapsule = shape.render();
    if (!shapeCapsule.has_value()) {
        PRETTY_WARNING << "Shape is not renderable, id: '"
            << Recoded::myToString(shape.getEntityNodeId()) << "'" << std::endl;
        return;
        // throw CustomExceptions::NoRenderableShape("<std::pair not found in std::any, have you initialised the class with a shape?>");
    }
    const std::pair<GUI::ECS::Components::ActiveShape, std::any> pairNode = shapeCapsule.value();
    const GUI::ECS::Components::ActiveShape shapeType = pairNode.first;
    const std::any shapeData = pairNode.second;
    if (shapeType == GUI::ECS::Components::ActiveShape::NONE) {
        PRETTY_WARNING << "There is no shape to render, skipping" << std::endl;
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::RECTANGLE) {
        const std::optional<sf::RectangleShape> renderableShape = Utilities::unCast<sf::RectangleShape, CustomExceptions::NoRenderableShape>(shapeData, true, "<Unknown or empty shape, this is not a RectangleShape>, any_cast error: ");
        if (!renderableShape.has_value()) {
            PRETTY_CRITICAL << "Shape : '" << shape.getShapeTypeString() << "' could not be rendered.\n" << std::endl;
            throw CustomExceptions::NoRenderableShape("<There is no sf::RectangleShape located in std::any>");
        }
        _sfWindow.draw(renderableShape.value());
        PRETTY_SUCCESS << "Shape: '" << shape.getShapeTypeString() << "' is drawn." << std::endl;
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CIRCLE) {
        const std::optional<sf::CircleShape> renderableShape = Utilities::unCast<sf::CircleShape, CustomExceptions::NoRenderableShape>(shapeData, true, "<Unknown or empty shape, this is not a CircleShape>, any_cast error: ");
        if (!renderableShape.has_value()) {
            PRETTY_CRITICAL << "Shape : '" << shape.getShapeTypeString() << "' could not be rendered.\n" << std::endl;
            throw CustomExceptions::NoRenderableShape("<There is no sf::CircleShape located in std::any>");
        }
        _sfWindow.draw(renderableShape.value());
        PRETTY_SUCCESS << "Shape: '" << shape.getShapeTypeString() << "' is drawn." << std::endl;
        return;
    };
    if (shapeType == GUI::ECS::Components::ActiveShape::CONVEX) {
        const std::optional<sf::ConvexShape> renderableShape = Utilities::unCast<sf::ConvexShape, CustomExceptions::NoRenderableShape>(shapeData, true, "<Unknown or empty shape, this is not a ConvexShape>, any_cast error: ");
        if (!renderableShape.has_value()) {
            PRETTY_CRITICAL << "Shape : '" << shape.getShapeTypeString() << "' could not be rendered.\n" << std::endl;
            throw CustomExceptions::NoRenderableShape("<There is no sf::ConvexShape located in std::any>");
        }
        _sfWindow.draw(renderableShape.value());
        PRETTY_SUCCESS << "Shape: '" << shape.getShapeTypeString() << "' is drawn." << std::endl;
        return;
    };
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ImageComponent &image)
{
    if (!image.isVisible()) {
        PRETTY_WARNING << "The image named '" << image.getName()
            << "' and whom's application is '" << image.getApplication()
            << "' is set to invisible, it will thus not be rendered."
            << std::endl;
        return;
    }
    const std::any imageCapsule = image.render();
    const std::optional<sf::Sprite> spriteCapsule = Utilities::unCast<sf::Sprite, CustomExceptions::NoRenderableImage>(imageCapsule, true, "<Unknown or empty Image, this is not an sf::Sprite>, any_cast error");
    if (!spriteCapsule.has_value()) {
        PRETTY_CRITICAL << "Image : '" << image.getName()
            << "' and whom's application is '" << image.getApplication()
            << "' could not be rendered.\n" << std::endl;
        throw CustomExceptions::NoRenderableImage("<Missing Image, this is not an sf::Sprite>, any_cast error");
    }
    _sfWindow.draw(spriteCapsule.value());
    PRETTY_SUCCESS << "Image named '" << image.getName()
        << "' and whom's application is '" << image.getApplication()
        << "' is drawn" << std::endl;
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::SpriteComponent &sprite)
{
    if (!sprite.isVisible()) {
        PRETTY_WARNING << "The sprite named '" << sprite.getName()
            << "' and whom's application is '" << sprite.getApplication()
            << "' is set to invisible, it will thus not be rendered."
            << std::endl;
        return;
    }
    const std::any spriteNode = sprite.render();
    const std::optional<sf::Sprite> spriteCapsule = Utilities::unCast<sf::Sprite, CustomExceptions::NoRenderableImage>(spriteNode, true, "<Unknown Image, this is not an sf::Sprite>, any_cast error");
    if (!spriteCapsule.has_value()) {
        PRETTY_CRITICAL << "Sprite : '" << sprite.getName()
            << "' and whom's application is '" << sprite.getApplication()
            << "' could not be rendered.\n" << std::endl;
        throw CustomExceptions::NoRenderableImage("<Missing Sprite, this is not an sf::Sprite>, any_cast error");
    }
    _sfWindow.draw(spriteCapsule.value());
    PRETTY_SUCCESS << "Sprite named '" << sprite.getName()
        << "' and whom's application is '" << sprite.getApplication()
        << "' is drawn" << std::endl;
}

void GUI::ECS::Systems::Window::draw(const GUI::ECS::Components::ButtonComponent &button)
{
    if (!button.isVisible()) {
        PRETTY_WARNING << "The button named '" << button.getName()
            << "' and whom's application is '" << button.getApplication()
            << "' is set to invisible, it will thus not be rendered."
            << std::endl;
        return;
    }
    std::unordered_map<std::type_index, std::any> buttonCapsule = button.render();

    const std::any shapeCapsule = buttonCapsule[typeid(GUI::ECS::Components::ShapeComponent)];
    if (shapeCapsule.has_value()) {
        const std::optional<GUI::ECS::Components::ShapeComponent> shape = Utilities::unCast<GUI::ECS::Components::ShapeComponent, CustomExceptions::NoRenderableShape>(shapeCapsule, false, "<There is no ShapeComponent to render>");
        if (!shape.has_value()) {
            PRETTY_WARNING << "There is no shape to render for the button, skipping shape rendering." << std::endl;
        }
        draw(shape.value());
    }

    const std::any textCapsule = buttonCapsule[typeid(GUI::ECS::Components::TextComponent)];
    if (textCapsule.has_value()) {
        const std::optional<GUI::ECS::Components::TextComponent> text = Utilities::unCast<GUI::ECS::Components::TextComponent, CustomExceptions::NoRenderableShape>(textCapsule, false, "<There is no TextComponent to render>");
        if (!text.has_value()) {
            PRETTY_WARNING << "There is no text to render for the button, skipping text rendering." << std::endl;
        }
        draw(text.value());
    }
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Window &item)
{
    os << item.getInfo();
    return os;
}
