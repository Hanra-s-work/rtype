/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.hpp
*/

/**
 * @file ButtonComponent.hpp
 * @brief This file contains the definition of the ButtonComponent class, which handles button-related functionalities.
 */

#pragma once

#include <any>
#include <optional>
#include <typeindex>
#include <functional>
#include <SFML/Graphics/Color.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/Colour.hpp"
#include "GUI/ECS/Components/TextComponent.hpp"
#include "GUI/ECS/Components/ShapeComponent.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class ButtonComponent
             * @brief Manages button functionalities, including appearance, position, and callbacks.
             */
            class ButtonComponent : public EntityNode {
                public:
                /**
                 * @brief Default constructor for ButtonComponent.
                 *
                 * @param entityId The unique ID of the entity. Default is 0.
                 */
                ButtonComponent(const std::uint32_t entityId = 0);

                /**
                 * @brief Constructor initializing with shape and text components.
                 *
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 */
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem);
                /**
                 * @brief Constructor initializing with shape, text components, and a callback function.
                 *
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param callback The function to be called when the button is triggered.
                 */
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback);
                /**
                 * @brief Constructor initializing with shape, text, collision components, and text size.
                 *
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param collisionItem The collision component of the button.
                 * @param textSize The size of the text. Default is 40.
                 */
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);
                /**
                 * @brief Constructor initializing with all button components.
                 *
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param callback The function to be called when the button is triggered.
                 * @param collisionItem The collision component of the button.
                 * @param textSize The size of the text. Default is 40.
                 */
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);

                /**
                 * @brief Constructor initializing with shape and text components.
                 *
                 * @param entityId The entity identification for the class
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 */
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem);
                /**
                 * @brief Constructor initializing with shape, text components, and a callback function.
                 *
                 * @param entityId The entity identification for the class
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param callback The function to be called when the button is triggered.
                 */
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback);
                /**
                 * @brief Constructor initializing with shape, text, collision components, and text size.
                 *
                 * @param entityId The entity identification for the class
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param collisionItem The collision component of the button.
                 * @param textSize The size of the text. Default is 40.
                 */
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);
                /**
                 * @brief Constructor initializing with all button components.
                 *
                 * @param entityId The entity identification for the class
                 * @param shapeItem The shape component of the button.
                 * @param textItem The text component of the button.
                 * @param callback The function to be called when the button is triggered.
                 * @param collisionItem The collision component of the button.
                 * @param textSize The size of the text. Default is 40.
                 */
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);

                /**
                 * @brief Destructor for ButtonComponent.
                 */
                ~ButtonComponent();

                /**
                 * @brief Set the Hover Color of the button for the child components
                 *
                 * @param hoverColor
                 */
                void setHoverColor(const GUI::ECS::Systems::Colour &hoverColor);
                /**
                 * @brief Set the Normal Color of the button for the child objects
                 *
                 * @param normalColor
                 */
                void setNormalColor(const GUI::ECS::Systems::Colour &normalColor);
                /**
                 * @brief Set the Clicked Color of the button for the child objects
                 *
                 * @param clickedColor
                 */
                void setClickedColor(const GUI::ECS::Systems::Colour &clickedColor);
                /**
                 * @brief Set the Text Hover Color
                 *
                 * @param hoverColor
                 */
                void setTextHoverColor(const GUI::ECS::Systems::Colour &hoverColor);
                /**
                 * @brief Set the Text Normal Color
                 *
                 * @param normalColor
                 */
                void setTextNormalColor(const GUI::ECS::Systems::Colour &normalColor);
                /**
                 * @brief Set the Text Clicked Color
                 *
                 * @param clickedColor
                 */
                void setTextClickedColor(const GUI::ECS::Systems::Colour &clickedColor);

                /**
                 * @brief Set the Position of all objects contained in the button
                 *
                 * @param position
                 */
                void setPosition(const std::pair<float, float> &position);
                /**
                 * @brief Set the Dimension of all objects contained in the button
                 *
                 * @param dimension The dimension of the button
                 * @param textSize The size of the text
                 */
                void setDimension(const std::pair<float, float> &dimension, const std::uint32_t textSize = 40);
                /**
                 * @brief Set the Text Position
                 *
                 * @param position
                 */
                void setTextPosition(const std::pair<float, float> &position);
                /**
                 * @brief Set the Text Size
                 *
                 * @param textSize
                 */
                void setTextSize(const std::uint32_t textSize);
                /**
                 * @brief Set the Shape Position
                 *
                 * @param position
                 */
                void setShapePosition(const std::pair<float, float> &position);
                /**
                 * @brief Set the Shape Dimensions
                 *
                 * @param dimension
                 */
                void setShapeDimension(const std::pair<float, float> &dimension);
                /**
                 * @brief Set the Collision for all objects of the Button class.
                 *
                 * @param collision The collision information
                 * @param textSize The size of the text
                 */
                void setCollision(const GUI::ECS::Components::CollisionComponent &collision, const std::uint32_t textSize = 40);

                /**
                 * @brief Set the Callback function for the the button is clicked
                 *
                 * @param callback The function
                 * @param callbackName The name of the function (for debugging purposes)
                 */
                void setCallback(std::function<void()> callback, const std::string &callbackName = "Callback Function");

                /**
                 * @brief Set the visibility of the element
                 *
                 * @param visible A boolean instance informing if (true) to be visible, (false) hidden.
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Get the callback function
                 *
                 * @return std::function<void()>
                 */
                std::function<void()> callback();

                /**
                 * @brief Get the information about if the element is visible
                 *
                 * @return true The component is visible
                 * @return false The component is hidden
                 */
                const bool isVisible() const;

                /**
                 * @brief Toggle the visibility of the component
                 *
                 */
                void toggleVisibility();

                /**
                 * @brief Get the Clicked Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getClickedColor() const;
                /**
                 * @brief Get the Normal Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getNormalColor() const;
                /**
                 * @brief Get the Hover Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getHoverColor() const;

                /**
                 * @brief Get the Text Clicked Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getTextClickedColor() const;
                /**
                 * @brief Get the Text Normal Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getTextNormalColor() const;
                /**
                 * @brief Get the Text Hover Color
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getTextHoverColor() const;

                /**
                 * @brief Get the Text Size
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getTextSize() const;
                /**
                 * @brief Get the Position of the button
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getPosition() const;
                /**
                 * @brief Get the Dimensions of the button
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getDimension() const;
                /**
                 * @brief Get the Text Position
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getTextPosition() const;
                /**
                 * @brief Get the Shape Position
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getShapePosition() const;
                /**
                 * @brief Get the Shape's Dimensions
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getShapeDimension() const;
                /**
                 * @brief Get the button collision object
                 *
                 * @return const GUI::ECS::Components::CollisionComponent
                 */
                const GUI::ECS::Components::CollisionComponent getCollision() const;

                /**
                 * @brief Get the Callback Name of the callback function
                 *
                 * @return const std::string
                 */
                const std::string getCallbackName() const;
                /**
                 * @brief Get the Callback object
                 *
                 * @return const std::function<void()>
                 */
                const std::function<void()> getCallback() const;

                /**
                 * @brief Get the information about if the Button is visible or hidden
                 *
                 * @return true The button is visible
                 * @return false The button is hidden
                 *
                 * @note This is an internal function used
                 * for the update function, please use the `isVisible` function.
                 */
                const bool getVisible() const;

                /**
                 * @brief Get the Text Component
                 *
                 * @return cost
                 */
                const GUI::ECS::Components::TextComponent getTextComponent() const;
                /**
                 * @brief Get the Shape Component
                 *
                 * @return const GUI::ECS::Components::ShapeComponent&
                 */
                const GUI::ECS::Components::ShapeComponent &getShapeComponent() const;
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
                 * @brief Update the mouse position information for all the entities in the button.
                 *
                 * @param mouse
                 */
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                /**
                 * @brief Update the textComponent instance located in the button.
                 *
                 * @param copy
                 */
                void update(const GUI::ECS::Components::TextComponent &copy);
                /**
                 * @brief Update the ShapeComponent instance located in the button.
                 *
                 * @param copy
                 */
                void update(const GUI::ECS::Components::ShapeComponent &copy);
                /**
                 * @brief Update the Button component using another Button Component.
                 *
                 * @param copy
                 */
                void update(const GUI::ECS::Components::ButtonComponent &copy);

                /**
                 * @brief Get the components that need rendering
                 *
                 * @return std::unordered_map<std::type_index, std::any>
                 *
                 * @note this is a function called by the window `draw` function,
                 * you do not need to call it.
                 */
                std::unordered_map<std::type_index, std::any> render() const;

                /**
                 * @brief A operator to allow seemless updating/asining from one
                 * button class to another.
                 *
                 * @param copy
                 * @return ButtonComponent&
                 */
                ButtonComponent &operator =(const GUI::ECS::Components::ButtonComponent &copy);

                private:
                bool _visible = true;                                           //!< A boolean instance that stores the state about the class needing to be rendered or not
                std::string _callbackName = "";                                 //!< A string containing the name of the callback function
                std::function<void()> _callback;                                //!< A function instance containing the callback function
                GUI::ECS::Components::TextComponent _componentText;             //!< The text component instance in charge of displaying text.
                GUI::ECS::Components::ShapeComponent _componentShape;           //!< The shape component instance in charge of displaying the shape behind the text.
                std::uint32_t _textSize = 40;                                   //!< An unsigned int 32 in charge of storing the size of the text component.
                GUI::ECS::Components::CollisionComponent _collision;            //!< The collision component in charge of tracking at a higher level the position of the components.

            };

            /**
             * @brief Outputs the button's info to a stream.
             *
             * @param os The output stream.
             * @param item The button to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const ButtonComponent &item);
        }
    }
}

