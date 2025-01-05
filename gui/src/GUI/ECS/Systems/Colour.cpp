/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Color.cpp
*/

#include "GUI/ECS/Systems/Colour.hpp"

GUI::ECS::Systems::Colour::Colour() : EntityNode(0) {};

GUI::ECS::Systems::Colour::Colour(const GUI::ECS::Systems::Colour &copy)
    : EntityNode(copy.getEntityNodeId())
{
    update(copy);
};

GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId)
    : EntityNode(entityId)
{
};

GUI::ECS::Systems::Colour::Colour(const std::uint32_t colour, const std::string &name)
    : EntityNode(0)
{
    setColour(colour, name);
}

GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId, const Colour &copy)
    : EntityNode(entityId)
{
    update(copy);
};

GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId, const std::uint32_t color, const std::string &name)
    : EntityNode(entityId)
{
    setColour(color, name);
};

GUI::ECS::Systems::Colour::Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue)
    : EntityNode(0)
{
    setColour(red, green, blue);
};

GUI::ECS::Systems::Colour::Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::string &name)
    : EntityNode(0)
{
    setColour(red, green, blue, name);
};

GUI::ECS::Systems::Colour::Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
    : EntityNode(0)
{
    setColour(red, green, blue, alpha);
};

GUI::ECS::Systems::Colour::Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name)
    : EntityNode(0)
{
    setColour(red, green, blue, alpha, name);
};

GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue)
    : EntityNode(entityId)
{
    setColour(red, green, blue);
};


GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
    : EntityNode(entityId)
{
    setColour(red, green, blue, alpha);
};

GUI::ECS::Systems::Colour::Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name)
    : EntityNode(entityId)
{
    setColour(red, green, blue, alpha, name);
};

void GUI::ECS::Systems::Colour::setName(const std::string &name)
{
    _colourName = name;
}

void GUI::ECS::Systems::Colour::setColour(const std::uint32_t color)
{
    _red = (color >> 24) & 0xFF;
    _green = (color >> 16) & 0xFF;
    _blue = (color >> 8) & 0xFF;
    _alpha = color & 0xFF;
};

void GUI::ECS::Systems::Colour::setColour(const std::uint32_t color, const std::string &name)
{
    setName(name);
    setColour(color);
};

void GUI::ECS::Systems::Colour::setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue)
{
    _red = red;
    _green = green;
    _blue = blue;
};

void GUI::ECS::Systems::Colour::setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::string &name)
{
    setName(name);
    setColour(red, green, blue);
};

void GUI::ECS::Systems::Colour::setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
};

void GUI::ECS::Systems::Colour::setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name)
{
    setName(name);
    setColour(red, green, blue, alpha);
};

void GUI::ECS::Systems::Colour::setRed(const std::uint8_t red)
{
    _red = red;
};

void GUI::ECS::Systems::Colour::setBlue(const std::uint8_t blue)
{
    _blue = blue;
};

void GUI::ECS::Systems::Colour::setGreen(const std::uint8_t green)
{
    _green = green;
};

void GUI::ECS::Systems::Colour::setAlpha(const std::uint8_t alpha)
{
    _alpha = alpha;
};

const std::uint32_t GUI::ECS::Systems::Colour::toInteger() const
{
    std::uint32_t result = (static_cast<std::uint32_t>(_red) << 24) |
        (static_cast<std::uint32_t>(_green) << 16) |
        (static_cast<std::uint32_t>(_blue) << 8) |
        (static_cast<std::uint32_t>(_alpha));
    return result;
};

const std::any GUI::ECS::Systems::Colour::toRenderColour() const
{
    return std::any(sf::Color(_red, _green, _blue, _alpha));
};

void GUI::ECS::Systems::Colour::update(const GUI::ECS::Systems::Colour &copy)
{
    setRed(copy.getRed());
    setGreen(copy.getGreen());
    setBlue(copy.getBlue());
    setAlpha(copy.getAlpha());
    setName(copy.getName());
};

void GUI::ECS::Systems::Colour::update(const std::uint32_t color)
{
    setColour(color);
};

const std::uint8_t GUI::ECS::Systems::Colour::getRed() const
{
    return _red;
};

const std::uint8_t GUI::ECS::Systems::Colour::getBlue() const
{
    return _blue;
};

const std::uint8_t GUI::ECS::Systems::Colour::getGreen() const
{
    return _green;
};

const std::uint8_t GUI::ECS::Systems::Colour::getAlpha() const
{
    return _alpha;
};

const std::uint32_t GUI::ECS::Systems::Colour::getColour() const
{
    return toInteger();
};

const std::uint32_t GUI::ECS::Systems::Colour::getInteger() const
{
    return toInteger();
}

const std::any GUI::ECS::Systems::Colour::getRenderColour() const
{
    return toRenderColour();
};

const std::string GUI::ECS::Systems::Colour::getName() const
{
    return _colourName;
};


const std::string GUI::ECS::Systems::Colour::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Colour:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Colour Name: " + getName() + "\n";
    result += indentation + "- Red: " + Recoded::myToString(getRed()) + "\n";
    result += indentation + "- Green: " + Recoded::myToString(getGreen()) + "\n";
    result += indentation + "- Blue: " + Recoded::myToString(getBlue()) + "\n";
    result += indentation + "- Alpha: " + Recoded::myToString(getAlpha()) + "\n";
    return result;
};

const std::uint8_t GUI::ECS::Systems::Colour::clamp(std::int32_t value, std::uint8_t min, std::uint8_t max)
{
    std::int32_t clampedValue = std::max(static_cast<std::int32_t>(min), std::min(static_cast<std::int32_t>(max), value));
    return static_cast<std::uint8_t>(clampedValue);
}

GUI::ECS::Systems::Colour &GUI::ECS::Systems::Colour::operator =(const GUI::ECS::Systems::Colour &copy)
{
    update(copy);
    return *this;
};

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Colour &colour)
{
    os << colour.getInfo();
    return os;
}

[[nodiscard]] const bool GUI::ECS::Systems::operator==(GUI::ECS::Systems::Colour left, GUI::ECS::Systems::Colour right)
{
    return left.getInteger() == right.getInteger();
};

[[nodiscard]] const bool GUI::ECS::Systems::operator!=(GUI::ECS::Systems::Colour left, GUI::ECS::Systems::Colour right)
{
    return !(left.getInteger() == right.getInteger());
};

[[nodiscard]] const GUI::ECS::Systems::Colour GUI::ECS::Systems::operator+(GUI::ECS::Systems::Colour left, GUI::ECS::Systems::Colour right)
{
    return GUI::ECS::Systems::Colour(
        GUI::ECS::Systems::Colour::clamp(left.getRed() + right.getRed()),
        GUI::ECS::Systems::Colour::clamp(left.getGreen() + right.getGreen()),
        GUI::ECS::Systems::Colour::clamp(left.getBlue() + right.getBlue()),
        GUI::ECS::Systems::Colour::clamp(left.getAlpha() + right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Systems::Colour GUI::ECS::Systems::operator-(GUI::ECS::Systems::Colour left, GUI::ECS::Systems::Colour right)
{
    return GUI::ECS::Systems::Colour(
        GUI::ECS::Systems::Colour::clamp(left.getRed() - right.getRed()),
        GUI::ECS::Systems::Colour::clamp(left.getGreen() - right.getGreen()),
        GUI::ECS::Systems::Colour::clamp(left.getBlue() - right.getBlue()),
        GUI::ECS::Systems::Colour::clamp(left.getAlpha() - right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Systems::Colour GUI::ECS::Systems::operator*(GUI::ECS::Systems::Colour left, GUI::ECS::Systems::Colour right)
{
    return GUI::ECS::Systems::Colour(
        GUI::ECS::Systems::Colour::clamp(left.getRed() * right.getRed()),
        GUI::ECS::Systems::Colour::clamp(left.getGreen() * right.getGreen()),
        GUI::ECS::Systems::Colour::clamp(left.getBlue() * right.getBlue()),
        GUI::ECS::Systems::Colour::clamp(left.getAlpha() * right.getAlpha())
    );
};

const GUI::ECS::Systems::Colour &GUI::ECS::Systems::operator+=(GUI::ECS::Systems::Colour &left, GUI::ECS::Systems::Colour right)
{
    left.setRed(GUI::ECS::Systems::Colour::clamp(left.getRed() + right.getRed()));
    left.setGreen(GUI::ECS::Systems::Colour::clamp(left.getGreen() + right.getGreen()));
    left.setBlue(GUI::ECS::Systems::Colour::clamp(left.getBlue() + right.getBlue()));
    left.setAlpha(GUI::ECS::Systems::Colour::clamp(left.getAlpha() + right.getAlpha()));
    return left;
};

const GUI::ECS::Systems::Colour &GUI::ECS::Systems::operator-=(GUI::ECS::Systems::Colour &left, GUI::ECS::Systems::Colour right)
{
    left.setRed(GUI::ECS::Systems::Colour::clamp(left.getRed() - right.getRed()));
    left.setGreen(GUI::ECS::Systems::Colour::clamp(left.getGreen() - right.getGreen()));
    left.setBlue(GUI::ECS::Systems::Colour::clamp(left.getBlue() - right.getBlue()));
    left.setAlpha(GUI::ECS::Systems::Colour::clamp(left.getAlpha() - right.getAlpha()));
    return left;
};

const GUI::ECS::Systems::Colour &GUI::ECS::Systems::operator*=(GUI::ECS::Systems::Colour &left, GUI::ECS::Systems::Colour right)
{
    left.setRed(GUI::ECS::Systems::Colour::clamp(left.getRed() * right.getRed()));
    left.setGreen(GUI::ECS::Systems::Colour::clamp(left.getGreen() * right.getGreen()));
    left.setBlue(GUI::ECS::Systems::Colour::clamp(left.getBlue() * right.getBlue()));
    left.setAlpha(GUI::ECS::Systems::Colour::clamp(left.getAlpha() * right.getAlpha()));
    return left;
};

// Colour definition
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Snow(255, 250, 250, "Snow");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Snow1(255, 250, 250, "Snow1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Snow2(238, 233, 233, "Snow2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RosyBrown1(255, 193, 193, "RosyBrown1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RosyBrown2(238, 180, 180, "RosyBrown2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Snow3(205, 201, 201, "Snow3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCoral(240, 128, 128, "LightCoral");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::IndianRed1(255, 106, 106, "IndianRed1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RosyBrown3(205, 155, 155, "RosyBrown3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::IndianRed2(238, 99, 99, "IndianRed2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RosyBrown(188, 143, 143, "RosyBrown");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Brown1(255, 64, 64, "Brown1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Firebrick1(255, 48, 48, "Firebrick1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Brown2(238, 59, 59, "Brown2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::IndianRed(205, 92, 92, "IndianRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::IndianRed3(205, 85, 85, "IndianRed3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Firebrick2(238, 44, 44, "Firebrick2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Snow4(139, 137, 137, "Snow4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Brown3(205, 51, 51, "Brown3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Red(255, 0, 0, "Red");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Red1(255, 0, 0, "Red1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RosyBrown4(139, 105, 105, "RosyBrown4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Firebrick3(205, 38, 38, "Firebrick3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Red2(238, 0, 0, "Red2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Firebrick(178, 34, 34, "Firebrick");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Brown(165, 42, 42, "Brown");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Red3(205, 0, 0, "Red3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::IndianRed4(139, 58, 58, "IndianRed4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Brown4(139, 35, 35, "Brown4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Firebrick4(139, 26, 26, "Firebrick4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkRed(139, 0, 0, "DarkRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Red4(139, 0, 0, "Red4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon(128, 0, 0, "Maroon");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightPink1(255, 174, 185, "LightPink1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightPink3(205, 140, 149, "LightPink3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightPink4(139, 95, 101, "LightPink4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightPink2(238, 162, 173, "LightPink2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightPink(255, 182, 193, "LightPink");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Pink(255, 192, 203, "Pink");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Crimson(220, 20, 60, "Crimson");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Pink1(255, 181, 197, "Pink1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Pink2(238, 169, 184, "Pink2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Pink3(205, 145, 158, "Pink3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Pink4(139, 99, 108, "Pink4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleVioletRed4(139, 71, 93, "PaleVioletRed4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleVioletRed(219, 112, 147, "PaleVioletRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleVioletRed2(238, 121, 159, "PaleVioletRed2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleVioletRed1(255, 130, 171, "PaleVioletRed1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleVioletRed3(205, 104, 137, "PaleVioletRed3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LavenderBlush(255, 240, 245, "LavenderBlush");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LavenderBlush1(255, 240, 245, "LavenderBlush1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LavenderBlush3(205, 193, 197, "LavenderBlush3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LavenderBlush2(238, 224, 229, "LavenderBlush2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LavenderBlush4(139, 131, 134, "LavenderBlush4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon5(176, 48, 96, "Maroon5");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::HotPink3(205, 96, 144, "HotPink3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::VioletRed3(205, 50, 120, "VioletRed3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::VioletRed1(255, 62, 150, "VioletRed1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::VioletRed2(238, 58, 140, "VioletRed2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::VioletRed4(139, 34, 82, "VioletRed4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::HotPink2(238, 106, 167, "HotPink2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::HotPink1(255, 110, 180, "HotPink1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::HotPink4(139, 58, 98, "HotPink4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::HotPink(255, 105, 180, "HotPink");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepPink(255, 20, 147, "DeepPink");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepPink1(255, 20, 147, "DeepPink1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepPink2(238, 18, 137, "DeepPink2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepPink3(205, 16, 118, "DeepPink3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepPink4(139, 10, 80, "DeepPink4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon1(255, 52, 179, "Maroon1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon2(238, 48, 167, "Maroon2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon3(205, 41, 144, "Maroon3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Maroon4(139, 28, 98, "Maroon4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumVioletRed(199, 21, 133, "MediumVioletRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::VioletRed(208, 32, 144, "VioletRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orchid2(238, 122, 233, "Orchid2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orchid(218, 112, 214, "Orchid");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orchid1(255, 131, 250, "Orchid1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orchid3(205, 105, 201, "Orchid3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orchid4(139, 71, 137, "Orchid4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Thistle1(255, 225, 255, "Thistle1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Thistle2(238, 210, 238, "Thistle2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Plum1(255, 187, 255, "Plum1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Plum2(238, 174, 238, "Plum2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Thistle(216, 191, 216, "Thistle");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Thistle3(205, 181, 205, "Thistle3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Plum(221, 160, 221, "Plum");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Violet(238, 130, 238, "Violet");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Plum3(205, 150, 205, "Plum3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Thistle4(139, 123, 139, "Thistle4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Fuchsia(255, 0, 255, "Fuchsia");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Magenta(255, 0, 255, "Magenta");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Magenta1(255, 0, 255, "Magenta1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Plum4(139, 102, 139, "Plum4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Magenta2(238, 0, 238, "Magenta2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Magenta3(205, 0, 205, "Magenta3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkMagenta(139, 0, 139, "DarkMagenta");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Magenta4(139, 0, 139, "Magenta4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple(128, 0, 128, "Purple");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumOrchid(186, 85, 211, "MediumOrchid");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumOrchid1(224, 102, 255, "MediumOrchid1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumOrchid2(209, 95, 238, "MediumOrchid2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumOrchid3(180, 82, 205, "MediumOrchid3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumOrchid4(122, 55, 139, "MediumOrchid4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkViolet(148, 0, 211, "DarkViolet");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrchid(153, 50, 204, "DarkOrchid");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrchid1(191, 62, 255, "DarkOrchid1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrchid3(154, 50, 205, "DarkOrchid3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrchid2(178, 58, 238, "DarkOrchid2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrchid4(104, 34, 139, "DarkOrchid4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple5(160, 32, 240, "Purple");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Indigo(75, 0, 130, "Indigo");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::BlueViolet(138, 43, 226, "BlueViolet");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple2(145, 44, 238, "Purple2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple3(125, 38, 205, "Purple3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple4(85, 26, 139, "Purple4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Purple1(155, 48, 255, "Purple1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumPurple(147, 112, 219, "MediumPurple");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumPurple1(171, 130, 255, "MediumPurple1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumPurple2(159, 121, 238, "MediumPurple2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumPurple3(137, 104, 205, "MediumPurple3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumPurple4(93, 71, 139, "MediumPurple4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateBlue(72, 61, 139, "DarkSlateBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSlateBlue(132, 112, 255, "LightSlateBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumSlateBlue(123, 104, 238, "MediumSlateBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateBlue(106, 90, 205, "SlateBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateBlue1(131, 111, 255, "SlateBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateBlue2(122, 103, 238, "SlateBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateBlue3(105, 89, 205, "SlateBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateBlue4(71, 60, 139, "SlateBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::GhostWhite(248, 248, 255, "GhostWhite");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Lavender(230, 230, 250, "Lavender");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Blue(0, 0, 255, "Blue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Blue1(0, 0, 255, "Blue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Blue2(0, 0, 238, "Blue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Blue3(0, 0, 205, "Blue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumBlue(0, 0, 205, "MediumBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Blue4(0, 0, 139, "Blue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkBlue(0, 0, 139, "DarkBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MidnightBlue(25, 25, 112, "MidnightBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Navy(0, 0, 128, "Navy");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavyBlue(0, 0, 128, "NavyBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RoyalBlue(65, 105, 225, "RoyalBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RoyalBlue1(72, 118, 255, "RoyalBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RoyalBlue2(67, 110, 238, "RoyalBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RoyalBlue3(58, 95, 205, "RoyalBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::RoyalBlue4(39, 64, 139, "RoyalBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CornflowerBlue(100, 149, 237, "CornflowerBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSteelBlue(176, 196, 222, "LightSteelBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSteelBlue1(202, 225, 255, "LightSteelBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSteelBlue2(188, 210, 238, "LightSteelBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSteelBlue3(162, 181, 205, "LightSteelBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSteelBlue4(110, 123, 139, "LightSteelBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGray4(108, 123, 139, "SlateGray4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGray1(198, 226, 255, "SlateGray1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGray2(185, 211, 238, "SlateGray2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGray3(159, 182, 205, "SlateGray3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSlateGray(119, 136, 153, "LightSlateGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSlateGrey(119, 136, 153, "LightSlateGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGray(112, 128, 144, "SlateGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SlateGrey(112, 128, 144, "SlateGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DodgerBlue(30, 144, 255, "DodgerBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DodgerBlue1(30, 144, 255, "DodgerBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DodgerBlue2(28, 134, 238, "DodgerBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DodgerBlue4(16, 78, 139, "DodgerBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DodgerBlue3(24, 116, 205, "DodgerBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AliceBlue(240, 248, 255, "AliceBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SteelBlue4(54, 100, 139, "SteelBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SteelBlue(70, 130, 180, "SteelBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SteelBlue1(99, 184, 255, "SteelBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SteelBlue2(92, 172, 238, "SteelBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SteelBlue3(79, 148, 205, "SteelBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SkyBlue4(74, 112, 139, "SkyBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SkyBlue1(135, 206, 255, "SkyBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SkyBlue2(126, 192, 238, "SkyBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SkyBlue3(108, 166, 205, "SkyBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSkyBlue(135, 206, 250, "LightSkyBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSkyBlue4(96, 123, 139, "LightSkyBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSkyBlue1(176, 226, 255, "LightSkyBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSkyBlue2(164, 211, 238, "LightSkyBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSkyBlue3(141, 182, 205, "LightSkyBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SkyBlue(135, 206, 235, "SkyBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightBlue3(154, 192, 205, "LightBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepSkyBlue(0, 191, 255, "DeepSkyBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepSkyBlue1(0, 191, 255, "DeepSkyBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepSkyBlue2(0, 178, 238, "DeepSkyBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepSkyBlue4(0, 104, 139, "DeepSkyBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DeepSkyBlue3(0, 154, 205, "DeepSkyBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightBlue1(191, 239, 255, "LightBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightBlue2(178, 223, 238, "LightBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightBlue(173, 216, 230, "LightBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightBlue4(104, 131, 139, "LightBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PowderBlue(176, 224, 230, "PowderBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CadetBlue1(152, 245, 255, "CadetBlue1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CadetBlue2(142, 229, 238, "CadetBlue2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CadetBlue3(122, 197, 205, "CadetBlue3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CadetBlue4(83, 134, 139, "CadetBlue4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Turquoise1(0, 245, 255, "Turquoise1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Turquoise2(0, 229, 238, "Turquoise2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Turquoise3(0, 197, 205, "Turquoise3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Turquoise4(0, 134, 139, "Turquoise4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::CadetBlue(95, 158, 160, "CadetBlue");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkTurquoise(0, 206, 209, "DarkTurquoise");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Azure(240, 255, 255, "Azure");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Azure1(240, 255, 255, "Azure1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCyan(224, 255, 255, "LightCyan");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCyan1(224, 255, 255, "LightCyan1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Azure2(224, 238, 238, "Azure2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCyan2(209, 238, 238, "LightCyan2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleTurquoise1(187, 255, 255, "PaleTurquoise1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleTurquoise(175, 238, 238, "PaleTurquoise");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleTurquoise2(174, 238, 238, "PaleTurquoise2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGray1(151, 255, 255, "DarkSlateGray1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Azure3(193, 205, 205, "Azure3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCyan3(180, 205, 205, "LightCyan3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGray2(141, 238, 238, "DarkSlateGray2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleTurquoise3(150, 205, 205, "PaleTurquoise3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGray3(121, 205, 205, "DarkSlateGray3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Azure4(131, 139, 139, "Azure4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightCyan4(122, 139, 139, "LightCyan4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aqua(0, 255, 255, "Aqua");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cyan(0, 255, 255, "Cyan");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cyan1(0, 255, 255, "Cyan1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleTurquoise4(102, 139, 139, "PaleTurquoise4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cyan2(0, 238, 238, "Cyan2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGray4(82, 139, 139, "DarkSlateGray4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cyan3(0, 205, 205, "Cyan3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cyan4(0, 139, 139, "Cyan4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkCyan(0, 139, 139, "DarkCyan");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Teal(0, 128, 128, "Teal");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGray(47, 79, 79, "DarkSlateGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSlateGrey(47, 79, 79, "DarkSlateGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumTurquoise(72, 209, 204, "MediumTurquoise");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSeaGreen(32, 178, 170, "LightSeaGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Turquoise(64, 224, 208, "Turquoise");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aquamarine4(69, 139, 116, "Aquamarine4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aquamarine(127, 255, 212, "Aquamarine");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aquamarine1(127, 255, 212, "Aquamarine1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aquamarine2(118, 238, 198, "Aquamarine2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Aquamarine3(102, 205, 170, "Aquamarine3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumAquamarine(102, 205, 170, "MediumAquamarine");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumSpringGreen(0, 250, 154, "MediumSpringGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MintCream(245, 255, 250, "MintCream");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SpringGreen(0, 255, 127, "SpringGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SpringGreen1(0, 255, 127, "SpringGreen1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SpringGreen2(0, 238, 118, "SpringGreen2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SpringGreen3(0, 205, 102, "SpringGreen3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SpringGreen4(0, 139, 69, "SpringGreen4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumSeaGreen(60, 179, 113, "MediumSeaGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SeaGreen(46, 139, 87, "SeaGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SeaGreen3(67, 205, 128, "SeaGreen3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SeaGreen1(84, 255, 159, "SeaGreen1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SeaGreen4(46, 139, 87, "SeaGreen4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SeaGreen2(78, 238, 148, "SeaGreen2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumForestGreen(50, 129, 75, "MediumForestGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Honeydew(240, 255, 240, "Honeydew");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Honeydew1(240, 255, 240, "Honeydew1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Honeydew2(224, 238, 224, "Honeydew2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSeaGreen1(193, 255, 193, "DarkSeaGreen1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSeaGreen2(180, 238, 180, "DarkSeaGreen2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGreen1(154, 255, 154, "PaleGreen1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGreen(152, 251, 152, "PaleGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Honeydew3(193, 205, 193, "Honeydew3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGreen(144, 238, 144, "LightGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGreen2(144, 238, 144, "PaleGreen2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSeaGreen3(155, 205, 155, "DarkSeaGreen3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSeaGreen(143, 188, 143, "DarkSeaGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGreen3(124, 205, 124, "PaleGreen3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Honeydew4(131, 139, 131, "Honeydew4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Green1(0, 255, 0, "Green1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Lime(0, 255, 0, "Lime");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LimeGreen(50, 205, 50, "LimeGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSeaGreen4(105, 139, 105, "DarkSeaGreen4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Green2(0, 238, 0, "Green2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGreen4(84, 139, 84, "PaleGreen4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Green3(0, 205, 0, "Green3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::ForestGreen(34, 139, 34, "ForestGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Green4(0, 139, 0, "Green4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Green(0, 128, 0, "Green");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGreen(0, 100, 0, "DarkGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LawnGreen(124, 252, 0, "LawnGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chartreuse(127, 255, 0, "Chartreuse");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chartreuse1(127, 255, 0, "Chartreuse1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chartreuse2(118, 238, 0, "Chartreuse2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chartreuse3(102, 205, 0, "Chartreuse3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chartreuse4(69, 139, 0, "Chartreuse4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::GreenYellow(173, 255, 47, "GreenYellow");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOliveGreen3(162, 205, 90, "DarkOliveGreen3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOliveGreen1(202, 255, 112, "DarkOliveGreen1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOliveGreen2(188, 238, 104, "DarkOliveGreen2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOliveGreen4(110, 139, 61, "DarkOliveGreen4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOliveGreen(85, 107, 47, "DarkOliveGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OliveDrab(107, 142, 35, "OliveDrab");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OliveDrab1(192, 255, 62, "OliveDrab1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OliveDrab2(179, 238, 58, "OliveDrab2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OliveDrab3(154, 205, 50, "OliveDrab3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::YellowGreen(154, 205, 50, "YellowGreen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OliveDrab4(105, 139, 34, "OliveDrab4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Ivory(255, 255, 240, "Ivory");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Ivory1(255, 255, 240, "Ivory1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightYellow(255, 255, 224, "LightYellow");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightYellow1(255, 255, 224, "LightYellow1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Beige(245, 245, 220, "Beige");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Ivory2(238, 238, 224, "Ivory2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrodYellow(250, 250, 210, "LightGoldenrodYellow");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightYellow2(238, 238, 209, "LightYellow2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Ivory3(205, 205, 193, "Ivory3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightYellow3(205, 205, 180, "LightYellow3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Ivory4(139, 139, 131, "Ivory4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightYellow4(139, 139, 122, "LightYellow4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Yellow(255, 255, 0, "Yellow");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Yellow1(255, 255, 0, "Yellow1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Yellow2(238, 238, 0, "Yellow2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Yellow3(205, 205, 0, "Yellow3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Yellow4(139, 139, 0, "Yellow4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Olive(128, 128, 0, "Olive");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkKhaki(189, 183, 107, "DarkKhaki");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Khaki2(238, 230, 133, "Khaki2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LemonChiffon4(139, 137, 112, "LemonChiffon4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Khaki1(255, 246, 143, "Khaki1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Khaki3(205, 198, 115, "Khaki3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Khaki4(139, 134, 78, "Khaki4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PaleGoldenrod(238, 232, 170, "PaleGoldenrod");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LemonChiffon(255, 250, 205, "LemonChiffon");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LemonChiffon1(255, 250, 205, "LemonChiffon1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Khaki(240, 230, 140, "Khaki");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LemonChiffon3(205, 201, 165, "LemonChiffon3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LemonChiffon2(238, 233, 191, "LemonChiffon2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MediumGoldenRod(209, 193, 102, "MediumGoldenRod");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cornsilk4(139, 136, 120, "Cornsilk4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gold(255, 215, 0, "Gold");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gold1(255, 215, 0, "Gold1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gold2(238, 201, 0, "Gold2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gold3(205, 173, 0, "Gold3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gold4(139, 117, 0, "Gold4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrod(238, 221, 130, "LightGoldenrod");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrod4(139, 129, 76, "LightGoldenrod4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrod1(255, 236, 139, "LightGoldenrod1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrod3(205, 190, 112, "LightGoldenrod3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGoldenrod2(238, 220, 130, "LightGoldenrod2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cornsilk3(205, 200, 177, "Cornsilk3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cornsilk2(238, 232, 205, "Cornsilk2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cornsilk(255, 248, 220, "Cornsilk");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Cornsilk1(255, 248, 220, "Cornsilk1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Goldenrod(218, 165, 32, "Goldenrod");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Goldenrod1(255, 193, 37, "Goldenrod1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Goldenrod2(238, 180, 34, "Goldenrod2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Goldenrod3(205, 155, 29, "Goldenrod3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Goldenrod4(139, 105, 20, "Goldenrod4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGoldenrod(184, 134, 11, "DarkGoldenrod");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGoldenrod1(255, 185, 15, "DarkGoldenrod1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGoldenrod2(238, 173, 14, "DarkGoldenrod2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGoldenrod3(205, 149, 12, "DarkGoldenrod3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGoldenrod4(139, 101, 8, "DarkGoldenrod4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::FloralWhite(255, 250, 240, "FloralWhite");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Wheat2(238, 216, 174, "Wheat2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OldLace(253, 245, 230, "OldLace");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Wheat(245, 222, 179, "Wheat");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Wheat1(255, 231, 186, "Wheat1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Wheat3(205, 186, 150, "Wheat3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orange(255, 165, 0, "Orange");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orange1(255, 165, 0, "Orange1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orange2(238, 154, 0, "Orange2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orange3(205, 133, 0, "Orange3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Orange4(139, 90, 0, "Orange4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Wheat4(139, 126, 102, "Wheat4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Moccasin(255, 228, 181, "Moccasin");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PapayaWhip(255, 239, 213, "PapayaWhip");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavajoWhite3(205, 179, 139, "NavajoWhite3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::BlanchedAlmond(255, 235, 205, "BlanchedAlmond");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavajoWhite(255, 222, 173, "NavajoWhite");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavajoWhite1(255, 222, 173, "NavajoWhite1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavajoWhite2(238, 207, 161, "NavajoWhite2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::NavajoWhite4(139, 121, 94, "NavajoWhite4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AntiqueWhite4(139, 131, 120, "AntiqueWhite4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AntiqueWhite(250, 235, 215, "AntiqueWhite");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tan(210, 180, 140, "Tan");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Bisque4(139, 125, 107, "Bisque4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Burlywood(222, 184, 135, "Burlywood");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AntiqueWhite2(238, 223, 204, "AntiqueWhite2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Burlywood1(255, 211, 155, "Burlywood1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Burlywood3(205, 170, 125, "Burlywood3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Burlywood2(238, 197, 145, "Burlywood2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AntiqueWhite1(255, 239, 219, "AntiqueWhite1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Burlywood4(139, 115, 85, "Burlywood4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::AntiqueWhite3(205, 192, 176, "AntiqueWhite3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrange(255, 140, 0, "DarkOrange");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Bisque2(238, 213, 183, "Bisque2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Bisque(255, 228, 196, "Bisque");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Bisque1(255, 228, 196, "Bisque1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Bisque3(205, 183, 158, "Bisque3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrange1(255, 127, 0, "DarkOrange1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Linen(250, 240, 230, "Linen");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrange2(238, 118, 0, "DarkOrange2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrange3(205, 102, 0, "DarkOrange3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkOrange4(139, 69, 0, "DarkOrange4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Peru(205, 133, 63, "Peru");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tan1(255, 165, 79, "Tan1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tan2(238, 154, 73, "Tan2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tan3(205, 133, 63, "Tan3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tan4(139, 90, 43, "Tan4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PeachPuff(255, 218, 185, "PeachPuff");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PeachPuff1(255, 218, 185, "PeachPuff1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PeachPuff4(139, 119, 101, "PeachPuff4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PeachPuff2(238, 203, 173, "PeachPuff2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::PeachPuff3(205, 175, 149, "PeachPuff3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SandyBrown(244, 164, 96, "SandyBrown");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Seashell4(139, 134, 130, "Seashell4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Seashell2(238, 229, 222, "Seashell2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Seashell3(205, 197, 191, "Seashell3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chocolate(210, 105, 30, "Chocolate");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chocolate1(255, 127, 36, "Chocolate1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chocolate2(238, 118, 33, "Chocolate2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chocolate3(205, 102, 29, "Chocolate3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Chocolate4(139, 69, 19, "Chocolate4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::SaddleBrown(139, 69, 19, "SaddleBrown");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Seashell(255, 245, 238, "Seashell");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Seashell1(255, 245, 238, "Seashell1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Sienna4(139, 71, 38, "Sienna4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Sienna(160, 82, 45, "Sienna");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Sienna1(255, 130, 71, "Sienna1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Sienna2(238, 121, 66, "Sienna2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Sienna3(205, 104, 57, "Sienna3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSalmon3(205, 129, 98, "LightSalmon3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSalmon(255, 160, 122, "LightSalmon");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSalmon1(255, 160, 122, "LightSalmon1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSalmon4(139, 87, 66, "LightSalmon4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightSalmon2(238, 149, 114, "LightSalmon2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Coral(255, 127, 80, "Coral");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OrangeRed(255, 69, 0, "OrangeRed");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OrangeRed1(255, 69, 0, "OrangeRed1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OrangeRed2(238, 64, 0, "OrangeRed2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OrangeRed3(205, 55, 0, "OrangeRed3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::OrangeRed4(139, 37, 0, "OrangeRed4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkSalmon(233, 150, 122, "DarkSalmon");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Salmon1(255, 140, 105, "Salmon1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Salmon2(238, 130, 98, "Salmon2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Salmon3(205, 112, 84, "Salmon3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Salmon4(139, 76, 57, "Salmon4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Coral1(255, 114, 86, "Coral1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Coral2(238, 106, 80, "Coral2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Coral3(205, 91, 69, "Coral3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Coral4(139, 62, 47, "Coral4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tomato4(139, 54, 38, "Tomato4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tomato(255, 99, 71, "Tomato");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tomato1(255, 99, 71, "Tomato1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tomato2(238, 92, 66, "Tomato2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Tomato3(205, 79, 57, "Tomato3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MistyRose4(139, 125, 123, "MistyRose4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MistyRose2(238, 213, 210, "MistyRose2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MistyRose(255, 228, 225, "MistyRose");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MistyRose1(255, 228, 225, "MistyRose1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Salmon(250, 128, 114, "Salmon");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::MistyRose3(205, 183, 181, "MistyRose3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::White(255, 255, 255, 255, "White");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray100(255, 255, 255, "Gray100");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey100(255, 255, 255, "Grey100");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray99(252, 252, 252, "Gray99");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey99(252, 252, 252, "Grey99");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray98(250, 250, 250, "Gray98");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey98(250, 250, 250, "Grey98");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray97(247, 247, 247, "Gray97");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey97(247, 247, 247, "Grey97");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray96(245, 245, 245, "Gray96");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey96(245, 245, 245, "Grey96");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::WhiteSmoke(245, 245, 245, "WhiteSmoke");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray95(242, 242, 242, "Gray95");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey95(242, 242, 242, "Grey95");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray94(240, 240, 240, "Gray94");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey94(240, 240, 240, "Grey94");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray93(237, 237, 237, "Gray93");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey93(237, 237, 237, "Grey93");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray92(235, 235, 235, "Gray92");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey92(235, 235, 235, "Grey92");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray91(232, 232, 232, "Gray91");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey91(232, 232, 232, "Grey91");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray90(229, 229, 229, "Gray90");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey90(229, 229, 229, "Grey90");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray89(227, 227, 227, "Gray89");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey89(227, 227, 227, "Grey89");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray88(224, 224, 224, "Gray88");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey88(224, 224, 224, "Grey88");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray87(222, 222, 222, "Gray87");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey87(222, 222, 222, "Grey87");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gainsboro(220, 220, 220, "Gainsboro");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray86(219, 219, 219, "Gray86");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey86(219, 219, 219, "Grey86");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray85(217, 217, 217, "Gray85");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey85(217, 217, 217, "Grey85");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray84(214, 214, 214, "Gray84");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey84(214, 214, 214, "Grey84");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray83(212, 212, 212, "Gray83");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey83(212, 212, 212, "Grey83");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGray(211, 211, 211, "LightGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::LightGrey(211, 211, 211, "LightGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray82(209, 209, 209, "Gray82");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey82(209, 209, 209, "Grey82");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray81(207, 207, 207, "Gray81");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey81(207, 207, 207, "Grey81");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray80(204, 204, 204, "Gray80");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey80(204, 204, 204, "Grey80");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray79(201, 201, 201, "Gray79");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey79(201, 201, 201, "Grey79");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray78(199, 199, 199, "Gray78");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey78(199, 199, 199, "Grey78");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray77(196, 196, 196, "Gray77");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey77(196, 196, 196, "Grey77");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray76(194, 194, 194, "Gray76");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey76(194, 194, 194, "Grey76");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Silver(192, 192, 192, "Silver");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray75(191, 191, 191, "Gray75");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey75(191, 191, 191, "Grey75");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray74(189, 189, 189, "Gray74");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey74(189, 189, 189, "Grey74");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray73(186, 186, 186, "Gray73");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey73(186, 186, 186, "Grey73");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray72(184, 184, 184, "Gray72");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey72(184, 184, 184, "Grey72");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray71(181, 181, 181, "Gray71");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey71(181, 181, 181, "Grey71");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray70(179, 179, 179, "Gray70");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey70(179, 179, 179, "Grey70");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray69(176, 176, 176, "Gray69");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey69(176, 176, 176, "Grey69");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray68(173, 173, 173, "Gray68");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey68(173, 173, 173, "Grey68");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray67(171, 171, 171, "Gray67");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey67(171, 171, 171, "Grey67");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGray(169, 169, 169, "DarkGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DarkGrey(169, 169, 169, "DarkGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray66(168, 168, 168, "Gray66");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey66(168, 168, 168, "Grey66");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray65(166, 166, 166, "Gray65");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey65(166, 166, 166, "Grey65");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray64(163, 163, 163, "Gray64");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey64(163, 163, 163, "Grey64");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray63(161, 161, 161, "Gray63");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey63(161, 161, 161, "Grey63");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray62(158, 158, 158, "Gray62");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey62(158, 158, 158, "Grey62");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray61(156, 156, 156, "Gray61");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey61(156, 156, 156, "Grey61");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray60(153, 153, 153, "Gray60");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey60(153, 153, 153, "Grey60");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray59(150, 150, 150, "Gray59");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey59(150, 150, 150, "Grey59");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray58(148, 148, 148, "Gray58");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey58(148, 148, 148, "Grey58");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray57(145, 145, 145, "Gray57");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey57(145, 145, 145, "Grey57");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray56(143, 143, 143, "Gray56");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey56(143, 143, 143, "Grey56");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray55(140, 140, 140, "Gray55");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey55(140, 140, 140, "Grey55");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray54(138, 138, 138, "Gray54");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey54(138, 138, 138, "Grey54");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray53(135, 135, 135, "Gray53");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey53(135, 135, 135, "Grey53");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray52(133, 133, 133, "Gray52");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey52(133, 133, 133, "Grey52");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray51(130, 130, 130, "Gray51");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey51(130, 130, 130, "Grey51");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Fractal(128, 128, 128, "Fractal");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray50(127, 127, 127, "Gray50");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey50(127, 127, 127, "Grey50");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray(126, 126, 126, "Gray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray49(125, 125, 125, "Gray49");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey49(125, 125, 125, "Grey49");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray48(122, 122, 122, "Gray48");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey48(122, 122, 122, "Grey48");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray47(120, 120, 120, "Gray47");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey47(120, 120, 120, "Grey47");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray46(117, 117, 117, "Gray46");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey46(117, 117, 117, "Grey46");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray45(115, 115, 115, "Gray45");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey45(115, 115, 115, "Grey45");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray44(112, 112, 112, "Gray44");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey44(112, 112, 112, "Grey44");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray43(110, 110, 110, "Gray43");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey43(110, 110, 110, "Grey43");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray42(107, 107, 107, "Gray42");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey42(107, 107, 107, "Grey42");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DimGray(105, 105, 105, "DimGray");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::DimGrey(105, 105, 105, "DimGrey");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray41(105, 105, 105, "Gray41");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey41(105, 105, 105, "Grey41");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray40(102, 102, 102, "Gray40");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey40(102, 102, 102, "Grey40");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray39(99, 99, 99, "Gray39");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey39(99, 99, 99, "Grey39");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray38(97, 97, 97, "Gray38");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey38(97, 97, 97, "Grey38");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray37(94, 94, 94, "Gray37");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey37(94, 94, 94, "Grey37");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray36(92, 92, 92, "Gray36");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey36(92, 92, 92, "Grey36");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray35(89, 89, 89, "Gray35");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey35(89, 89, 89, "Grey35");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray34(87, 87, 87, "Gray34");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey34(87, 87, 87, "Grey34");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray33(84, 84, 84, "Gray33");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey33(84, 84, 84, "Grey33");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray32(82, 82, 82, "Gray32");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey32(82, 82, 82, "Grey32");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray31(79, 79, 79, "Gray31");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey31(79, 79, 79, "Grey31");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray30(77, 77, 77, "Gray30");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey30(77, 77, 77, "Grey30");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray29(74, 74, 74, "Gray29");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey29(74, 74, 74, "Grey29");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray28(71, 71, 71, "Gray28");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey28(71, 71, 71, "Grey28");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray27(69, 69, 69, "Gray27");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey27(69, 69, 69, "Grey27");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray26(66, 66, 66, "Gray26");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey26(66, 66, 66, "Grey26");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray25(64, 64, 64, "Gray25");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey25(64, 64, 64, "Grey25");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray24(61, 61, 61, "Gray24");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey24(61, 61, 61, "Grey24");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray23(59, 59, 59, "Gray23");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey23(59, 59, 59, "Grey23");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray22(56, 56, 56, "Gray22");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey22(56, 56, 56, "Grey22");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray21(54, 54, 54, "Gray21");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey21(54, 54, 54, "Grey21");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray20(51, 51, 51, "Gray20");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey20(51, 51, 51, "Grey20");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray19(48, 48, 48, "Gray19");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey19(48, 48, 48, "Grey19");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray18(46, 46, 46, "Gray18");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey18(46, 46, 46, "Grey18");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray17(43, 43, 43, "Gray17");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey17(43, 43, 43, "Grey17");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray16(41, 41, 41, "Gray16");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey16(41, 41, 41, "Grey16");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray15(38, 38, 38, "Gray15");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey15(38, 38, 38, "Grey15");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray14(36, 36, 36, "Gray14");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey14(36, 36, 36, "Grey14");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray13(33, 33, 33, "Gray13");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey13(33, 33, 33, "Grey13");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray12(31, 31, 31, "Gray12");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey12(31, 31, 31, "Grey12");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray11(28, 28, 28, "Gray11");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey11(28, 28, 28, "Grey11");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray10(26, 26, 26, "Gray10");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey10(26, 26, 26, "Grey10");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray9(23, 23, 23, "Gray9");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey9(23, 23, 23, "Grey9");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray8(20, 20, 20, "Gray8");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey8(20, 20, 20, "Grey8");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray7(18, 18, 18, "Gray7");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey7(18, 18, 18, "Grey7");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray6(15, 15, 15, "Gray6");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey6(15, 15, 15, "Grey6");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray5(13, 13, 13, "Gray5");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey5(13, 13, 13, "Grey5");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray4(10, 10, 10, "Gray4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey4(10, 10, 10, "Grey4");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray3(8, 8, 8, "Gray3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey3(8, 8, 8, "Grey3");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray2(5, 5, 5, "Gray2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey2(5, 5, 5, "Grey2");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray1(3, 3, 3, "Gray1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey1(3, 3, 3, "Grey1");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Black(0, 0, 0, "Black");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Gray0(0, 0, 0, "Gray0");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Grey0(0, 0, 0, "Grey0");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Opaque(0, 0, 0, "Opaque");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::None(0, 0, 0, 0, "None");
const GUI::ECS::Systems::Colour GUI::ECS::Systems::Colour::Transparent(0, 0, 0, 0, "Transparent");
