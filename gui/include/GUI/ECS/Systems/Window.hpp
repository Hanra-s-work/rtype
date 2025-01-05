/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.hpp
*/

/**
 * @file Window.hpp
 *
 * @brief Header file for the `Window` class, which handles the graphical window and rendering logic.
 */

#pragma once

#include <any>
#include <string>
#include <cstring>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components.hpp"
#include "GUI/ECS/Systems/Colour.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @brief Represents a text component to be rendered in the window.
             */
            class TextComponent;

            /**
             * @brief Represents a shape component to be rendered in the window.
             */
            class ShapeComponent;

            /**
             * @brief Represents a button component to be rendered in the window.
             */
            class ButtonComponent;

            /**
             * @brief Represents a sprite component to be rendered in the window.
             */
            class SpriteComponent;

            /**
             * @brief Represents an image component to be rendered in the window.
             */
            class ImageComponent;
        }

        namespace Systems
        {
            /**
             * @class Window
             * @brief Manages an SFML-based graphical window and handles rendering of ECS components.
             */
            class Window : public EntityNode {
                public:
                /**
                 * @brief Constructs a new Window object.
                 *
                 * @param entityId The unique ID of the entity associated with this window.
                 * @param windowWidth The width of the window in pixels.
                 * @param windowHeight The height of the window in pixels.
                 * @param windowName The title of the window.
                 * @param frameRateLimit The maximum frame rate for rendering.
                 */
                Window(const std::uint32_t entityId = 0, const std::uint32_t windowWidth = 800, const std::uint32_t windowHeight = 600, const std::string &windowName = "R-Type", unsigned int frameRateLimit = 60);

                /**
                 * @brief Destroys the Window object.
                 */
                ~Window();

                /**
                 * @brief Clears the window with the specified color.
                 *
                 * @param color The color to clear the window with. Defaults to black.
                 */
                void clear(const GUI::ECS::Systems::Colour &color = GUI::ECS::Systems::Colour::Black);

                /**
                 * @brief Displays the contents of the window on the screen.
                 */
                void display();

                /**
                 * @brief Checks if the window is currently open.
                 *
                 * @return true if the window is open, false otherwise.
                 */
                bool isOpen() const;

                /**
                 * @brief Closes the window.
                 */
                void close();

                /**
                 * @brief Polls for the next event in the window's event queue.
                 *
                 * @return A `std::any` containing the event, or an empty value if no event is available.
                 */
                std::any pollEvent();

                /**
                 * @brief Sets the frame rate limit of the window.
                 *
                 * @param framerateLimit The maximum number of frames per second.
                 */
                void setFramerateLimit(const unsigned int framerateLimit);
                /**
                 * @brief Enables or disables fullscreen mode for the window.
                 *
                 * @param fullScreen Whether to enable fullscreen mode.
                 */
                void setFullScreen(const bool fullScreen);

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
                 * @brief Retrieves the current fullscreen mode of the window.
                 *
                 * @return true if fullscreen mode is enabled, false otherwise.
                 */
                const bool getFullScreen() const;

                /**
                 * @brief Renders a text component to the window.
                 *
                 * @param text The text component to render.
                 */
                void draw(const GUI::ECS::Components::TextComponent &text);
                /**
                 * @brief Renders a shape component to the window.
                 *
                 * @param shape The shape component to render.
                 */
                void draw(const GUI::ECS::Components::ShapeComponent &shape);
                /**
                 * @brief Renders an image component to the window.
                 *
                 * @param image The image component to render.
                 */
                void draw(const GUI::ECS::Components::ImageComponent &image);
                /**
                 * @brief Renders a sprite component to the window.
                 *
                 * @param sprite The sprite component to render.
                 */
                void draw(const GUI::ECS::Components::SpriteComponent &sprite);
                /**
                 * @brief Renders a button component to the window.
                 *
                 * @param button The button component to render.
                 */
                void draw(const GUI::ECS::Components::ButtonComponent &button);


                private:
                bool _fullScreen;                                               //!< A boolean instance to indicate wether the window is in fullscreen or not
                std::string _windowName;                                        //!< A string containing the window's name
                sf::RenderWindow _sfWindow;                                     //!< The sfml window instance
                std::uint32_t _windowWidth;                                     //!< The window width
                std::uint32_t _windowHeight;                                    //!< The window height
                sf::VideoMode _desktopMode = sf::VideoMode::getDesktopMode();   //!< The size of the window when in desktop mode
            };

            /**
             * @brief Outputs the window's info to a stream.
             *
             * @param os The output stream.
             * @param item The window to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Window &item);
        }
    }
}
