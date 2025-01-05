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

#include <any>
#include <cstdint>
#include <optional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/Font.hpp"
#include "GUI/ECS/Systems/Colour.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
            * @class GUI::ECS::Components::TextComponent
            * @brief A class that represents a text component in the GUI system.
            * It manages font, size, color, and position of text entities in a graphical application.
            *
            * This class is derived from the EntityNode class and is a part of the ECS system.
            * It includes various constructors for initializing a text component with different configurations.
            */
            class TextComponent : public EntityNode {
                public:

                /**
                 * @brief Default constructor. Initializes the text component with default values.
                 */
                TextComponent();
                /**
                 * @brief Constructor with an entity ID.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 */
                TextComponent(const std::uint32_t entityId);
                /**
                 * @brief Constructor with an entity ID and a font path.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontPath Path to the font file.
                 */
                TextComponent(const std::uint32_t entityId, const std::string &fontPath);
                /**
                 * @brief Constructor with an entity ID, a font path, and text content.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontPath Path to the font file.
                 * @param text The text to be displayed.
                 */
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text);
                /**
                 * @brief Constructor with an entity ID, font path, text content, and font size.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontPath Path to the font file.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 */
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size);
                /**
                 * @brief Constructor with detailed parameters.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontPath Path to the font file.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 */
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor);
                /**
                 * @brief Constructor with full parameter specification.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontPath Path to the font file.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param position The position of the text in 2D space.
                 */
                TextComponent(const std::uint32_t entityId, const std::string &fontPath, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::pair<float, float> &position);
                /**
                 * @brief Constructor with a font instance.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontInstance An instance of the font.
                 */
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance);
                /**
                 * @brief Constructor with a font instance and text content.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontInstance An instance of the font.
                 * @param text The text to be displayed.
                 */
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text);
                /**
                 * @brief Constructor with a font instance, text content, and font size.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontInstance An instance of the font.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 */
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size);
                /**
                 * @brief Constructor with detailed parameters and a font instance.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontInstance An instance of the font.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 */
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor);
                /**
                 * @brief Constructor with detailed parameters and a font instance, including position.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param fontInstance An instance of the font.
                 * @param text The text to be displayed.
                 * @param size The size of the font.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param position The position of the text in 2D space.
                 */
                TextComponent(const std::uint32_t entityId, const GUI::ECS::Systems::Font &fontInstance, const std::string &text, const unsigned int &size, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::pair<float, float> &position);

                /**
                 * @brief Destructor for TextComponent.
                 */
                ~TextComponent();

                /**
                 * @brief Set the Font of the text using a loaded Font instance from GUI::ECS::Systems::Font
                 *
                 * @param font
                 */
                void setFont(const GUI::ECS::Systems::Font &font);

                /**
                 * @brief Set the default colour of the text object
                 *
                 * @param color The default colour for the text
                 */
                void setNormalColor(const GUI::ECS::Systems::Colour &color);
                /**
                 * @brief Set the Hover Color of the text object
                 *
                 * @param color The hover colour of the text
                 */
                void setHoverColor(const GUI::ECS::Systems::Colour &color);
                /**
                 * @brief Set the Clicked Color of the text object
                 *
                 * @param color The clicked colour of the text
                 */
                void setClickedColor(const GUI::ECS::Systems::Colour &color);

                /**
                 * @brief Set the Text
                 *
                 * @param text The text to be displayed
                 */
                void setText(const std::string &text);

                /**
                 * @brief Set the Size of the text
                 *
                 * @param size The size of the text (in pixels)
                 */
                void setSize(const std::uint32_t &size);

                /**
                 * @brief Set the font from a path (this will attempt to load the font internally)
                 *
                 * @param fontPath The font path to be loaded.
                 * @param name The name of the font
                 *
                 * @throws CustomExceptions::InvalidFontPath if the font path provided is incorrect
                 */
                void setFontPath(const std::string &fontPath, const std::string &name = "");

                /**
                 * @brief Set the Position of the text
                 *
                 * @param position The position to be set.
                 */
                void setPosition(const std::pair<float, float> &position);

                /**
                 * @brief Set the visibility of the object using a boolean
                 * @li true : visible
                 * @li false : hidden
                 *
                 * @param visible The boolean value
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Toggle the visibility of the object.
                 * @if visible -> hidden
                 * @else hidden
                 */
                void toggleVisibility();

                /**
                 * @brief Check if the text is set to be rendered or not.
                 *
                 * @return true The text is set to be rendered
                 * @return false The text is not set to be rendered
                 */
                const bool isVisible() const;

                /**
                 * @brief Get the Font object contained in the class
                 *
                 * @return const GUI::ECS::Systems::Font
                 */
                const GUI::ECS::Systems::Font getFont() const;

                /**
                 * @brief Get the Font Path object
                 *
                 * @return const std::string
                 */
                const std::string getFontPath() const;

                /**
                 * @brief Get the Normal Color of the text
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getNormalColor() const;
                /**
                 * @brief Get the Hover Color of the text
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getHoverColor() const;
                /**
                 * @brief Get the Clicked Color of the text
                 *
                 * @return const GUI::ECS::Systems::Colour
                 */
                const GUI::ECS::Systems::Colour getClickedColor() const;

                /**
                 * @brief Get the Text that was set in the class.
                 *
                 * @return const std::string
                 */
                const std::string getText() const;

                /**
                 * @brief Get the Size of the text
                 *
                 * @return const std::uint32_t
                 */
                const std::uint32_t getSize() const;

                /**
                 * @brief Get the Position of the text
                 *
                 * @return const std::pair<float, float>
                 */
                const std::pair<float, float> getPosition() const;

                /**
                 * @brief Get the Visibility of the text
                 *
                 * @return true if visible
                 * @return false if hidden
                 */
                const bool getVisible() const;
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
                 * @brief Function in charge of returning the collision instance of the text component.
                 *
                 * @return const GUI::ECS::Components::CollisionComponent
                 */
                const GUI::ECS::Components::CollisionComponent getCollisionComponent() const;

                /**
                 * @brief Function in charge of rendering the text if it is set to visible, otherwise, does nothing
                 *
                 * @return std::optional<std::any>
                 */
                std::any render() const;

                /**
                 * @brief The function in charge of updating the stored mouse information
                 *
                 * @param mouse A mouse instance
                 */
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                /**
                 * @brief The function in charge of updating the current text component using another text component instance.
                 *
                 * @param copy A TextComponent instance
                 */
                void update(const GUI::ECS::Components::TextComponent &copy);

                /**
                 * @brief The overload in charge of allowing a TextComponent update using the '=' sign.
                 *
                 * @param copy The TextComponent to copy the data from.
                 *
                 * @return GUI::ECS::Components::TextComponent& An updated textComponent
                 */
                GUI::ECS::Components::TextComponent &operator =(const GUI::ECS::Components::TextComponent &copy);

                private:
                /**
                 * @brief Function in charge of loading the text component if not already done.
                 *
                 */
                void _initialiseText();
                /**
                 * @brief Function in charge of updating the state of the sf::Text instance
                 *
                 */
                void _processTextComponent();
                /**
                 * @brief Function in charge of loading the font into a font instance.
                 *
                 * @throws CustomExceptions::NoFont To inform the user that there was no usable font found.
                 */
                void _loadFont();

                bool _visible = true;                                                            //!< A boolean value to know if the text should be rendered or not
                bool _fontAltered = false;                                                       //!< A boolean value to know if the font configuration has been edited
                bool _fontChanged = false;                                                       //!< A boolean value to know if the font instance was changed
                bool _textAltered = false;                                                       //!< A boolean value to know if the text has been edited
                bool _sizeAltered = false;                                                       //!< A boolean value to know if the size has been edited
                bool _inConstructor = true;                                                      //!< A boolean value to know if the class has been built or is still being built
                bool _positionAltered = false;                                                   //!< A boolean value to know if the positon of the text has been altered
                std::string _text = "SampleText";                                                //!< A string to contain the text set by the user
                unsigned int _size = 30;                                                         //!< An unsigned int to contain the user assigned size
                std::optional<sf::Text> _sfTextComponent;                                        //!< An std::optional sf::Text to contain the final text instance that will be rendered
                CollisionComponent _textPos;                                                     //!< A Collision component class to contain and track collisions
                GUI::ECS::Systems::Font _font;                                                   //!< An GUI::ECS::Systems::Font class to contain the active font
                GUI::ECS::Systems::Colour _color = GUI::ECS::Systems::Colour::Black;             //!< A Colour class that contains the colour for the default state
                GUI::ECS::Systems::Colour _hoverColor = GUI::ECS::Systems::Colour::Black;        //!< A Colour class that contains the colour for the hover state
                GUI::ECS::Systems::Colour _clickedColor = GUI::ECS::Systems::Colour::Black;      //!< A Colour class that contains the colour for the clicked state
            };

            /**
             * @brief Outputs the text's info to a stream.
             * @param os The output stream.
             * @param item The text to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const TextComponent &item);

        }
    }
}

