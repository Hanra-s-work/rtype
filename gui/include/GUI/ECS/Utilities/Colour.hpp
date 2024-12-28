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

#include <cstdint>
#include <algorithm>
#include <SFML/Graphics/Color.hpp>

#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
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
                Colour(Colour &copy);
                /**
                 * @brief Constructs a color associated with a specific entity ID.
                 * @param entityId The ID of the entity.
                 */
                Colour(const std::uint32_t entityId);
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
                 */
                explicit Colour(const std::uint32_t entityId, const std::uint32_t color);
                /**
                 * @brief Constructs a color with specific RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);
                /**
                 * @brief Constructs a color with specific RGBA components, associated with an entity ID.
                 * @param entityId The ID of the entity.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);

                /**
                 * @brief Sets the color using a 32-bit integer representation.
                 * @param color The 32-bit integer color value (0xRRGGBBAA).
                 */
                void setColour(const std::uint32_t color);
                /**
                 * @brief Sets the color using individual RGBA components.
                 * @param red Red component (0-255).
                 * @param green Green component (0-255).
                 * @param blue Blue component (0-255).
                 * @param alpha Alpha component (0-255, defaults to 255).
                 */
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);
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
                 * @brief Converts the color to an SFML `sf::Color` object.
                 * @return The SFML color representation.
                 */
                const sf::Color toSFMLColour() const;

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
                 * @brief Retrieves the color as an SFML `sf::Color`.
                 * @return The SFML color representation.
                 */
                const sf::Color getColourSFML() const;

                /**
                 * @brief Provides a human-readable string representation of the color.
                 * @return A string describing the RGBA components.
                 */
                const std::string getInfo() const;

                /**
                 * @brief Clamps a value between a minimum and maximum range.
                 * @param value The value to clamp.
                 * @param min The minimum allowable value (default: 0).
                 * @param max The maximum allowable value (default: 255).
                 * @return The clamped value.
                 */
                static const std::uint8_t clamp(std::int32_t value, std::uint8_t min = 0, std::uint8_t max = 255);

                private:
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
