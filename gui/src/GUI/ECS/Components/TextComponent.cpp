/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.cpp
*/

/**
 * @file TextComponent.cpp
 * @brief This is the file in charge of managing the text
 */

#include "GUI/ECS/Components/TextComponent.hpp"

GUI::ECS::Components::TextComponent::TextComponent() : EntityNode(0) {};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId) : EntityNode(entityId) {};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath)
    : EntityNode(entityId)
{
    setFontPath(fontPath);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text)
    : EntityNode(entityId)
{
    setFontPath(fontPath);
    setText(text);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size)
    : EntityNode(entityId)
{
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor, const sf::Vector2f &position)
    : EntityNode(entityId)
{
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    setPosition(position);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance)
    : EntityNode(entityId)
{
    setFont(fontInstance);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text)
    : EntityNode(entityId)
{
    setFont(fontInstance);
    setText(text);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size)
    : EntityNode(entityId)
{
    setFont(fontInstance);
    setText(text);
    setSize(size);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor)
    : EntityNode(entityId)
{
    setFont(fontInstance);
    setText(text);
    setSize(size);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor, const sf::Vector2f &position)
    : EntityNode(entityId)
{
    setFont(fontInstance);
    setText(text);
    setSize(size);
    setPosition(position);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _processTextComponent();
};


GUI::ECS::Components::TextComponent::~TextComponent() {};

void GUI::ECS::Components::TextComponent::setFont(const sf::Font &font)
{
    _font.update(font);
    _processTextComponent();
    _sfTextComponent->setFont(_font.getFontInstance());
}

void GUI::ECS::Components::TextComponent::setFont(const GUI::ECS::Utilities::Font &font)
{
    _font.update(font);
    _processTextComponent();
    _sfTextComponent->setFont(_font.getFontInstance());
}

void GUI::ECS::Components::TextComponent::setNormalColor(const sf::Color &color)
{
    _color = color;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setText(const std::string &text)
{
    sf::String sfmlText(text);
    _text = text;
    _textPos.setWidth(text.size());
    _processTextComponent();
    _sfTextComponent->setString(sfmlText);
}

void GUI::ECS::Components::TextComponent::setSize(const std::uint32_t &size)
{
    _size = size;
    _textPos.setHeight(size);
    _processTextComponent();
    _sfTextComponent->setCharacterSize(size);
}

void GUI::ECS::Components::TextComponent::setHoverColor(const sf::Color &color)
{
    _hoverColor = color;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setClickedColor(const sf::Color &color)
{
    _clickedColor = color;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setFontPath(const std::string &fontPath)
{
    GUI::ECS::Utilities::Font font(_font.getFontName(), fontPath);
    _font = font;
    _loadFont();
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setPosition(const sf::Vector2f &position)
{
    _textPos.setPosition(position);
    _processTextComponent();
    _sfTextComponent->setPosition(position);
}

void GUI::ECS::Components::TextComponent::setVisible(const bool visible)
{
    _visible = visible;
}

GUI::ECS::Utilities::Font GUI::ECS::Components::TextComponent::getFont() const
{
    return _font;
}

std::string GUI::ECS::Components::TextComponent::getFontPath() const
{
    return _font.getFontPath();
}

sf::Color GUI::ECS::Components::TextComponent::getNormalColor() const
{
    return _color;
}

sf::Color GUI::ECS::Components::TextComponent::getHoverColor() const
{
    return _hoverColor;
}

sf::Color GUI::ECS::Components::TextComponent::getClickedColor() const
{
    return _clickedColor;
}

std::string GUI::ECS::Components::TextComponent::getText() const
{
    return _text;
}

std::uint32_t GUI::ECS::Components::TextComponent::getSize() const
{
    return _size;
}

sf::Vector2f GUI::ECS::Components::TextComponent::getPosition() const
{
    return _textPos.getPosition();
}

bool GUI::ECS::Components::TextComponent::getVisible() const
{
    return _visible;
}

void GUI::ECS::Components::TextComponent::render(sf::RenderWindow &window) const
{
    if (_visible) {
        sf::Text data = _sfTextComponent.value();
        window.draw(data);
    }
}

void GUI::ECS::Components::TextComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    _textPos.update(mouse);
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::update(const GUI::ECS::Components::TextComponent &copy)
{
    setFont(copy.getFont());
    setNormalColor(copy.getNormalColor());
    setClickedColor(copy.getClickedColor());
    setText(copy.getText());
    setSize(copy.getSize());
    setHoverColor(copy.getHoverColor());
    setPosition(copy.getPosition());
    setVisible(copy.getVisible());
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::_loadFont()
{
    if (!_font.isLoaded()) {
        return;
    }
    _processTextComponent();
    _sfTextComponent->setFont(_font.getFontInstance());
}

void GUI::ECS::Components::TextComponent::_processTextComponent()
{
    if (!_sfTextComponent.has_value()) {
        if (_font.getFontPath().empty()) {
            return;
        }
        sf::String nodeText(_text);
        sf::Text node(_font.getFontInstance(), nodeText, _size);
        _sfTextComponent.emplace(node);
    }
    if (_textPos.isClicked()) {
        _sfTextComponent->setFillColor(_clickedColor);
    } else if (_textPos.isHovered()) {
        _sfTextComponent->setFillColor(_hoverColor);
    } else {
        _sfTextComponent->setFillColor(_color);
    }
}

GUI::ECS::Components::TextComponent &GUI::ECS::Components::TextComponent::operator =(const GUI::ECS::Components::TextComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};
