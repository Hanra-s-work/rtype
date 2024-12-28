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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor, const sf::Vector2f &position)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor, const sf::Vector2f &position)
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

void GUI::ECS::Components::TextComponent::setNormalColor(const GUI::ECS::Utilities::Colour &color)
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

void GUI::ECS::Components::TextComponent::setHoverColor(const GUI::ECS::Utilities::Colour &color)
{
    _hoverColor = color;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setClickedColor(const GUI::ECS::Utilities::Colour &color)
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

const GUI::ECS::Utilities::Font GUI::ECS::Components::TextComponent::getFont() const
{
    return _font;
}

const std::string GUI::ECS::Components::TextComponent::getFontPath() const
{
    return _font.getFontPath();
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::TextComponent::getNormalColor() const
{
    return _color;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::TextComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::TextComponent::getClickedColor() const
{
    return _clickedColor;
}

const std::string GUI::ECS::Components::TextComponent::getText() const
{
    return _text;
}

const std::uint32_t GUI::ECS::Components::TextComponent::getSize() const
{
    return _size;
}

const sf::Vector2f GUI::ECS::Components::TextComponent::getPosition() const
{
    return _textPos.getPosition();
}

const bool GUI::ECS::Components::TextComponent::getVisible() const
{
    return _visible;
}


const std::string GUI::ECS::Components::TextComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Text:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + MyRecodes::myToString(_visible) + "\n";
    result += indentation + "- Text: '" + _text + "'\n";
    result += indentation + "- (sfText) Has text: " + MyRecodes::myToString(_sfTextComponent.has_value()) + "\n";
    result += indentation + "- Size: " + MyRecodes::myToString(_size) + "\n";
    result += indentation + "- Text Position: {\n" + _textPos.getInfo(indent + 1) + "}\n";
    result += indentation + "- Font: {\n" + _font.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _color.getInfo(indent + 1) + "}\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    return result;
}



void GUI::ECS::Components::TextComponent::render(sf::RenderWindow &window) const
{
    if (_visible) {
        Debug::getInstance() << "Rendering text" << std::endl;
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
        Debug::getInstance() << "No known instance of sf::Text, creating." << std::endl;
        if (_font.getFontPath().empty()) {
            Debug::getInstance() << "No font, skipping update." << std::endl;
            return;
        }

        sf::Text node(_font.getFontInstance(), _text, _size);
        _sfTextComponent.emplace(node);
    }
    if (_textPos.isClicked()) {
        _sfTextComponent->setFillColor(_clickedColor.getColourSFML());
    } else if (_textPos.isHovered()) {
        _sfTextComponent->setFillColor(_hoverColor.getColourSFML());
    } else {
        _sfTextComponent->setFillColor(_color.getColourSFML());
    }
}

GUI::ECS::Components::TextComponent &GUI::ECS::Components::TextComponent::operator =(const GUI::ECS::Components::TextComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::TextComponent &item)
{
    os << item.getInfo();
    return os;
}
