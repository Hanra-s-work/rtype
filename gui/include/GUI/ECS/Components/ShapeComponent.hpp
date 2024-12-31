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

#include <any>
#include <memory>
#include <string>
#include <utility>
#include <ostream>
#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {

            enum class ActiveShape {
                NONE = -1,
                RECTANGLE = 0,
                CIRCLE,
                CONVEX
            };

            class ShapeComponent : public EntityNode {
                public:
                ShapeComponent(const std::uint32_t entityId = 0);
                ~ShapeComponent();

                void setHoverColor(const GUI::ECS::Utilities::Colour &hoverColor);
                void setNormalColor(const GUI::ECS::Utilities::Colour &normalColor);
                void setClickedColor(const GUI::ECS::Utilities::Colour &clickedColor);

                void setShape(const ActiveShape &type);
                void setShape(const ActiveShape &type, const std::any &shape);
                void setShape(const std::pair<ActiveShape, std::any> &shape);

                void setVisible(const bool visible);

                void setPosition(const std::pair<float, float> position);
                void setDimension(const std::pair<float, float> dimension);
                void setCollision(const CollisionComponent &collision);

                void toggleVisibility();

                const bool isVisible() const;
                const bool isShapeInitialised() const;

                const ActiveShape getShapeType() const;
                const std::pair<ActiveShape, std::any> getActiveShape() const;

                const GUI::ECS::Utilities::Colour getHoverColor() const;
                const GUI::ECS::Utilities::Colour getNormalColor() const;
                const GUI::ECS::Utilities::Colour getClickedColor() const;

                const std::pair<float, float> getPosition() const;
                const std::pair<float, float> getDimension() const;
                const std::pair<ActiveShape, std::any> getShape() const;
                const CollisionComponent getCollisionComponent() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                const bool getVisible() const;

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const ShapeComponent &copy);

                void clearShapes();

                std::optional<std::pair<ActiveShape, std::any>> render() const;

                ShapeComponent &operator=(const ShapeComponent &copy);

                private:
                void _processColor();
                void _processCollisions();

                template <typename T>
                void _assignShape(const std::any &shape, std::optional<T> &shapeStorage);

                bool _visible;
                ActiveShape _shape;

                std::optional<sf::CircleShape> _sfShapeCircle;
                std::optional<sf::ConvexShape> _sfShapeConvex;
                std::optional<sf::RectangleShape> _sfShapeRectangle;

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
