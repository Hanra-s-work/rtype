/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

/**
 * @file ShapeComponent.hpp
 * @brief This is the file that contains the class in charge of managing shapes
 */

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"
#include "GUI/ECS/Utilities/EventManager.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ShapeComponent : public EntityNode {
                public:
                ShapeComponent(const std::uint32_t entityId = 0);
                ~ShapeComponent();

                void setHoverColor(const GUI::ECS::Utilities::Colour &hoverColor);
                void setNormalColor(const GUI::ECS::Utilities::Colour &normalColor);
                void setClickedColor(const GUI::ECS::Utilities::Colour &clickedColor);

                void setShape(sf::Shape &&shape);
                void setShape(const sf::Shape &shape);
                void setShape(std::unique_ptr<sf::Shape> shape);

                void setPosition(const sf::Vector2f position);
                void setDimension(const sf::Vector2f dimension);
                void setCollision(const GUI::ECS::Components::CollisionComponent &collision);

                const GUI::ECS::Utilities::Colour getHoverColor() const;
                const GUI::ECS::Utilities::Colour getNormalColor() const;
                const GUI::ECS::Utilities::Colour getClickedColor() const;

                const sf::Vector2f getPosition() const;
                const sf::Vector2f getDimension() const;
                const sf::Shape &getShape() const;
                const GUI::ECS::Components::CollisionComponent getCollisionComponent() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::ShapeComponent &copy);

                void render(sf::RenderWindow &window) const;

                ShapeComponent &operator=(const ShapeComponent &copy);
                ShapeComponent &operator=(ShapeComponent &&move) noexcept;

                private:
                static std::unique_ptr<sf::Shape> cloneShape(const sf::Shape &shape);
                void _processColor();

                std::unique_ptr<sf::Shape> _sfShape;
                GUI::ECS::Utilities::Colour _hoverColor;
                GUI::ECS::Utilities::Colour _normalColor;
                GUI::ECS::Utilities::Colour _clickedColor;
                GUI::ECS::Components::CollisionComponent _collision;
            };

            /**
             * @brief Outputs the shape's info to a stream.
             * @param os The output stream.
             * @param item The shape to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const ShapeComponent &item);
        }
    }
}
