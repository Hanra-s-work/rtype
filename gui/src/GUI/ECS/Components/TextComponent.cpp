/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.cpp
*/

/**
 * @file TextComponent.cpp
 *
 * @brief This is the file in charge of managing the text
 */

#include "GUI/ECS/Components/TextComponent.hpp"

GUI::ECS::Components::TextComponent::TextComponent()
    : EntityNode(0),
    _font(0),
    _textPos(0),
    _color(0, GUI::ECS::Systems::Colour::Black),
    _hoverColor(0, GUI::ECS::Systems::Colour::Black),
    _clickedColor(0, GUI::ECS::Systems::Colour::Black)
{
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFontPath(fontPath);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFontPath(fontPath);
    setText(text);
    setSize(size);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::pair<float, float> &position)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFont(fontInstance);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size)
    : EntityNode(entityId),
    _font(entityId),
    _textPos(entityId),
    _color(entityId, GUI::ECS::Systems::Colour::Black),
    _hoverColor(entityId, GUI::ECS::Systems::Colour::Black),
    _clickedColor(entityId, GUI::ECS::Systems::Colour::Black)
{
    _inConstructor = true;
    setFont(fontInstance);
    setText(text);
    setSize(size);
    _inConstructor = false;
    _processTextComponent();
};

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor)
    : EntityNode(entityId),
    _font(0),
    _textPos(0),
    _color(0, GUI::ECS::Systems::Colour::Black),
    _hoverColor(0, GUI::ECS::Systems::Colour::Black),
    _clickedColor(0, GUI::ECS::Systems::Colour::Black)
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

GUI::ECS::Components::TextComponent::TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::pair<float, float> &position)
    : EntityNode(entityId),
    _font(0),
    _textPos(0),
    _color(0, GUI::ECS::Systems::Colour::Black),
    _hoverColor(0, GUI::ECS::Systems::Colour::Black),
    _clickedColor(0, GUI::ECS::Systems::Colour::Black)
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

void GUI::ECS::Components::TextComponent::setFont(const GUI::ECS::Systems::Font &font)
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

void GUI::ECS::Components::TextComponent::setNormalColor(const GUI::ECS::Systems::Colour &color)
{
    if (_color != color) {
        _color = color;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setHoverColor(const GUI::ECS::Systems::Colour &color)
{
    if (_hoverColor != color) {
        _hoverColor = color;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setClickedColor(const GUI::ECS::Systems::Colour &color)
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
        throw CustomExceptions::InvalidFontPath("<empty path>");
    }
    if (_font.getFontPath() != fontPath) {
        std::string nameChild = name;
        if (nameChild == "") {
            nameChild = _font.getFontName();
        }
        GUI::ECS::Systems::Font font(nameChild, fontPath);
        _font = font;
        _fontChanged = true;
        if (!_inConstructor) {
            _processTextComponent();
        }
    }
}

void GUI::ECS::Components::TextComponent::setPosition(const std::pair<float, float> &position)
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

const bool GUI::ECS::Components::TextComponent::isVisible() const
{
    return _visible;
}

const GUI::ECS::Systems::Font GUI::ECS::Components::TextComponent::getFont() const
{
    return _font;
}

const std::string GUI::ECS::Components::TextComponent::getFontPath() const
{
    return _font.getFontPath();
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::TextComponent::getNormalColor() const
{
    return _color;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::TextComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::TextComponent::getClickedColor() const
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

const std::pair<float, float> GUI::ECS::Components::TextComponent::getPosition() const
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
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- In Constructor: " + Recoded::myToString(_inConstructor) + "\n";
    result += indentation + "- Font Altered: " + Recoded::myToString(_fontAltered) + "\n";
    result += indentation + "- Font Changed: " + Recoded::myToString(_fontChanged) + "\n";
    result += indentation + "- Text Altered: " + Recoded::myToString(_textAltered) + "\n";
    result += indentation + "- Size Altered: " + Recoded::myToString(_sizeAltered) + "\n";
    result += indentation + "- Position Altered: " + Recoded::myToString(_positionAltered) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
    result += indentation + "- Text: '" + _text + "'\n";
    result += indentation + "- (sfText) Has text: " + Recoded::myToString(_sfTextComponent.has_value()) + "\n";
    result += indentation + "- Size: " + Recoded::myToString(_size) + "\n";
    result += indentation + "- Text Position: {\n" + _textPos.getInfo(indent + 1) + "}\n";
    result += indentation + "- Font: {\n" + _font.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _color.getInfo(indent + 1) + "}\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    return result;
}

std::any GUI::ECS::Components::TextComponent::render() const
{
    if (!_visible || !_sfTextComponent.has_value()) {
        PRETTY_INFO << "Instance is hidden or no sfImage instance found, not rendering" << std::endl;
        return std::nullopt;
    }
    return std::make_any<sf::Text>(_sfTextComponent.value());
};

void GUI::ECS::Components::TextComponent::update(const GUI::ECS::Systems::MouseInfo &mouse)
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
        PRETTY_INFO << "No known instance of sf::Text, creating." << std::endl;
        if (_font.getFontPath().empty()) {
            PRETTY_WARNING << "No font, skipping update." << std::endl;
            return;
        }

        PRETTY_DEBUG << "Fetching the font" << std::endl;
        std::any systemFont = _font.getFontInstance();
        PRETTY_DEBUG << "Font package received, checking that it is not empty." << std::endl;
        if (!systemFont.has_value()) {
            PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
                << "No font found in the provided system font." << std::endl;
            throw CustomExceptions::NoFont("<There is no sf::Font instance to apply>");
        }
        PRETTY_DEBUG << "Font instance has content, unpacking" << std::endl;
        std::string errorMsg = "<There is no sf::Font instance to manipulate>, system error: ";
        std::optional<std::shared_ptr<sf::Font>> fontCapsule = Utilities::unCast<std::shared_ptr<sf::Font>, CustomExceptions::NoFont>(systemFont, true, errorMsg);
        PRETTY_DEBUG << "Font unpacked successfully into an std::optional, checking std::optional." << std::endl;
        if (!fontCapsule.has_value()) {
            PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
                << "Failed to cast sf::Font from system font, anycast failed." << std::endl;
            throw CustomExceptions::NoFont(errorMsg);
        }
        PRETTY_DEBUG << "std::optional has content, unpacking" << std::endl;
        const std::shared_ptr<sf::Font> font = fontCapsule.value();
        PRETTY_DEBUG << "std::optional unpacked successfully into an sf::Font" << std::endl;
        PRETTY_SUCCESS << "Font unpacked successfully" << std::endl;
        if (_sfTextComponent.has_value()) {
            PRETTY_DEBUG << "An instance of sf::Text already exists, updating it's font." << std::endl;
            _sfTextComponent->setFont(*font);
        } else {
            PRETTY_DEBUG << "No instance of sf::Text, creating a new one." << std::endl;
            sf::Text node(*font, _text, _size);
            _sfTextComponent = node;
            _textAltered = false;
        }
        PRETTY_DEBUG << "Checking that the font is still present" << std::endl;
        const sf::Font fontTest = _sfTextComponent->getFont();
        const sf::Texture fontTexture = fontTest.getTexture(30);
        if (fontTexture.getSize().x > 0 && fontTexture.getSize().y > 0) {
            PRETTY_SUCCESS << "Font loaded and has a valid texture!" << std::endl;
        } else {
            PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
                << "Font loaded, but no valid texture found!" << std::endl;
        }
        PRETTY_DEBUG << "Text component updated." << std::endl;
        _fontChanged = false;

    }
}

void GUI::ECS::Components::TextComponent::_loadFont()
{
    if (!_font.isLoaded()) {
        std::string msg = "Font name : '" + _font.getFontName() + "' (not found) in '" + _font.getFontPath() + "'";
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << msg << std::endl;
        throw CustomExceptions::NoFont(msg);
    }
    if (!_sfTextComponent.has_value()) {
        PRETTY_INFO << "Text not initialised, initialising..." << std::endl;
        _initialiseText();
    }
    PRETTY_DEBUG << "Fetching the font" << std::endl;
    std::any systemFont = _font.getFontInstance();
    PRETTY_DEBUG << "Font package received, checking that it is not empty." << std::endl;
    if (!systemFont.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "No font found in the provided system font." << std::endl;
        throw CustomExceptions::NoFont("<There is no sf::Font instance to apply>");
    }
    PRETTY_DEBUG << "Font instance has content, unpacking" << std::endl;
    std::string errorMsg = "<There is no sf::Font instance to manipulate>, system error: ";
    std::optional<std::shared_ptr<sf::Font>> fontCapsule = Utilities::unCast<std::shared_ptr<sf::Font>, CustomExceptions::NoFont>(systemFont, true, errorMsg);
    PRETTY_DEBUG << "Font unpacked successfully into an std::optional, checking std::optional." << std::endl;
    if (!fontCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "Failed to cast sf::Font from system font, anycast failed." << std::endl;
        throw CustomExceptions::NoFont(errorMsg);
    }
    PRETTY_DEBUG << "std::optional has content, unpacking" << std::endl;
    const std::shared_ptr<sf::Font> font = fontCapsule.value();
    PRETTY_DEBUG << "std::optional unpacked successfully into an sf::Font, applying font to sf::Text" << std::endl;
    _sfTextComponent->setFont(*font);
    PRETTY_DEBUG << "Font applied to sf::Text, text component updated." << std::endl;
    PRETTY_DEBUG << "Checking that the font is still present" << std::endl;
    const sf::Font fontTest = _sfTextComponent->getFont();
    const sf::Texture fontTexture = fontTest.getTexture(30);
    if (fontTexture.getSize().x > 0 && fontTexture.getSize().y > 0) {
        PRETTY_SUCCESS << "Font loaded and has a valid texture!" << std::endl;
    } else {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "Font loaded, but no valid texture found!" << std::endl;
    }

}

void GUI::ECS::Components::TextComponent::_processTextComponent()
{
    PRETTY_INFO << "Checking initiailisation" << std::endl;
    _initialiseText();
    if (_sfTextComponent.has_value()) {
        if (_fontChanged) {
            PRETTY_DEBUG << "Going to update the font." << std::endl;
            _loadFont();
            _fontChanged = false;
            _fontAltered = true;
        }
        if (_textAltered) {
            PRETTY_DEBUG << "Going to update the text." << std::endl;
            _sfTextComponent->setString(_text);
            _textAltered = false;
            _fontAltered = true;
            PRETTY_DEBUG << "Text Updated" << std::endl;
        }
        if (_sizeAltered) {
            PRETTY_DEBUG << "Going to update the font size" << std::endl;
            _sfTextComponent->setCharacterSize(_size);
            _sizeAltered = false;
            _fontAltered = true;
        }
        if (_positionAltered) {
            PRETTY_DEBUG << "Going to check the position" << std::endl;
            std::pair<float, float> pos = _textPos.getPosition();
            _sfTextComponent->setPosition({ pos.first, pos.second });
            _positionAltered = false;
            _fontAltered = true;
        }
        if (_fontAltered) {
            PRETTY_DEBUG << "Going to update the font" << std::endl;
            PRETTY_DEBUG << "Text component has a value" << std::endl;
            const sf::Font font = _sfTextComponent->getFont();
            const sf::Texture fontTexture = font.getTexture(30);
            if (fontTexture.getSize().x > 0 && fontTexture.getSize().y > 0) {
                PRETTY_SUCCESS << "Font loaded and has a valid texture!" << std::endl;
            } else {
                PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
                    << "Font loaded, but no valid texture found!" << std::endl;
            }
            sf::FloatRect textBounds = _sfTextComponent->getLocalBounds();
            PRETTY_DEBUG << "Text bounds gathered." << std::endl;
            _textPos.setDimension({ textBounds.size.x, textBounds.size.y });
            PRETTY_DEBUG << "Text position updated." << std::endl;
            _fontAltered = false;
        }
    } else {
        PRETTY_WARNING << "No text component value to be managed" << std::endl;
    }
    PRETTY_INFO << "Font loaded, updating text colour" << std::endl;
    std::any systemColour;
    if (_textPos.isClicked()) {
        systemColour = _clickedColor.getRenderColour();
    } else if (_textPos.isHovered()) {
        systemColour = _hoverColor.getRenderColour();
    } else {
        systemColour = _color.getRenderColour();
    }
    if (!systemColour.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "No color value to be managed" << std::endl;
        throw CustomExceptions::NoColour("<There was no content returned by getRenderColour when std::any (containing sf::Font was expected)>");
    }
    std::string errMsg = "<The content returned by the getRenderColour function is not of type sf::Color>, system error: ";
    std::optional<sf::Color> colourCapsule = Utilities::unCast<sf::Color, CustomExceptions::NoColour>(systemColour, true, errMsg);
    PRETTY_DEBUG << "Colour capsule gathered, checking integrity" << std::endl;
    if (!colourCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "Colour capsule is empty" << std::endl;
        throw CustomExceptions::NoColour(errMsg);
    }
    PRETTY_DEBUG << "Colour capsule is valid, updating text colour" << std::endl;
    sf::Color result = colourCapsule.value();
    _sfTextComponent->setFillColor(result);
    PRECISE_SUCCESS << "Text colour updated" << std::endl;
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
