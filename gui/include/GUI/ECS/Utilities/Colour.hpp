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
            class Colour : public EntityNode {
                public:
                Colour();
                Colour(Colour &copy);
                Colour(const std::uint32_t entityId);
                Colour(const std::uint32_t entityId, Colour &copy);
                explicit Colour(const std::uint32_t entityId, const std::uint32_t color);
                Colour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);
                Colour(const std::uint32_t entityId, const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);

                void setColour(const std::uint32_t color);
                void setColour(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255);
                void setRed(const std::uint8_t red);
                void setBlue(const std::uint8_t blue);
                void setGreen(const std::uint8_t green);
                void setAlpha(const std::uint8_t alpha);

                ////////////////////////////////////////////////////////////
                /// \brief Retrieve the color as a 32-bit unsigned integer
                ///
                /// \return Color represented as a 32-bit unsigned integer
                ///
                ////////////////////////////////////////////////////////////
                const std::uint32_t toInteger() const;

                const sf::Color toSFMLColour() const;

                void update(const Colour &copy);
                void update(const std::uint32_t color);

                const std::uint8_t getRed() const;
                const std::uint8_t getBlue() const;
                const std::uint8_t getGreen() const;
                const std::uint8_t getAlpha() const;
                const std::uint32_t getColour() const;
                const std::uint32_t getInteger() const;
                const sf::Color getColourSFML() const;

                const std::string getInfo() const;

                static const std::uint8_t clamp(std::int32_t value, std::uint8_t min = 0, std::uint8_t max = 255);

                private:
                std::uint8_t _red = 0;
                std::uint8_t _blue = 0;
                std::uint8_t _green = 0;
                std::uint8_t _alpha = 255;
            };

            std::ostream &operator<<(std::ostream &os, const Colour &colour);

            [[nodiscard]] const bool operator==(Colour left, Colour right);

            [[nodiscard]] const bool operator!=(Colour left, Colour right);

            [[nodiscard]] const Colour operator+(Colour left, Colour right);

            [[nodiscard]] const Colour operator-(Colour left, Colour right);

            [[nodiscard]] const Colour operator*(Colour left, Colour right);

            const Colour &operator+=(Colour &left, Colour right);

            const Colour &operator-=(Colour &left, Colour right);

            const Colour &operator*=(Colour &left, Colour right);
        }
    }
}
