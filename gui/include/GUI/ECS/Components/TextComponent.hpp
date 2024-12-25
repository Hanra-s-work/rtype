/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.hpp
*/

/**
 * @file TextComponent.hpp
 * @brief This is the file that contains a class in charge of managing a test component.
 */

#pragma once

#include <cstdint>
#include <optional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Font.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent : public EntityNode {
                public:
                TextComponent();
                TextComponent(const std::uint32_t entityId);
                TextComponent(const std::uint32_t entityId, const std::string &fontPath);
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text);
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size);
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor);
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor, const sf::Vector2f &position);
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance);
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text);
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size);
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor);
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Utilities::Font &fontInstance, const std::string &text, const unsigned int &size, const sf::Color &normalColor, const sf::Color &hoverColor, const sf::Color &clickedColor, const sf::Vector2f &position);
                ~TextComponent();

                void setFont(const sf::Font &font);
                void setFont(const GUI::ECS::Utilities::Font &font);

                void setNormalColor(const sf::Color &color);
                void setHoverColor(const sf::Color &color);
                void setClickedColor(const sf::Color &color);

                void setText(const std::string &text);

                void setSize(const std::uint32_t &size);

                void setFontPath(const std::string &fontPath);

                void setPosition(const sf::Vector2f &position);

                void setVisible(const bool visible);

                GUI::ECS::Utilities::Font getFont() const;

                std::string getFontPath() const;

                sf::Color getNormalColor() const;
                sf::Color getHoverColor() const;
                sf::Color getClickedColor() const;

                std::string getText() const;

                std::uint32_t getSize() const;

                sf::Vector2f getPosition() const;

                bool getVisible() const;

                void render(sf::RenderWindow &window) const;

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::TextComponent &copy);

                GUI::ECS::Components::TextComponent &operator =(const GUI::ECS::Components::TextComponent &copy);

                private:
                void _processTextComponent();
                void _loadFont();

                bool _visible;
                std::string _text = "SampleText";
                unsigned int _size = 30;
                std::optional<sf::Text> _sfTextComponent;
                CollisionComponent _textPos;
                GUI::ECS::Utilities::Font _font;
                sf::Color _color = sf::Color::Black;
                sf::Color _hoverColor = sf::Color::Black;
                sf::Color _clickedColor = sf::Color::Black;
            };
        }
    }
}

