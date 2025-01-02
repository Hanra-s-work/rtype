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
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/Colour.hpp"
#include "GUI/ECS/Systems/MouseInfo.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @enum ActiveShape
             * @brief Enum representing different types of shapes managed by the ShapeComponent.
             */
            enum class ActiveShape {
                NONE = -1,                                                      //!< No shape initialized
                RECTANGLE = 0,                                                  //!< Rectangle shape
                CIRCLE,                                                         //!< Circle shape
                CONVEX                                                          //!< Convex shape
            };

            /**
             * @class ShapeComponent
             *
             * @brief Manages shapes and their associated properties in the ECS framework.
             */
            class ShapeComponent : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * @param entityId The ID of the entity this component belongs to.
                 */
                ShapeComponent(const std::uint32_t entityId = 0);
                /**
                 * @brief Constructs a convex shape.
                 *
                 * @param pointCount Number of points for the convex shape.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::size_t pointCount, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a circle shape.
                 *
                 * @param pointCount Number of points to render the circle.
                 * @param radius Radius of the circle.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::size_t pointCount, const float radius, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a rectangle shape.
                 *
                 * @param size Dimensions of the rectangle.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::pair<float, float> &size, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a rectangle shape from a FloatRect.
                 *
                 * @param rect Rectangle bounds.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const Recoded::FloatRect &rect, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a convex shape.
                 *
                 * @param entityId The ID of the entity this component belongs to.
                 * @param pointCount Number of points for the convex shape.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::uint32_t entityId, const std::size_t pointCount, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a circle shape.
                 *
                 * @param entityId The ID of the entity this component belongs to.
                 * @param pointCount Number of points to render the circle.
                 * @param radius Radius of the circle.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::uint32_t entityId, const std::size_t pointCount, const float radius, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a rectangle shape.
                 *
                 * @param entityId The ID of the entity this component belongs to.
                 * @param size Dimensions of the rectangle.
                 * @param position Position of the shape.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::uint32_t entityId, const std::pair<float, float> &size, const std::pair<float, float> &position = { 0,0 }, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);
                /**
                 * @brief Constructs a rectangle shape from a FloatRect.
                 *
                 * @param entityId The ID of the entity this component belongs to.
                 * @param rect Rectangle bounds.
                 * @param normalColour Default color for the shape.
                 * @param hoverColour Color when hovered.
                 * @param clickedColour Color when clicked.
                 * @param visible Visibility status of the shape.
                 */
                ShapeComponent(const std::uint32_t entityId, const Recoded::FloatRect &rect, const GUI::ECS::Systems::Colour &normalColour = GUI::ECS::Systems::Colour::AliceBlue, const GUI::ECS::Systems::Colour &hoverColour = GUI::ECS::Systems::Colour::White, const GUI::ECS::Systems::Colour &clickedColour = GUI::ECS::Systems::Colour::CornflowerBlue, const bool visible = true);

                /**
                 * @brief Destructor.
                 */
                ~ShapeComponent();

                /**
                 * @brief Sets the hover color for the shape.
                 *
                 * @param hoverColor The new hover color.
                 */
                void setHoverColor(const GUI::ECS::Systems::Colour &hoverColor);
                /**
                 * @brief Sets the normal color for the shape.
                 *
                 * @param normalColor The new normal color.
                 */
                void setNormalColor(const GUI::ECS::Systems::Colour &normalColor);
                /**
                 * @brief Sets the clicked color for the shape.
                 *
                 * @param clickedColor The new clicked color.
                 */
                void setClickedColor(const GUI::ECS::Systems::Colour &clickedColor);

                /**
                 * @brief Create a convex shape
                 *
                 * @param pointCount Create a shape based on the number of points being inputted
                 *
                 * @note Any previous shapes will be cleared and a convex will take their place.
                 */
                void setShape(const std::size_t pointCount);
                /**
                 * @brief Create a circle
                 *
                 * @param pointCount The number of points used to render the circle
                 * @param radius The radius of the circle
                 *
                 * @note Any previous shapes will be cleared and a circle will take their place.
                 */
                void setShape(const std::size_t pointCount, const float radius);
                /**
                 * @brief Create a rectangle
                 *
                 * @param size
                 *
                 * @note Any previous shapes will be cleared and a rectangle will take their place.
                 */
                void setShape(const std::pair<float, float> &size);
                /**
                 * @brief Create a rectangle based on an Recoded::FloatRect
                 *
                 * @param rect A rectangle component representing the dimensions of a rectangle.
                 *
                 * @note Any previous shapes will be cleared and a rectangle will take their place.
                 */
                void setShape(const Recoded::FloatRect &rect);
                /**
                 * @brief Set the type of the object (this does not initialise the component)
                 *
                 * @param type The type of the object
                 */
                void setShape(const ActiveShape &type);
                /**
                 * @brief Set the shape based on the type and an existing instance of a shape.
                 *
                 * @param type The type of shape
                 * @param shape The instance of the shape
                 *
                 * @throws CustomExceptions::InvalidShape if the provided shape was not found
                 */
                void setShape(const ActiveShape &type, const std::any &shape);
                /**
                 * @brief Set the Shape object based on a pair made of the shape type and shape instance
                 *
                 * @param shape std::pair<ActiveShape, std::any>
                 */
                void setShape(const std::pair<ActiveShape, std::any> &shape);

                /**
                 *@brief Set the visible toggle informing the program if it should (or not) render the component.
                 *
                 * @param visible
                 */
                void setVisible(const bool visible);

                /**
                 *@brief Set the position of the component
                 *
                 * @param position an std::pair<float, float> representing the position of the component
                 */
                void setPosition(const std::pair<float, float> position);
                /**
                 *@brief Set the Dimension object
                 *
                 * @param dimension an std::pair<float, float> representing the dimensions of the component
                 */
                void setDimension(const std::pair<float, float> dimension);
                /**
                 *@brief Set the internal collision class using another Collision component
                 *
                 * @param collision The collision component to query the data from.
                 */
                void setCollision(const CollisionComponent &collision);

                /**
                 * @brief Toggles the visibility of the shape.
                 */
                void toggleVisibility();

                /**
                 *@brief Get the visibility status of the component.
                 *
                 * @return true the component is visible
                 * @return false the component is hidden
                 */
                const bool isVisible() const;
                /**
                 *@brief Know if there is a shape initialised or not
                 *
                 * @return true the shape is initialised
                 * @return false the shape is not initialised
                 */
                const bool isShapeInitialised() const;

                /**
                 *@brief Get the Shape Type shape, none is returned if none are initialised.
                 *
                 * @return const ActiveShape
                 */
                const ActiveShape getShapeType() const;
                /**
                 *@brief Get the Active Shape and it's type all contained in an std::pair
                 *
                 * @return const std::pair<ActiveShape, std::any>
                 */
                const std::pair<ActiveShape, std::any> getActiveShape() const;

                /**
                 *@brief Get the Hover Color of the shape
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getHoverColor() const;
                /**
                 *@brief Get the Normal Color of the shape
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getNormalColor() const;
                /**
                 *@brief Get the Clicked Color shape
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getClickedColor() const;

                /**
                 *@brief Get the Position of the shape
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getPosition() const;
                /**
                 *@brief Get the Dimension of the shape
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getDimension() const;
                /**
                 *@brief Get the Shape and it's type all packaged in an std::pair
                 *
                 * @return const std::pair<ActiveShape, std::any>
                 */
                const std::pair<ActiveShape, std::any> getShape() const;
                /**
                 *@brief Get the Collision Component of the object
                 *
                 * @return const CollisionComponent
                 *
                 * @note This is an internal function used by the update function.
                 */
                const CollisionComponent getCollisionComponent() const;
                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                /**
                 *@brief Get the info about if the shape is visible or not
                 *
                 * @return true the object is visible
                 * @return false the object is hidden
                 *
                 * @note This is an internal function used by the `update` function, please call `isVisible` to get this information.
                 */
                const bool getVisible() const;

                /**
                 *@brief Update the mouse information of the component (this is used for mouse collision calculations)
                 *
                 * @param mouse
                 */
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                /**
                 *@brief Update the ShapeComponent using another shape component.
                 *
                 * @param copy
                 */
                void update(const ShapeComponent &copy);

                /**
                 *@brief Remove all and any initialised shapes in the class, this will reset the type to NONE.
                 *
                 */
                void clearShapes();

                /**
                 *@brief Get an optional std::pair of the object so that it can be displayed on screen
                 *
                 * @return std::optional<std::pair<ActiveShape, std::any>>
                 *
                 * @note This is an internal function meant to be called by the `draw` function from the `Window` component.
                 */
                std::optional<std::pair<ActiveShape, std::any>> render() const;

                /**
                 *@brief '=' operator in charge of allowing the user to seamlessly assing the content of one ShapeComponent to another.
                 *
                 * @param copy
                 *
                 * @return ShapeComponent&
                 */
                ShapeComponent &operator=(const ShapeComponent &copy);

                private:
                /**
                 *@brief Function in charge of updating the shape's colour based on the mouse information.
                 *
                 */
                void _processColor();
                /**
                 *@brief Function in charge of updating the collision information based on the initialised object.
                 *
                 */
                void _processCollisions();

                /**
                 *@brief A template in charge of assigning a provided shape to the correct std::optional shape container.
                 *
                 * @tparam T The template representing the shape type
                 *
                 * @param shape The shame instance
                 * @param shapeStorage The destination for the shape instance
                 */
                template <typename T>
                void _assignShape(const std::any &shape, std::optional<T> &shapeStorage);

                bool _visible = true;                                           //!< A boolean operator in charge of tracking the visibility of the component
                bool _inConstructor = true;                                     //!< A boolean operator in charge of tracking if we are or not in the constructor scope
                ActiveShape _shape;                                             //!< An enum representing the type of the shape

                std::optional<sf::CircleShape> _sfShapeCircle;                  //!< An std::optional of the sf::CircleShape in charge of containing circle instances
                std::optional<sf::ConvexShape> _sfShapeConvex;                  //!< An std::optional of the sf::ConvexShape in charge of containing convex shape instances
                std::optional<sf::RectangleShape> _sfShapeRectangle;            //!< An std::optional of the sf::RectangleShape in charge of containing a rectangle instance

                GUI::ECS::Systems::Colour _hoverColor;                          //!< A Colour instance in charge of representing the colour when the component is hovered
                GUI::ECS::Systems::Colour _normalColor;                         //!< A Colour instance in charge of representing the colour when the component is in it's default state
                GUI::ECS::Systems::Colour _clickedColor;                        //!< A Colour instance in charge of representing the colour when the component is clicked

                GUI::ECS::Components::CollisionComponent _collision;
            };

            /**
             * @brief Outputs the shape's info to a stream.
             *
             * @param os The output stream.
             * @param item The shape to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const ShapeComponent &item);
        }
    }
}
