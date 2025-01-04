/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Color.hpp
*/

/**
 * @file Color.hpp
 * @brief File in charge of storing and providing info about the colour.
 */

#pragma once

#include <any>
#include <cstdint>
#include <algorithm>
#include <SFML/Graphics/Color.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @class Colour
             * @brief A class for representing and manipulating colors using RGBA components.
             * Inherits from `EntityNode` to associate colors with entities in the ECS.
             */
            class Colour : public EntityNode {
                public:
                /**
                 * @brief Default constructor. Initializes a color with black (0, 0, 0, 255).
                 */
                Colour();
                /**
                 * @brief Copy constructor. Creates a color by copying another color.
                 * @param copy The color to copy.
                 */
                Colour(const GUI::ECS::Systems::Colour &copy);
                /**
                 * @brief Constructs a color associated with a specific entity ID.
                 * @param entityId The ID of the entity.
                 */
                Colour(const std::uint32_t entityId);
                /**
                 * @brief Constructs a color associated with a specific entity ID.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint32_t colour, const std::string &name);
                /**
                 * @brief Constructs a color associated with an entity ID and copies properties from another color.
                 * @param entityId The ID of the entity.
                 * @param copy The color to copy.
                 */
                Colour(const std::uint32_t entityId, Colour &copy);
                /**
                 * @brief Constructs a color from a 32-bit integer representation.
                 * @param entityId The ID of the entity.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint32_t entityId, const std::uint32_t color, const std::string &name);
                /**
                 * @brief Constructs a color with specific RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
                /**
                 * @brief Constructs a color with specific RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::string &name);
                /**
                 * @brief Constructs a color with specific RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha);
                /**
                 * @brief Constructs a color with specific RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name);
                /**
                 * @brief Constructs a color with specific RGBA components, associated with an entity ID.
                 * @param entityId The ID of the entity.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 */
                Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
                /**
                 * @brief Constructs a color with specific RGBA components, associated with an entity ID.
                 * @param entityId The ID of the entity.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha);

                /**
                 * @brief Constructs a color with specific RGBA components, associated with an entity ID.
                 * @param entityId The ID of the entity.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name);

                /**
                 * @brief Set the Name of the colour in the class
                 *
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                void setName(const std::string &name);

                /**
                 * @brief Sets the color using a 32-bit integer representation.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 */
                void setColour(const std::uint32_t color);

                /**
                 * @brief Sets the color using a 32-bit integer representation.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                void setColour(const std::uint32_t color, const std::string &name);
                /**
                 * @brief Sets the color using individual RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 */
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
                /**
                 * @brief Sets the color using individual RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha);
                /**
                 * @brief Sets the color using individual RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::string &name);
                /**
                 * @brief Sets the color using individual RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 * @param name The name of the colour (this is a way to make the class mor human readable)
                 */
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha, const std::string &name);
                /**
                 * @brief Sets the red component of the color.
                 * @param red Red component (0-255).
                 */
                void setRed(const std::uint8_t red);
                /**
                 * @brief Sets the blue component of the color.
                 * @param blue Blue component (0-255).
                 */
                void setBlue(const std::uint8_t blue);
                /**
                 * @brief Sets the green component of the color.
                 * @param green Green component (0-255).
                 */
                void setGreen(const std::uint8_t green);
                /**
                 * @brief Sets the alpha (transparency) component of the color.
                 * @param alpha Alpha component (0-255).
                 */
                void setAlpha(const std::uint8_t alpha);

                /**
                 * @brief Retrieves the color as a 32-bit unsigned integer.
                 * @return The color represented as 0xRRGGBBAA.
                 */
                const std::uint32_t toInteger() const;

                /**
                 * @brief Converts the color to an SFML `sf::Color` object (or another similare object format if the rendering library isn't sfml).
                 *
                 * @return The an std::any of the component expected by the rendering library.
                 */
                const std::any toRenderColour() const;

                /**
                 * @brief Updates the color by copying from another `Colour` instance.
                 * @param copy The color to copy.
                 */
                void update(const Colour &copy);
                /**
                 * @brief Updates the color using a 32-bit integer representation.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 */
                void update(const std::uint32_t color);

                /**
                 * @brief Retrieves the red component of the color.
                 * @return The red component (0-255).
                 */
                const std::uint8_t getRed() const;
                /**
                 * @brief Retrieves the blue component of the color.
                 * @return The blue component (0-255).
                 */
                const std::uint8_t getBlue() const;
                /**
                 * @brief Retrieves the green component of the color.
                 * @return The green component (0-255).
                 */
                const std::uint8_t getGreen() const;
                /**
                 * @brief Retrieves the alpha component of the color.
                 * @return The alpha component (0-255).
                 */
                const std::uint8_t getAlpha() const;
                /**
                 * @brief Retrieves the color as a 32-bit integer (0xRRGGBBAA).
                 * @return The color as a 32-bit integer.
                 */
                const std::uint32_t getColour() const;
                /**
                 * @brief Retrieves the color as a 32-bit integer.
                 * Alias for `getColour`.
                 * @return The color as a 32-bit integer.
                 */
                const std::uint32_t getInteger() const;
                /**
                 * @brief Retrieves the color as an SFML `sf::Color` if the sfml library is the underlying library, otherwise, it will be another format.
                 *
                 * @return an std::any of the colour (for sfml, an std::any of sf::Color)
                 */
                const std::any getRenderColour() const;
                /**
                 * @brief Get the Name of the colour contained in the class
                 *
                 * @return const std::string
                 */
                const std::string getName() const;

                /**
                * @brief This is a function meant for debugging purposes
                * It will dump the current state of the variables upon call.
                * It will dump them for itself and any of it's underlying classes
                *
                * @param indent The level to which the class should be indented in the dump.
                * @return const std::string The formatted output.
                */
                const std::string getInfo(const unsigned int indent = 0) const;

                /**
                 * @brief Clamps a value between a minimum and maximum range.
                 * @param value The value to clamp.
                 * @param min The minimum allowable value (default: 0).
                 * @param max The maximum allowable value (default: 255).
                 * @return The clamped value.
                 */
                static const std::uint8_t clamp(std::int32_t value, std::uint8_t min = 0, std::uint8_t max = 255);

                /**
                 * @brief Operator in charge of assigning the content of one colour to another.
                 *
                 * @param copy The colour to copy
                 *
                 * @return GUI::ECS::Systems::Colour& The resulting colour
                 */
                GUI::ECS::Systems::Colour &operator =(const GUI::ECS::Systems::Colour &copy);

                // Supported colours
                static const Colour Snow;
                static const Colour Snow1;
                static const Colour Snow2;
                static const Colour RosyBrown1;
                static const Colour RosyBrown2;
                static const Colour Snow3;
                static const Colour LightCoral;
                static const Colour IndianRed1;
                static const Colour RosyBrown3;
                static const Colour IndianRed2;
                static const Colour RosyBrown;
                static const Colour Brown1;
                static const Colour Firebrick1;
                static const Colour Brown2;
                static const Colour IndianRed;
                static const Colour IndianRed3;
                static const Colour Firebrick2;
                static const Colour Snow4;
                static const Colour Brown3;
                static const Colour Red;
                static const Colour Red1;
                static const Colour RosyBrown4;
                static const Colour Firebrick3;
                static const Colour Red2;
                static const Colour Firebrick;
                static const Colour Brown;
                static const Colour Red3;
                static const Colour IndianRed4;
                static const Colour Brown4;
                static const Colour Firebrick4;
                static const Colour DarkRed;
                static const Colour Red4;
                static const Colour Maroon;
                static const Colour LightPink1;
                static const Colour LightPink3;
                static const Colour LightPink4;
                static const Colour LightPink2;
                static const Colour LightPink;
                static const Colour Pink;
                static const Colour Crimson;
                static const Colour Pink1;
                static const Colour Pink2;
                static const Colour Pink3;
                static const Colour Pink4;
                static const Colour PaleVioletRed4;
                static const Colour PaleVioletRed;
                static const Colour PaleVioletRed2;
                static const Colour PaleVioletRed1;
                static const Colour PaleVioletRed3;
                static const Colour LavenderBlush;
                static const Colour LavenderBlush1;
                static const Colour LavenderBlush3;
                static const Colour LavenderBlush2;
                static const Colour LavenderBlush4;
                static const Colour Maroon5;
                static const Colour HotPink3;
                static const Colour VioletRed3;
                static const Colour VioletRed1;
                static const Colour VioletRed2;
                static const Colour VioletRed4;
                static const Colour HotPink2;
                static const Colour HotPink1;
                static const Colour HotPink4;
                static const Colour HotPink;
                static const Colour DeepPink;
                static const Colour DeepPink1;
                static const Colour DeepPink2;
                static const Colour DeepPink3;
                static const Colour DeepPink4;
                static const Colour Maroon1;
                static const Colour Maroon2;
                static const Colour Maroon3;
                static const Colour Maroon4;
                static const Colour MediumVioletRed;
                static const Colour VioletRed;
                static const Colour Orchid2;
                static const Colour Orchid;
                static const Colour Orchid1;
                static const Colour Orchid3;
                static const Colour Orchid4;
                static const Colour Thistle1;
                static const Colour Thistle2;
                static const Colour Plum1;
                static const Colour Plum2;
                static const Colour Thistle;
                static const Colour Thistle3;
                static const Colour Plum;
                static const Colour Violet;
                static const Colour Plum3;
                static const Colour Thistle4;
                static const Colour Fuchsia;
                static const Colour Magenta;
                static const Colour Magenta1;
                static const Colour Plum4;
                static const Colour Magenta2;
                static const Colour Magenta3;
                static const Colour DarkMagenta;
                static const Colour Magenta4;
                static const Colour Purple;
                static const Colour MediumOrchid;
                static const Colour MediumOrchid1;
                static const Colour MediumOrchid2;
                static const Colour MediumOrchid3;
                static const Colour MediumOrchid4;
                static const Colour DarkViolet;
                static const Colour DarkOrchid;
                static const Colour DarkOrchid1;
                static const Colour DarkOrchid3;
                static const Colour DarkOrchid2;
                static const Colour DarkOrchid4;
                static const Colour Purple5;
                static const Colour Indigo;
                static const Colour BlueViolet;
                static const Colour Purple2;
                static const Colour Purple3;
                static const Colour Purple4;
                static const Colour Purple1;
                static const Colour MediumPurple;
                static const Colour MediumPurple1;
                static const Colour MediumPurple2;
                static const Colour MediumPurple3;
                static const Colour MediumPurple4;
                static const Colour DarkSlateBlue;
                static const Colour LightSlateBlue;
                static const Colour MediumSlateBlue;
                static const Colour SlateBlue;
                static const Colour SlateBlue1;
                static const Colour SlateBlue2;
                static const Colour SlateBlue3;
                static const Colour SlateBlue4;
                static const Colour GhostWhite;
                static const Colour Lavender;
                static const Colour Blue;
                static const Colour Blue1;
                static const Colour Blue2;
                static const Colour Blue3;
                static const Colour MediumBlue;
                static const Colour Blue4;
                static const Colour DarkBlue;
                static const Colour MidnightBlue;
                static const Colour Navy;
                static const Colour NavyBlue;
                static const Colour RoyalBlue;
                static const Colour RoyalBlue1;
                static const Colour RoyalBlue2;
                static const Colour RoyalBlue3;
                static const Colour RoyalBlue4;
                static const Colour CornflowerBlue;
                static const Colour LightSteelBlue;
                static const Colour LightSteelBlue1;
                static const Colour LightSteelBlue2;
                static const Colour LightSteelBlue3;
                static const Colour LightSteelBlue4;
                static const Colour SlateGray4;
                static const Colour SlateGray1;
                static const Colour SlateGray2;
                static const Colour SlateGray3;
                static const Colour LightSlateGray;
                static const Colour LightSlateGrey;
                static const Colour SlateGray;
                static const Colour SlateGrey;
                static const Colour DodgerBlue;
                static const Colour DodgerBlue1;
                static const Colour DodgerBlue2;
                static const Colour DodgerBlue4;
                static const Colour DodgerBlue3;
                static const Colour AliceBlue;
                static const Colour SteelBlue4;
                static const Colour SteelBlue;
                static const Colour SteelBlue1;
                static const Colour SteelBlue2;
                static const Colour SteelBlue3;
                static const Colour SkyBlue4;
                static const Colour SkyBlue1;
                static const Colour SkyBlue2;
                static const Colour SkyBlue3;
                static const Colour LightSkyBlue;
                static const Colour LightSkyBlue4;
                static const Colour LightSkyBlue1;
                static const Colour LightSkyBlue2;
                static const Colour LightSkyBlue3;
                static const Colour SkyBlue;
                static const Colour LightBlue3;
                static const Colour DeepSkyBlue;
                static const Colour DeepSkyBlue1;
                static const Colour DeepSkyBlue2;
                static const Colour DeepSkyBlue4;
                static const Colour DeepSkyBlue3;
                static const Colour LightBlue1;
                static const Colour LightBlue2;
                static const Colour LightBlue;
                static const Colour LightBlue4;
                static const Colour PowderBlue;
                static const Colour CadetBlue1;
                static const Colour CadetBlue2;
                static const Colour CadetBlue3;
                static const Colour CadetBlue4;
                static const Colour Turquoise1;
                static const Colour Turquoise2;
                static const Colour Turquoise3;
                static const Colour Turquoise4;
                static const Colour CadetBlue;
                static const Colour DarkTurquoise;
                static const Colour Azure;
                static const Colour Azure1;
                static const Colour LightCyan;
                static const Colour LightCyan1;
                static const Colour Azure2;
                static const Colour LightCyan2;
                static const Colour PaleTurquoise1;
                static const Colour PaleTurquoise;
                static const Colour PaleTurquoise2;
                static const Colour DarkSlateGray1;
                static const Colour Azure3;
                static const Colour LightCyan3;
                static const Colour DarkSlateGray2;
                static const Colour PaleTurquoise3;
                static const Colour DarkSlateGray3;
                static const Colour Azure4;
                static const Colour LightCyan4;
                static const Colour Aqua;
                static const Colour Cyan;
                static const Colour Cyan1;
                static const Colour PaleTurquoise4;
                static const Colour Cyan2;
                static const Colour DarkSlateGray4;
                static const Colour Cyan3;
                static const Colour Cyan4;
                static const Colour DarkCyan;
                static const Colour Teal;
                static const Colour DarkSlateGray;
                static const Colour DarkSlateGrey;
                static const Colour MediumTurquoise;
                static const Colour LightSeaGreen;
                static const Colour Turquoise;
                static const Colour Aquamarine4;
                static const Colour Aquamarine;
                static const Colour Aquamarine1;
                static const Colour Aquamarine2;
                static const Colour Aquamarine3;
                static const Colour MediumAquamarine;
                static const Colour MediumSpringGreen;
                static const Colour MintCream;
                static const Colour SpringGreen;
                static const Colour SpringGreen1;
                static const Colour SpringGreen2;
                static const Colour SpringGreen3;
                static const Colour SpringGreen4;
                static const Colour MediumSeaGreen;
                static const Colour SeaGreen;
                static const Colour SeaGreen3;
                static const Colour SeaGreen1;
                static const Colour SeaGreen4;
                static const Colour SeaGreen2;
                static const Colour MediumForestGreen;
                static const Colour Honeydew;
                static const Colour Honeydew1;
                static const Colour Honeydew2;
                static const Colour DarkSeaGreen1;
                static const Colour DarkSeaGreen2;
                static const Colour PaleGreen1;
                static const Colour PaleGreen;
                static const Colour Honeydew3;
                static const Colour LightGreen;
                static const Colour PaleGreen2;
                static const Colour DarkSeaGreen3;
                static const Colour DarkSeaGreen;
                static const Colour PaleGreen3;
                static const Colour Honeydew4;
                static const Colour Green1;
                static const Colour Lime;
                static const Colour LimeGreen;
                static const Colour DarkSeaGreen4;
                static const Colour Green2;
                static const Colour PaleGreen4;
                static const Colour Green3;
                static const Colour ForestGreen;
                static const Colour Green4;
                static const Colour Green;
                static const Colour DarkGreen;
                static const Colour LawnGreen;
                static const Colour Chartreuse;
                static const Colour Chartreuse1;
                static const Colour Chartreuse2;
                static const Colour Chartreuse3;
                static const Colour Chartreuse4;
                static const Colour GreenYellow;
                static const Colour DarkOliveGreen3;
                static const Colour DarkOliveGreen1;
                static const Colour DarkOliveGreen2;
                static const Colour DarkOliveGreen4;
                static const Colour DarkOliveGreen;
                static const Colour OliveDrab;
                static const Colour OliveDrab1;
                static const Colour OliveDrab2;
                static const Colour OliveDrab3;
                static const Colour YellowGreen;
                static const Colour OliveDrab4;
                static const Colour Ivory;
                static const Colour Ivory1;
                static const Colour LightYellow;
                static const Colour LightYellow1;
                static const Colour Beige;
                static const Colour Ivory2;
                static const Colour LightGoldenrodYellow;
                static const Colour LightYellow2;
                static const Colour Ivory3;
                static const Colour LightYellow3;
                static const Colour Ivory4;
                static const Colour LightYellow4;
                static const Colour Yellow;
                static const Colour Yellow1;
                static const Colour Yellow2;
                static const Colour Yellow3;
                static const Colour Yellow4;
                static const Colour Olive;
                static const Colour DarkKhaki;
                static const Colour Khaki2;
                static const Colour LemonChiffon4;
                static const Colour Khaki1;
                static const Colour Khaki3;
                static const Colour Khaki4;
                static const Colour PaleGoldenrod;
                static const Colour LemonChiffon;
                static const Colour LemonChiffon1;
                static const Colour Khaki;
                static const Colour LemonChiffon3;
                static const Colour LemonChiffon2;
                static const Colour MediumGoldenRod;
                static const Colour Cornsilk4;
                static const Colour Gold;
                static const Colour Gold1;
                static const Colour Gold2;
                static const Colour Gold3;
                static const Colour Gold4;
                static const Colour LightGoldenrod;
                static const Colour LightGoldenrod4;
                static const Colour LightGoldenrod1;
                static const Colour LightGoldenrod3;
                static const Colour LightGoldenrod2;
                static const Colour Cornsilk3;
                static const Colour Cornsilk2;
                static const Colour Cornsilk;
                static const Colour Cornsilk1;
                static const Colour Goldenrod;
                static const Colour Goldenrod1;
                static const Colour Goldenrod2;
                static const Colour Goldenrod3;
                static const Colour Goldenrod4;
                static const Colour DarkGoldenrod;
                static const Colour DarkGoldenrod1;
                static const Colour DarkGoldenrod2;
                static const Colour DarkGoldenrod3;
                static const Colour DarkGoldenrod4;
                static const Colour FloralWhite;
                static const Colour Wheat2;
                static const Colour OldLace;
                static const Colour Wheat;
                static const Colour Wheat1;
                static const Colour Wheat3;
                static const Colour Orange;
                static const Colour Orange1;
                static const Colour Orange2;
                static const Colour Orange3;
                static const Colour Orange4;
                static const Colour Wheat4;
                static const Colour Moccasin;
                static const Colour PapayaWhip;
                static const Colour NavajoWhite3;
                static const Colour BlanchedAlmond;
                static const Colour NavajoWhite;
                static const Colour NavajoWhite1;
                static const Colour NavajoWhite2;
                static const Colour NavajoWhite4;
                static const Colour AntiqueWhite4;
                static const Colour AntiqueWhite;
                static const Colour Tan;
                static const Colour Bisque4;
                static const Colour Burlywood;
                static const Colour AntiqueWhite2;
                static const Colour Burlywood1;
                static const Colour Burlywood3;
                static const Colour Burlywood2;
                static const Colour AntiqueWhite1;
                static const Colour Burlywood4;
                static const Colour AntiqueWhite3;
                static const Colour DarkOrange;
                static const Colour Bisque2;
                static const Colour Bisque;
                static const Colour Bisque1;
                static const Colour Bisque3;
                static const Colour DarkOrange1;
                static const Colour Linen;
                static const Colour DarkOrange2;
                static const Colour DarkOrange3;
                static const Colour DarkOrange4;
                static const Colour Peru;
                static const Colour Tan1;
                static const Colour Tan2;
                static const Colour Tan3;
                static const Colour Tan4;
                static const Colour PeachPuff;
                static const Colour PeachPuff1;
                static const Colour PeachPuff4;
                static const Colour PeachPuff2;
                static const Colour PeachPuff3;
                static const Colour SandyBrown;
                static const Colour Seashell4;
                static const Colour Seashell2;
                static const Colour Seashell3;
                static const Colour Chocolate;
                static const Colour Chocolate1;
                static const Colour Chocolate2;
                static const Colour Chocolate3;
                static const Colour Chocolate4;
                static const Colour SaddleBrown;
                static const Colour Seashell;
                static const Colour Seashell1;
                static const Colour Sienna4;
                static const Colour Sienna;
                static const Colour Sienna1;
                static const Colour Sienna2;
                static const Colour Sienna3;
                static const Colour LightSalmon3;
                static const Colour LightSalmon;
                static const Colour LightSalmon1;
                static const Colour LightSalmon4;
                static const Colour LightSalmon2;
                static const Colour Coral;
                static const Colour OrangeRed;
                static const Colour OrangeRed1;
                static const Colour OrangeRed2;
                static const Colour OrangeRed3;
                static const Colour OrangeRed4;
                static const Colour DarkSalmon;
                static const Colour Salmon1;
                static const Colour Salmon2;
                static const Colour Salmon3;
                static const Colour Salmon4;
                static const Colour Coral1;
                static const Colour Coral2;
                static const Colour Coral3;
                static const Colour Coral4;
                static const Colour Tomato4;
                static const Colour Tomato;
                static const Colour Tomato1;
                static const Colour Tomato2;
                static const Colour Tomato3;
                static const Colour MistyRose4;
                static const Colour MistyRose2;
                static const Colour MistyRose;
                static const Colour MistyRose1;
                static const Colour Salmon;
                static const Colour MistyRose3;
                static const Colour White;
                static const Colour Gray100;
                static const Colour Grey100;
                static const Colour Gray99;
                static const Colour Grey99;
                static const Colour Gray98;
                static const Colour Grey98;
                static const Colour Gray97;
                static const Colour Grey97;
                static const Colour Gray96;
                static const Colour Grey96;
                static const Colour WhiteSmoke;
                static const Colour Gray95;
                static const Colour Grey95;
                static const Colour Gray94;
                static const Colour Grey94;
                static const Colour Gray93;
                static const Colour Grey93;
                static const Colour Gray92;
                static const Colour Grey92;
                static const Colour Gray91;
                static const Colour Grey91;
                static const Colour Gray90;
                static const Colour Grey90;
                static const Colour Gray89;
                static const Colour Grey89;
                static const Colour Gray88;
                static const Colour Grey88;
                static const Colour Gray87;
                static const Colour Grey87;
                static const Colour Gainsboro;
                static const Colour Gray86;
                static const Colour Grey86;
                static const Colour Gray85;
                static const Colour Grey85;
                static const Colour Gray84;
                static const Colour Grey84;
                static const Colour Gray83;
                static const Colour Grey83;
                static const Colour LightGray;
                static const Colour LightGrey;
                static const Colour Gray82;
                static const Colour Grey82;
                static const Colour Gray81;
                static const Colour Grey81;
                static const Colour Gray80;
                static const Colour Grey80;
                static const Colour Gray79;
                static const Colour Grey79;
                static const Colour Gray78;
                static const Colour Grey78;
                static const Colour Gray77;
                static const Colour Grey77;
                static const Colour Gray76;
                static const Colour Grey76;
                static const Colour Silver;
                static const Colour Gray75;
                static const Colour Grey75;
                static const Colour Gray74;
                static const Colour Grey74;
                static const Colour Gray73;
                static const Colour Grey73;
                static const Colour Gray72;
                static const Colour Grey72;
                static const Colour Gray71;
                static const Colour Grey71;
                static const Colour Gray70;
                static const Colour Grey70;
                static const Colour Gray69;
                static const Colour Grey69;
                static const Colour Gray68;
                static const Colour Grey68;
                static const Colour Gray67;
                static const Colour Grey67;
                static const Colour DarkGray;
                static const Colour DarkGrey;
                static const Colour Gray66;
                static const Colour Grey66;
                static const Colour Gray65;
                static const Colour Grey65;
                static const Colour Gray64;
                static const Colour Grey64;
                static const Colour Gray63;
                static const Colour Grey63;
                static const Colour Gray62;
                static const Colour Grey62;
                static const Colour Gray61;
                static const Colour Grey61;
                static const Colour Gray60;
                static const Colour Grey60;
                static const Colour Gray59;
                static const Colour Grey59;
                static const Colour Gray58;
                static const Colour Grey58;
                static const Colour Gray57;
                static const Colour Grey57;
                static const Colour Gray56;
                static const Colour Grey56;
                static const Colour Gray55;
                static const Colour Grey55;
                static const Colour Gray54;
                static const Colour Grey54;
                static const Colour Gray53;
                static const Colour Grey53;
                static const Colour Gray52;
                static const Colour Grey52;
                static const Colour Gray51;
                static const Colour Grey51;
                static const Colour Fractal;
                static const Colour Gray50;
                static const Colour Grey50;
                static const Colour Gray;
                static const Colour Gray49;
                static const Colour Grey49;
                static const Colour Gray48;
                static const Colour Grey48;
                static const Colour Gray47;
                static const Colour Grey47;
                static const Colour Gray46;
                static const Colour Grey46;
                static const Colour Gray45;
                static const Colour Grey45;
                static const Colour Gray44;
                static const Colour Grey44;
                static const Colour Gray43;
                static const Colour Grey43;
                static const Colour Gray42;
                static const Colour Grey42;
                static const Colour DimGray;
                static const Colour DimGrey;
                static const Colour Gray41;
                static const Colour Grey41;
                static const Colour Gray40;
                static const Colour Grey40;
                static const Colour Gray39;
                static const Colour Grey39;
                static const Colour Gray38;
                static const Colour Grey38;
                static const Colour Gray37;
                static const Colour Grey37;
                static const Colour Gray36;
                static const Colour Grey36;
                static const Colour Gray35;
                static const Colour Grey35;
                static const Colour Gray34;
                static const Colour Grey34;
                static const Colour Gray33;
                static const Colour Grey33;
                static const Colour Gray32;
                static const Colour Grey32;
                static const Colour Gray31;
                static const Colour Grey31;
                static const Colour Gray30;
                static const Colour Grey30;
                static const Colour Gray29;
                static const Colour Grey29;
                static const Colour Gray28;
                static const Colour Grey28;
                static const Colour Gray27;
                static const Colour Grey27;
                static const Colour Gray26;
                static const Colour Grey26;
                static const Colour Gray25;
                static const Colour Grey25;
                static const Colour Gray24;
                static const Colour Grey24;
                static const Colour Gray23;
                static const Colour Grey23;
                static const Colour Gray22;
                static const Colour Grey22;
                static const Colour Gray21;
                static const Colour Grey21;
                static const Colour Gray20;
                static const Colour Grey20;
                static const Colour Gray19;
                static const Colour Grey19;
                static const Colour Gray18;
                static const Colour Grey18;
                static const Colour Gray17;
                static const Colour Grey17;
                static const Colour Gray16;
                static const Colour Grey16;
                static const Colour Gray15;
                static const Colour Grey15;
                static const Colour Gray14;
                static const Colour Grey14;
                static const Colour Gray13;
                static const Colour Grey13;
                static const Colour Gray12;
                static const Colour Grey12;
                static const Colour Gray11;
                static const Colour Grey11;
                static const Colour Gray10;
                static const Colour Grey10;
                static const Colour Gray9;
                static const Colour Grey9;
                static const Colour Gray8;
                static const Colour Grey8;
                static const Colour Gray7;
                static const Colour Grey7;
                static const Colour Gray6;
                static const Colour Grey6;
                static const Colour Gray5;
                static const Colour Grey5;
                static const Colour Gray4;
                static const Colour Grey4;
                static const Colour Gray3;
                static const Colour Grey3;
                static const Colour Gray2;
                static const Colour Grey2;
                static const Colour Gray1;
                static const Colour Grey1;
                static const Colour Black;
                static const Colour Gray0;
                static const Colour Grey0;
                static const Colour Opaque;
                static const Colour None;
                static const Colour Transparent;

                private:
                std::string _colourName = ""; ///< The name of the colour
                std::uint8_t _red = 0;     ///< The red component (0-255).
                std::uint8_t _blue = 0;    ///< The blue component (0-255).
                std::uint8_t _green = 0;   ///< The green component (0-255).
                std::uint8_t _alpha = 255; ///< The alpha component (0-255, defaults to 255).
            };

            /**
             * @brief Outputs the color's info to a stream.
             * @param os The output stream.
             * @param colour The color to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Colour &colour);

            /**
             * @brief Compares two colors for equality.
             * @param left The first color.
             * @param right The second color.
             * @return `true` if the colors are equal; otherwise, `false`.
             */
            [[nodiscard]] const bool operator==(Colour left, Colour right);

            /**
             * @brief Compares two colors for inequality.
             * @param left The first color.
             * @param right The second color.
             * @return `true` if the colors are not equal; otherwise, `false`.
             */
            [[nodiscard]] const bool operator!=(Colour left, Colour right);

            /**
             * @brief Adds two colors component-wise.
             * @param left The first color.
             * @param right The second color.
             * @return The resulting color.
             */
            [[nodiscard]] const Colour operator+(Colour left, Colour right);

            /**
             * @brief Subtracts two colors component-wise.
             * @param left The first color.
             * @param right The second color.
             * @return The resulting color.
             */
            [[nodiscard]] const Colour operator-(Colour left, Colour right);

            /**
             * @brief Multiplies two colors component-wise.
             * @param left The first color.
             * @param right The second color.
             * @return The resulting color.
             */
            [[nodiscard]] const Colour operator*(Colour left, Colour right);

            /**
             * @brief Adds another color to the current color component-wise.
             * @param left The color to modify.
             * @param right The color to add.
             * @return Reference to the modified color.
             */
            const Colour &operator+=(Colour &left, Colour right);

            /**
             * @brief Subtracts another color from the current color component-wise.
             * @param left The color to modify.
             * @param right The color to subtract.
             * @return Reference to the modified color.
             */
            const Colour &operator-=(Colour &left, Colour right);

            /**
             * @brief Multiplies another color with the current color component-wise.
             * @param left The color to modify.
             * @param right The color to multiply.
             * @return Reference to the modified color.
             */
            const Colour &operator*=(Colour &left, Colour right);
        }
    }
}
