/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.hpp
*/

/**
 * @file ButtonComponent.hpp
 * @brief This is the file that contains the class in charge of tracking buttons.
 */

#pragma once

#include <any>
#include <optional>
#include <typeindex>
#include <functional>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Components/TextComponent.hpp"
#include "GUI/ECS/Components/ShapeComponent.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ButtonComponent : public EntityNode {
                public:
                ButtonComponent(const std::uint32_t entityId = 0);

                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem);
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback);
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);
                ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);

                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem);
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback);
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);
                ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize = 40);

                ~ButtonComponent();

                void setHoverColor(const GUI::ECS::Utilities::Colour &hoverColor);
                void setNormalColor(const GUI::ECS::Utilities::Colour &normalColor);
                void setClickedColor(const GUI::ECS::Utilities::Colour &clickedColor);
                void setTextHoverColor(const GUI::ECS::Utilities::Colour &hoverColor);
                void setTextNormalColor(const GUI::ECS::Utilities::Colour &normalColor);
                void setTextClickedColor(const GUI::ECS::Utilities::Colour &clickedColor);

                void setPosition(const std::pair<float, float> &position);
                void setDimension(const std::pair<float, float> &dimension, const std::uint32_t textSize = 40);
                void setTextPosition(const std::pair<float, float> &position);
                void setTextSize(const std::uint32_t textSize);
                void setShapePosition(const std::pair<float, float> &position);
                void setShapeDimension(const std::pair<float, float> &dimension);
                void setCollision(const GUI::ECS::Components::CollisionComponent &collision, const std::uint32_t textSize = 40);

                void setCallback(std::function<void()> callback, const std::string &callbackName = "Callback Function");

                std::function<void()> callback();

                const bool isVisible() const;

                void toggleVisibility();

                const GUI::ECS::Utilities::Colour getClickedColor() const;
                const GUI::ECS::Utilities::Colour getNormalColor() const;
                const GUI::ECS::Utilities::Colour getHoverColor() const;

                const GUI::ECS::Utilities::Colour getTextClickedColor() const;
                const GUI::ECS::Utilities::Colour getTextNormalColor() const;
                const GUI::ECS::Utilities::Colour getTextHoverColor() const;

                const std::uint32_t getTextSize() const;
                const std::pair<float, float> getPosition() const;
                const std::pair<float, float> getDimension() const;
                const std::pair<float, float> getTextPosition() const;
                const std::pair<float, float> getShapePosition() const;
                const std::pair<float, float> getShapeDimension() const;
                const GUI::ECS::Components::CollisionComponent getCollision() const;

                const std::string getCallbackName() const;
                const std::function<void()> getCallback() const;

                const bool getVisible() const;

                const GUI::ECS::Components::TextComponent getTextComponent() const;
                const GUI::ECS::Components::ShapeComponent &getShapeComponent() const;
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
                void update(const GUI::ECS::Components::TextComponent &copy);
                void update(const GUI::ECS::Components::ShapeComponent &copy);
                void update(const GUI::ECS::Components::ButtonComponent &copy);

                std::unordered_map<std::type_index, std::any> render() const;

                ButtonComponent &operator =(const GUI::ECS::Components::ButtonComponent &copy);

                private:
                bool _visible = true;
                std::string _callbackName = "";
                std::function<void()> _callback;
                GUI::ECS::Components::TextComponent _componentText;
                GUI::ECS::Components::ShapeComponent _componentShape;
                std::uint32_t _textSize = 40;
                GUI::ECS::Components::CollisionComponent _collision;

            };

            /**
             * @brief Outputs the button's info to a stream.
             * @param os The output stream.
             * @param item The button to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const ButtonComponent &item);
        }
    }
}

