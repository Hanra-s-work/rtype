/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Color.cpp
*/

#include "GUI/ECS/Utilities/Colour.hpp"

GUI::ECS::Utilities::Colour::Colour() : EntityNode(0) {};

GUI::ECS::Utilities::Colour::Colour(GUI::ECS::Utilities::Colour &copy)
    : EntityNode(copy.getEntityNodeId())
{
    update(copy);
};

GUI::ECS::Utilities::Colour::Colour(const std::uint32_t entityId)
    : EntityNode(entityId)
{
};

GUI::ECS::Utilities::Colour::Colour(const std::uint32_t entityId, Colour &copy)
    : EntityNode(entityId)
{
    update(copy);
};

GUI::ECS::Utilities::Colour::Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
    : EntityNode(0)
{
    setColour(red, green, blue, alpha);
};

GUI::ECS::Utilities::Colour::Colour(const std::uint32_t entityId, const std::uint32_t color)
    : EntityNode(entityId)
{
    setColour(color);
};

GUI::ECS::Utilities::Colour::Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
    : EntityNode(entityId)
{
    setColour(red, green, blue, alpha);
};

void GUI::ECS::Utilities::Colour::setColour(const std::uint32_t color)
{
    _red = (color >> 24) & 0xFF;
    _green = (color >> 16) & 0xFF;
    _blue = (color >> 8) & 0xFF;
    _alpha = color & 0xFF;
};

void GUI::ECS::Utilities::Colour::setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
};

void GUI::ECS::Utilities::Colour::setRed(const std::uint8_t red)
{
    _red = red;
};

void GUI::ECS::Utilities::Colour::setBlue(const std::uint8_t blue)
{
    _blue = blue;
};

void GUI::ECS::Utilities::Colour::setGreen(const std::uint8_t green)
{
    _green = green;
};

void GUI::ECS::Utilities::Colour::setAlpha(const std::uint8_t alpha)
{
    _alpha = alpha;
};

const std::uint32_t GUI::ECS::Utilities::Colour::toInteger() const
{
    std::uint32_t result = (static_cast<std::uint32_t>(_red) << 24) |
        (static_cast<std::uint32_t>(_green) << 16) |
        (static_cast<std::uint32_t>(_blue) << 8) |
        (static_cast<std::uint32_t>(_alpha));
    return result;
};

const sf::Color GUI::ECS::Utilities::Colour::toSFMLColour() const
{
    sf::Color node(_red, _green, _blue, _alpha);
    return node;
};

void GUI::ECS::Utilities::Colour::update(const GUI::ECS::Utilities::Colour &copy)
{
    setRed(copy.getRed());
    setGreen(copy.getGreen());
    setBlue(copy.getBlue());
    setAlpha(copy.getAlpha());
};

void GUI::ECS::Utilities::Colour::update(const std::uint32_t color)
{
    setColour(color);
};

const std::uint8_t GUI::ECS::Utilities::Colour::getRed() const
{
    return _red;
};

const std::uint8_t GUI::ECS::Utilities::Colour::getBlue() const
{
    return _blue;
};

const std::uint8_t GUI::ECS::Utilities::Colour::getGreen() const
{
    return _green;
};

const std::uint8_t GUI::ECS::Utilities::Colour::getAlpha() const
{
    return _alpha;
};

const std::uint32_t GUI::ECS::Utilities::Colour::getColour() const
{
    return toInteger();
};

const std::uint32_t GUI::ECS::Utilities::Colour::getInteger() const
{
    return toInteger();
}

const sf::Color GUI::ECS::Utilities::Colour::getColourSFML() const
{
    return toSFMLColour();
};


const std::string GUI::ECS::Utilities::Colour::getInfo() const
{
    std::string result = "The vales of this colour are: ";
    result += "Red: " + std::to_string(getRed()) + ", ";
    result += "Green: " + std::to_string(getGreen()) + ", ";
    result += "Blue: " + std::to_string(getBlue()) + ", ";
    result += "Alpha: " + std::to_string(getAlpha());
    return result;
};

const std::uint8_t GUI::ECS::Utilities::Colour::clamp(std::int32_t value, std::uint8_t min, std::uint8_t max)
{
    std::int32_t clampedValue = std::max(static_cast<std::int32_t>(min), std::min(static_cast<std::int32_t>(max), value));
    return static_cast<std::uint8_t>(clampedValue);
}

std::ostream &operator<<(std::ostream &os, const GUI::ECS::Utilities::Colour &colour)
{
    os << colour.getInfo();
    return os;
}

[[nodiscard]] const bool operator==(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return left.getInteger() == right.getInteger();
};

[[nodiscard]] const bool operator!=(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return !(left.getInteger() == right.getInteger());
};

[[nodiscard]] const GUI::ECS::Utilities::Colour operator+(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() + right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() + right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() + right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() + right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Utilities::Colour operator-(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() - right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() - right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() - right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() - right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Utilities::Colour operator*(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() * right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() * right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() * right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() * right.getAlpha())
    );
};

const GUI::ECS::Utilities::Colour &operator+=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() + right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() + right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() + right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() + right.getAlpha()));
    return left;
};

const GUI::ECS::Utilities::Colour &operator-=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() - right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() - right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() - right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() - right.getAlpha()));
    return left;
};

const GUI::ECS::Utilities::Colour &operator*=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() * right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() * right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() * right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() * right.getAlpha()));
    return left;
};
