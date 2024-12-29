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
    _inConstructor = true;
    setFontPath(fontPath);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor, const sf::Vector2f &position)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    setPosition(position);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFont(fontInstance);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    setSize(size);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    setSize(size);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor, const sf::Vector2f &position)
    : EntityNode(entityId)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    setSize(size);
    setPosition(position);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processTextComponent();
};


GUI::ECS::Components::TextComponent::~TextComponent() {};

void GUI::ECS::Components::TextComponent::setFont(const sf::Font &font)
{
    _font.update(font);
    _fontChanged = true;
    if (!_inConstructor) {
        _processTextComponent();
    }
}

void GUI::ECS::Components::TextComponent::setFont(const GUI::ECS::Utilities::Font &font)
{
    _font.update(font);
    _fontChanged = true;
    if (!_inConstructor) {
        _processTextComponent();
    }
}

void GUI::ECS::Components::TextComponent::setText(const std::string &text)
{
    if (_text != text) {
        _text = text;
        _textAltered = true;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setSize(const std::uint32_t &size)
{
    if (_size != size) {
        _size = size;
        _sizeAltered = true;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setNormalColor(const GUI::ECS::Utilities::Colour &color)
{
    if (_color != color) {
        _color = color;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setHoverColor(const GUI::ECS::Utilities::Colour &color)
{
    if (_hoverColor != color) {
        _hoverColor = color;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setClickedColor(const GUI::ECS::Utilities::Colour &color)
{
    if (_clickedColor != color) {
        _clickedColor = color;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setFontPath(const std::string &fontPath, const std::string &name)
{
    if (fontPath.empty()) {
        throw MyException::InvalidFontPath("<empty path>");
    }
    if (_font.getFontPath() != fontPath) {
        std::string nameChild = name;
        if (nameChild == "") {
            nameChild = _font.getFontName();
        }
        GUI::ECS::Utilities::Font font(nameChild, fontPath);
        _font = font;
        _fontChanged = true;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setPosition(const sf::Vector2f &position)
{
    if (_textPos.getPosition() != position) {
        _textPos.setPosition(position);
        _positionAltered = true;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setVisible(const bool visible)
{
    _visible = visible;
}

void GUI::ECS::Components::TextComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
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
    result += indentation + "- In Constructor: " + MyRecodes::myToString(_inConstructor) + "\n";
    result += indentation + "- Font Altered: " + MyRecodes::myToString(_fontAltered) + "\n";
    result += indentation + "- Font Changed: " + MyRecodes::myToString(_fontChanged) + "\n";
    result += indentation + "- Text Altered: " + MyRecodes::myToString(_textAltered) + "\n";
    result += indentation + "- Size Altered: " + MyRecodes::myToString(_sizeAltered) + "\n";
    result += indentation + "- Position Altered: " + MyRecodes::myToString(_positionAltered) + "\n";
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
        if (!_sfTextComponent.has_value()) {
            throw MyException::NoText("to be rendered.");
        }
        sf::Text data = _sfTextComponent.value();
        window.draw(data);
    }
}

void GUI::ECS::Components::TextComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    _textPos.update(mouse);
    if (!_inConstructor) {
        _processTextComponent();
    }
}

void GUI::ECS::Components::TextComponent::update(const GUI::ECS::Components::TextComponent &copy)
{
    _inConstructor = true;
    setText(copy.getText());
    setSize(copy.getSize());
    setFont(copy.getFont());
    setVisible(copy.getVisible());
    setPosition(copy.getPosition());
    setHoverColor(copy.getHoverColor());
    setNormalColor(copy.getNormalColor());
    setClickedColor(copy.getClickedColor());
    _fontAltered = true;
    _inConstructor = false;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::_initialiseText()
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
}

void GUI::ECS::Components::TextComponent::_loadFont()
{
    if (!_font.isLoaded()) {
        std::string msg = "Font name : '" + _font.getFontName() + "' (not found) in '" + _font.getFontPath() + "'";
        throw MyException::NoFont(msg);
    }
    if (!_sfTextComponent.has_value()) {
        Debug::getInstance() << "Text not initialised, initialising..." << std::endl;
        _initialiseText();
    }
    _sfTextComponent->setFont(_font.getFontInstance());
}

void GUI::ECS::Components::TextComponent::_processTextComponent()
{
    Debug::getInstance() << "Checking initiailisation" << std::endl;
    _initialiseText();
    if (_sfTextComponent.has_value()) {
        if (_fontChanged) {
            Debug::getInstance() << "Going to update the font." << std::endl;
            _loadFont();
            _fontChanged = false;
            _fontAltered = true;
        }
        if (_textAltered) {
            Debug::getInstance() << "Going to update the text." << std::endl;
            _sfTextComponent->setString(_text);
            _textAltered = false;
            _fontAltered = true;
            Debug::getInstance() << "Text Updated" << std::endl;
        }
        if (_sizeAltered) {
            Debug::getInstance() << "Going to update the font size" << std::endl;
            _sfTextComponent->setCharacterSize(_size);
            _sizeAltered = false;
            _fontAltered = true;
        }
        if (_positionAltered) {
            Debug::getInstance() << "Going to check the position" << std::endl;
            _sfTextComponent->setPosition(_textPos.getPosition());
            _positionAltered = false;
            _fontAltered = true;
        }
        if (_fontAltered) {
            Debug::getInstance() << "Going to update the font" << std::endl;
            Debug::getInstance() << "Text component has a value" << std::endl;
            sf::FloatRect textBounds = _sfTextComponent->getGlobalBounds();
            _textPos.setDimension(textBounds.size);
            _fontAltered = false;
        }
    } else {
        Debug::getInstance() << "No text component value to be managed" << std::endl;
    }
    Debug::getInstance() << "Font loaded, updating text colour" << std::endl;
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
