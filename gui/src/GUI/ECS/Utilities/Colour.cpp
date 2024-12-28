/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Color.cpp
*/

#include "GUI/ECS/Utilities/Colour.hpp"

GUI::ECS::Utilities::Colour::Colour() : EntityNode(0) {};

GUI::ECS::Utilities::Colour::Colour(const GUI::ECS::Utilities::Colour &copy)
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


const std::string GUI::ECS::Utilities::Colour::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Colour:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += "Red: " + MyRecodes::myToString(getRed()) + ", ";
    result += "Green: " + MyRecodes::myToString(getGreen()) + ", ";
    result += "Blue: " + MyRecodes::myToString(getBlue()) + ", ";
    result += "Alpha: " + MyRecodes::myToString(getAlpha());
    return result;
};

const std::uint8_t GUI::ECS::Utilities::Colour::clamp(std::int32_t value, std::uint8_t min, std::uint8_t max)
{
    std::int32_t clampedValue = std::max(static_cast<std::int32_t>(min), std::min(static_cast<std::int32_t>(max), value));
    return static_cast<std::uint8_t>(clampedValue);
}

GUI::ECS::Utilities::Colour &GUI::ECS::Utilities::Colour::operator =(const GUI::ECS::Utilities::Colour &copy)
{
    update(copy);
    return *this;
};

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::Colour &colour)
{
    os << colour.getInfo();
    return os;
}

[[nodiscard]] const bool GUI::ECS::Utilities::operator==(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return left.getInteger() == right.getInteger();
};

[[nodiscard]] const bool GUI::ECS::Utilities::operator!=(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return !(left.getInteger() == right.getInteger());
};

[[nodiscard]] const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::operator+(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() + right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() + right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() + right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() + right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::operator-(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() - right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() - right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() - right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() - right.getAlpha())
    );
};

[[nodiscard]] const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::operator*(GUI::ECS::Utilities::Colour left, GUI::ECS::Utilities::Colour right)
{
    return GUI::ECS::Utilities::Colour(
        GUI::ECS::Utilities::Colour::clamp(left.getRed() * right.getRed()),
        GUI::ECS::Utilities::Colour::clamp(left.getGreen() * right.getGreen()),
        GUI::ECS::Utilities::Colour::clamp(left.getBlue() * right.getBlue()),
        GUI::ECS::Utilities::Colour::clamp(left.getAlpha() * right.getAlpha())
    );
};

const GUI::ECS::Utilities::Colour &GUI::ECS::Utilities::operator+=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() + right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() + right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() + right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() + right.getAlpha()));
    return left;
};

const GUI::ECS::Utilities::Colour &GUI::ECS::Utilities::operator-=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() - right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() - right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() - right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() - right.getAlpha()));
    return left;
};

const GUI::ECS::Utilities::Colour &GUI::ECS::Utilities::operator*=(GUI::ECS::Utilities::Colour &left, GUI::ECS::Utilities::Colour right)
{
    left.setRed(GUI::ECS::Utilities::Colour::clamp(left.getRed() * right.getRed()));
    left.setGreen(GUI::ECS::Utilities::Colour::clamp(left.getGreen() * right.getGreen()));
    left.setBlue(GUI::ECS::Utilities::Colour::clamp(left.getBlue() * right.getBlue()));
    left.setAlpha(GUI::ECS::Utilities::Colour::clamp(left.getAlpha() * right.getAlpha()));
    return left;
};

// Colour definition
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Snow(255, 250, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Snow1(255, 250, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Snow2(238, 233, 233);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RosyBrown1(255, 193, 193);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RosyBrown2(238, 180, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Snow3(205, 201, 201);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCoral(240, 128, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::IndianRed1(255, 106, 106);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RosyBrown3(205, 155, 155);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::IndianRed2(238, 99, 99);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RosyBrown(188, 143, 143);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Brown1(255, 64, 64);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Firebrick1(255, 48, 48);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Brown2(238, 59, 59);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::IndianRed(205, 92, 92);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::IndianRed3(205, 85, 85);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Firebrick2(238, 44, 44);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Snow4(139, 137, 137);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Brown3(205, 51, 51);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Red(255, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Red1(255, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RosyBrown4(139, 105, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Firebrick3(205, 38, 38);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Red2(238, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Firebrick(178, 34, 34);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Brown(165, 42, 42);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Red3(205, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::IndianRed4(139, 58, 58);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Brown4(139, 35, 35);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Firebrick4(139, 26, 26);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkRed(139, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Red4(139, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Maroon(128, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightPink1(255, 174, 185);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightPink3(205, 140, 149);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightPink4(139, 95, 101);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightPink2(238, 162, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightPink(255, 182, 193);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Pink(255, 192, 203);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Crimson(220, 20, 60);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Pink1(255, 181, 197);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Pink2(238, 169, 184);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Pink3(205, 145, 158);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Pink4(139, 99, 108);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleVioletRed4(139, 71, 93);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleVioletRed(219, 112, 147);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleVioletRed2(238, 121, 159);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleVioletRed1(255, 130, 171);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleVioletRed3(205, 104, 137);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LavenderBlush(255, 240, 245);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LavenderBlush1(255, 240, 245);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LavenderBlush3(205, 193, 197);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LavenderBlush2(238, 224, 229);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LavenderBlush4(139, 131, 134);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::HotPink3(205, 96, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::VioletRed3(205, 50, 120);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::VioletRed1(255, 62, 150);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::VioletRed2(238, 58, 140);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::VioletRed4(139, 34, 82);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::HotPink2(238, 106, 167);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::HotPink1(255, 110, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::HotPink4(139, 58, 98);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::HotPink(255, 105, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepPink(255, 20, 147);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepPink1(255, 20, 147);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepPink2(238, 18, 137);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepPink3(205, 16, 118);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepPink4(139, 10, 80);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Maroon1(255, 52, 179);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Maroon2(238, 48, 167);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Maroon3(205, 41, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Maroon4(139, 28, 98);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumVioletRed(199, 21, 133);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::VioletRed(208, 32, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orchid2(238, 122, 233);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orchid(218, 112, 214);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orchid1(255, 131, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orchid3(205, 105, 201);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orchid4(139, 71, 137);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Thistle1(255, 225, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Thistle2(238, 210, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Plum1(255, 187, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Plum2(238, 174, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Thistle(216, 191, 216);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Thistle3(205, 181, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Plum(221, 160, 221);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Violet(238, 130, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Plum3(205, 150, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Thistle4(139, 123, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Fuchsia(255, 0, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Magenta(255, 0, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Magenta1(255, 0, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Plum4(139, 102, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Magenta2(238, 0, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Magenta3(205, 0, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkMagenta(139, 0, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Magenta4(139, 0, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple(128, 0, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumOrchid(186, 85, 211);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumOrchid1(224, 102, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumOrchid2(209, 95, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumOrchid3(180, 82, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumOrchid4(122, 55, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkViolet(148, 0, 211);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrchid(153, 50, 204);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrchid1(191, 62, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrchid3(154, 50, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrchid2(178, 58, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrchid4(104, 34, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple5(160, 32, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Indigo(75, 0, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::BlueViolet(138, 43, 226);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple2(145, 44, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple3(125, 38, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple4(85, 26, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Purple1(155, 48, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumPurple(147, 112, 219);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumPurple1(171, 130, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumPurple2(159, 121, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumPurple3(137, 104, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumPurple4(93, 71, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateBlue(72, 61, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSlateBlue(132, 112, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumSlateBlue(123, 104, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateBlue(106, 90, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateBlue1(131, 111, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateBlue2(122, 103, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateBlue3(105, 89, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateBlue4(71, 60, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::GhostWhite(248, 248, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Lavender(230, 230, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Blue(0, 0, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Blue1(0, 0, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Blue2(0, 0, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Blue3(0, 0, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumBlue(0, 0, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Blue4(0, 0, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkBlue(0, 0, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MidnightBlue(25, 25, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Navy(0, 0, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavyBlue(0, 0, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RoyalBlue(65, 105, 225);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RoyalBlue1(72, 118, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RoyalBlue2(67, 110, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RoyalBlue3(58, 95, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::RoyalBlue4(39, 64, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CornflowerBlue(100, 149, 237);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSteelBlue(176, 196, 222);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSteelBlue1(202, 225, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSteelBlue2(188, 210, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSteelBlue3(162, 181, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSteelBlue4(110, 123, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGray4(108, 123, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGray1(198, 226, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGray2(185, 211, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGray3(159, 182, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSlateGray(119, 136, 153);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSlateGrey(119, 136, 153);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGray(112, 128, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SlateGrey(112, 128, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DodgerBlue(30, 144, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DodgerBlue1(30, 144, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DodgerBlue2(28, 134, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DodgerBlue4(16, 78, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DodgerBlue3(24, 116, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AliceBlue(240, 248, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SteelBlue4(54, 100, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SteelBlue(70, 130, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SteelBlue1(99, 184, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SteelBlue2(92, 172, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SteelBlue3(79, 148, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SkyBlue4(74, 112, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SkyBlue1(135, 206, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SkyBlue2(126, 192, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SkyBlue3(108, 166, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSkyBlue(135, 206, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSkyBlue4(96, 123, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSkyBlue1(176, 226, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSkyBlue2(164, 211, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSkyBlue3(141, 182, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SkyBlue(135, 206, 235);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightBlue3(154, 192, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepSkyBlue(0, 191, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepSkyBlue1(0, 191, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepSkyBlue2(0, 178, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepSkyBlue4(0, 104, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DeepSkyBlue3(0, 154, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightBlue1(191, 239, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightBlue2(178, 223, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightBlue(173, 216, 230);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightBlue4(104, 131, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PowderBlue(176, 224, 230);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CadetBlue1(152, 245, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CadetBlue2(142, 229, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CadetBlue3(122, 197, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CadetBlue4(83, 134, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Turquoise1(0, 245, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Turquoise2(0, 229, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Turquoise3(0, 197, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Turquoise4(0, 134, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::CadetBlue(95, 158, 160);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkTurquoise(0, 206, 209);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Azure(240, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Azure1(240, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCyan(224, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCyan1(224, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Azure2(224, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCyan2(209, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleTurquoise1(187, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleTurquoise(175, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleTurquoise2(174, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGray1(151, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Azure3(193, 205, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCyan3(180, 205, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGray2(141, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleTurquoise3(150, 205, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGray3(121, 205, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Azure4(131, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightCyan4(122, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aqua(0, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cyan(0, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cyan1(0, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleTurquoise4(102, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cyan2(0, 238, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGray4(82, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cyan3(0, 205, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cyan4(0, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkCyan(0, 139, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Teal(0, 128, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGray(47, 79, 79);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSlateGrey(47, 79, 79);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumTurquoise(72, 209, 204);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSeaGreen(32, 178, 170);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Turquoise(64, 224, 208);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aquamarine4(69, 139, 116);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aquamarine(127, 255, 212);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aquamarine1(127, 255, 212);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aquamarine2(118, 238, 198);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Aquamarine3(102, 205, 170);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumAquamarine(102, 205, 170);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumSpringGreen(0, 250, 154);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MintCream(245, 255, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SpringGreen(0, 255, 127);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SpringGreen1(0, 255, 127);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SpringGreen2(0, 238, 118);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SpringGreen3(0, 205, 102);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SpringGreen4(0, 139, 69);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumSeaGreen(60, 179, 113);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SeaGreen(46, 139, 87);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SeaGreen3(67, 205, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SeaGreen1(84, 255, 159);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SeaGreen4(46, 139, 87);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SeaGreen2(78, 238, 148);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumForestGreen(50, 129, 75);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Honeydew(240, 255, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Honeydew1(240, 255, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Honeydew2(224, 238, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSeaGreen1(193, 255, 193);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSeaGreen2(180, 238, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGreen1(154, 255, 154);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGreen(152, 251, 152);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Honeydew3(193, 205, 193);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGreen(144, 238, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGreen2(144, 238, 144);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSeaGreen3(155, 205, 155);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSeaGreen(143, 188, 143);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGreen3(124, 205, 124);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Honeydew4(131, 139, 131);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Green1(0, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Lime(0, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LimeGreen(50, 205, 50);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSeaGreen4(105, 139, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Green2(0, 238, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGreen4(84, 139, 84);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Green3(0, 205, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::ForestGreen(34, 139, 34);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Green4(0, 139, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Green(0, 128, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGreen(0, 100, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LawnGreen(124, 252, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chartreuse(127, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chartreuse1(127, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chartreuse2(118, 238, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chartreuse3(102, 205, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chartreuse4(69, 139, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::GreenYellow(173, 255, 47);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOliveGreen3(162, 205, 90);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOliveGreen1(202, 255, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOliveGreen2(188, 238, 104);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOliveGreen4(110, 139, 61);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOliveGreen(85, 107, 47);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OliveDrab(107, 142, 35);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OliveDrab1(192, 255, 62);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OliveDrab2(179, 238, 58);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OliveDrab3(154, 205, 50);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::YellowGreen(154, 205, 50);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OliveDrab4(105, 139, 34);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Ivory(255, 255, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Ivory1(255, 255, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightYellow(255, 255, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightYellow1(255, 255, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Beige(245, 245, 220);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Ivory2(238, 238, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrodYellow(250, 250, 210);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightYellow2(238, 238, 209);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Ivory3(205, 205, 193);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightYellow3(205, 205, 180);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Ivory4(139, 139, 131);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightYellow4(139, 139, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Yellow(255, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Yellow1(255, 255, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Yellow2(238, 238, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Yellow3(205, 205, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Yellow4(139, 139, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Olive(128, 128, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkKhaki(189, 183, 107);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Khaki2(238, 230, 133);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LemonChiffon4(139, 137, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Khaki1(255, 246, 143);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Khaki3(205, 198, 115);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Khaki4(139, 134, 78);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PaleGoldenrod(238, 232, 170);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LemonChiffon(255, 250, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LemonChiffon1(255, 250, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Khaki(240, 230, 140);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LemonChiffon3(205, 201, 165);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LemonChiffon2(238, 233, 191);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MediumGoldenRod(209, 193, 102);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cornsilk4(139, 136, 120);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gold(255, 215, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gold1(255, 215, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gold2(238, 201, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gold3(205, 173, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gold4(139, 117, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrod(238, 221, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrod4(139, 129, 76);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrod1(255, 236, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrod3(205, 190, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGoldenrod2(238, 220, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cornsilk3(205, 200, 177);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cornsilk2(238, 232, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cornsilk(255, 248, 220);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Cornsilk1(255, 248, 220);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Goldenrod(218, 165, 32);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Goldenrod1(255, 193, 37);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Goldenrod2(238, 180, 34);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Goldenrod3(205, 155, 29);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Goldenrod4(139, 105, 20);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGoldenrod(184, 134, 11);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGoldenrod1(255, 185, 15);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGoldenrod2(238, 173, 14);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGoldenrod3(205, 149, 12);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGoldenrod4(139, 101, 8);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::FloralWhite(255, 250, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Wheat2(238, 216, 174);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OldLace(253, 245, 230);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Wheat(245, 222, 179);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Wheat1(255, 231, 186);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Wheat3(205, 186, 150);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orange(255, 165, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orange1(255, 165, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orange2(238, 154, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orange3(205, 133, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Orange4(139, 90, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Wheat4(139, 126, 102);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Moccasin(255, 228, 181);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PapayaWhip(255, 239, 213);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavajoWhite3(205, 179, 139);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::BlanchedAlmond(255, 235, 205);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavajoWhite(255, 222, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavajoWhite1(255, 222, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavajoWhite2(238, 207, 161);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::NavajoWhite4(139, 121, 94);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AntiqueWhite4(139, 131, 120);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AntiqueWhite(250, 235, 215);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tan(210, 180, 140);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Bisque4(139, 125, 107);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Burlywood(222, 184, 135);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AntiqueWhite2(238, 223, 204);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Burlywood1(255, 211, 155);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Burlywood3(205, 170, 125);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Burlywood2(238, 197, 145);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AntiqueWhite1(255, 239, 219);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Burlywood4(139, 115, 85);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::AntiqueWhite3(205, 192, 176);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrange(255, 140, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Bisque2(238, 213, 183);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Bisque(255, 228, 196);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Bisque1(255, 228, 196);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Bisque3(205, 183, 158);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrange1(255, 127, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Linen(250, 240, 230);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrange2(238, 118, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrange3(205, 102, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkOrange4(139, 69, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Peru(205, 133, 63);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tan1(255, 165, 79);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tan2(238, 154, 73);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tan3(205, 133, 63);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tan4(139, 90, 43);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PeachPuff(255, 218, 185);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PeachPuff1(255, 218, 185);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PeachPuff4(139, 119, 101);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PeachPuff2(238, 203, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::PeachPuff3(205, 175, 149);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SandyBrown(244, 164, 96);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Seashell4(139, 134, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Seashell2(238, 229, 222);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Seashell3(205, 197, 191);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chocolate(210, 105, 30);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chocolate1(255, 127, 36);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chocolate2(238, 118, 33);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chocolate3(205, 102, 29);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Chocolate4(139, 69, 19);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::SaddleBrown(139, 69, 19);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Seashell(255, 245, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Seashell1(255, 245, 238);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Sienna4(139, 71, 38);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Sienna(160, 82, 45);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Sienna1(255, 130, 71);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Sienna2(238, 121, 66);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Sienna3(205, 104, 57);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSalmon3(205, 129, 98);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSalmon(255, 160, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSalmon1(255, 160, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSalmon4(139, 87, 66);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightSalmon2(238, 149, 114);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Coral(255, 127, 80);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OrangeRed(255, 69, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OrangeRed1(255, 69, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OrangeRed2(238, 64, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OrangeRed3(205, 55, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::OrangeRed4(139, 37, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkSalmon(233, 150, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Salmon1(255, 140, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Salmon2(238, 130, 98);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Salmon3(205, 112, 84);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Salmon4(139, 76, 57);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Coral1(255, 114, 86);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Coral2(238, 106, 80);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Coral3(205, 91, 69);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Coral4(139, 62, 47);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tomato4(139, 54, 38);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tomato(255, 99, 71);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tomato1(255, 99, 71);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tomato2(238, 92, 66);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Tomato3(205, 79, 57);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MistyRose4(139, 125, 123);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MistyRose2(238, 213, 210);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MistyRose(255, 228, 225);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MistyRose1(255, 228, 225);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Salmon(250, 128, 114);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::MistyRose3(205, 183, 181);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::White(255, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray100(255, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey100(255, 255, 255);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray99(252, 252, 252);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey99(252, 252, 252);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray98(250, 250, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey98(250, 250, 250);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray97(247, 247, 247);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey97(247, 247, 247);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray96(245, 245, 245);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey96(245, 245, 245);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::WhiteSmoke(245, 245, 245);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray95(242, 242, 242);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey95(242, 242, 242);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray94(240, 240, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey94(240, 240, 240);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray93(237, 237, 237);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey93(237, 237, 237);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray92(235, 235, 235);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey92(235, 235, 235);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray91(232, 232, 232);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey91(232, 232, 232);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray90(229, 229, 229);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey90(229, 229, 229);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray89(227, 227, 227);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey89(227, 227, 227);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray88(224, 224, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey88(224, 224, 224);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray87(222, 222, 222);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey87(222, 222, 222);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gainsboro(220, 220, 220);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray86(219, 219, 219);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey86(219, 219, 219);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray85(217, 217, 217);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey85(217, 217, 217);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray84(214, 214, 214);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey84(214, 214, 214);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray83(212, 212, 212);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey83(212, 212, 212);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGray(211, 211, 211);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::LightGrey(211, 211, 211);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray82(209, 209, 209);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey82(209, 209, 209);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray81(207, 207, 207);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey81(207, 207, 207);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray80(204, 204, 204);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey80(204, 204, 204);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray79(201, 201, 201);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey79(201, 201, 201);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray78(199, 199, 199);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey78(199, 199, 199);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray77(196, 196, 196);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey77(196, 196, 196);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray76(194, 194, 194);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey76(194, 194, 194);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Silver(192, 192, 192);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray75(191, 191, 191);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey75(191, 191, 191);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray74(189, 189, 189);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey74(189, 189, 189);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray73(186, 186, 186);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey73(186, 186, 186);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray72(184, 184, 184);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey72(184, 184, 184);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray71(181, 181, 181);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey71(181, 181, 181);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray70(179, 179, 179);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey70(179, 179, 179);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray69(176, 176, 176);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey69(176, 176, 176);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray68(173, 173, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey68(173, 173, 173);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray67(171, 171, 171);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey67(171, 171, 171);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGray(169, 169, 169);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DarkGrey(169, 169, 169);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray66(168, 168, 168);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey66(168, 168, 168);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray65(166, 166, 166);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey65(166, 166, 166);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray64(163, 163, 163);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey64(163, 163, 163);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray63(161, 161, 161);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey63(161, 161, 161);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray62(158, 158, 158);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey62(158, 158, 158);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray61(156, 156, 156);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey61(156, 156, 156);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray60(153, 153, 153);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey60(153, 153, 153);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray59(150, 150, 150);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey59(150, 150, 150);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray58(148, 148, 148);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey58(148, 148, 148);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray57(145, 145, 145);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey57(145, 145, 145);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray56(143, 143, 143);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey56(143, 143, 143);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray55(140, 140, 140);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey55(140, 140, 140);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray54(138, 138, 138);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey54(138, 138, 138);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray53(135, 135, 135);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey53(135, 135, 135);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray52(133, 133, 133);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey52(133, 133, 133);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray51(130, 130, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey51(130, 130, 130);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Fractal(128, 128, 128);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray50(127, 127, 127);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey50(127, 127, 127);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray(126, 126, 126);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray49(125, 125, 125);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey49(125, 125, 125);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray48(122, 122, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey48(122, 122, 122);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray47(120, 120, 120);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey47(120, 120, 120);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray46(117, 117, 117);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey46(117, 117, 117);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray45(115, 115, 115);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey45(115, 115, 115);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray44(112, 112, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey44(112, 112, 112);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray43(110, 110, 110);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey43(110, 110, 110);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray42(107, 107, 107);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey42(107, 107, 107);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DimGray(105, 105, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::DimGrey(105, 105, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray41(105, 105, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey41(105, 105, 105);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray40(102, 102, 102);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey40(102, 102, 102);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray39(99, 99, 99);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey39(99, 99, 99);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray38(97, 97, 97);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey38(97, 97, 97);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray37(94, 94, 94);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey37(94, 94, 94);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray36(92, 92, 92);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey36(92, 92, 92);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray35(89, 89, 89);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey35(89, 89, 89);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray34(87, 87, 87);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey34(87, 87, 87);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray33(84, 84, 84);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey33(84, 84, 84);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray32(82, 82, 82);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey32(82, 82, 82);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray31(79, 79, 79);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey31(79, 79, 79);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray30(77, 77, 77);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey30(77, 77, 77);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray29(74, 74, 74);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey29(74, 74, 74);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray28(71, 71, 71);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey28(71, 71, 71);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray27(69, 69, 69);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey27(69, 69, 69);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray26(66, 66, 66);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey26(66, 66, 66);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray25(64, 64, 64);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey25(64, 64, 64);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray24(61, 61, 61);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey24(61, 61, 61);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray23(59, 59, 59);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey23(59, 59, 59);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray22(56, 56, 56);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey22(56, 56, 56);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray21(54, 54, 54);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey21(54, 54, 54);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray20(51, 51, 51);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey20(51, 51, 51);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray19(48, 48, 48);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey19(48, 48, 48);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray18(46, 46, 46);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey18(46, 46, 46);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray17(43, 43, 43);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey17(43, 43, 43);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray16(41, 41, 41);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey16(41, 41, 41);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray15(38, 38, 38);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey15(38, 38, 38);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray14(36, 36, 36);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey14(36, 36, 36);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray13(33, 33, 33);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey13(33, 33, 33);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray12(31, 31, 31);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey12(31, 31, 31);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray11(28, 28, 28);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey11(28, 28, 28);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray10(26, 26, 26);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey10(26, 26, 26);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray9(23, 23, 23);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey9(23, 23, 23);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray8(20, 20, 20);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey8(20, 20, 20);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray7(18, 18, 18);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey7(18, 18, 18);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray6(15, 15, 15);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey6(15, 15, 15);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray5(13, 13, 13);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey5(13, 13, 13);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray4(10, 10, 10);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey4(10, 10, 10);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray3(8, 8, 8);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey3(8, 8, 8);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray2(5, 5, 5);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey2(5, 5, 5);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray1(3, 3, 3);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey1(3, 3, 3);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Black(0, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Gray0(0, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Grey0(0, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Opaque(0, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::None(0, 0, 0, 0);
const GUI::ECS::Utilities::Colour GUI::ECS::Utilities::Colour::Transparent(0, 0, 0, 0);
