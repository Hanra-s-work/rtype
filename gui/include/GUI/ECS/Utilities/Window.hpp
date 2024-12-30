/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Window.hpp
*/

#pragma once

#include <any>
#include <string>
#include <cstring>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent;
            class ShapeComponent;
            class ButtonComponent;
            class SpriteComponent;
        }
        namespace Utilities
        {
            class Window : public EntityNode {
                public:
                Window(const std::uint32_t entityId = 0, const std::uint32_t windowWidth = 800, const std::uint32_t windowHeight = 600, const std::string &windowName = "R-Type", unsigned int frameRateLimit = 60);
                ~Window();

                void clear(const GUI::ECS::Utilities::Colour &color = GUI::ECS::Utilities::Colour::Black);
                void display();
                bool isOpen() const;
                void close();

                std::any pollEvent();
                void setFramerateLimit(const unsigned int framerateLimit);
                void setFullScreen(const bool fullScreen);

                /**
                  *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                const bool getFullScreen() const;

                void draw(const GUI::ECS::Components::TextComponent &text);
                void draw(const GUI::ECS::Components::ShapeComponent &shape);
                void draw(const GUI::ECS::Components::ImageComponent &image);
                void draw(const GUI::ECS::Components::SpriteComponent &sprite);
                void draw(const GUI::ECS::Components::ButtonComponent &button);

                std::any &getWindow();

                private:
                bool _fullScreen;
                std::string _windowName;
                sf::RenderWindow _sfWindow;
                std::shared_ptr<sf::RenderWindow> _sfSharedWindow;
                std::any _sfAnySharedWindow;
                std::uint32_t _windowWidth;
                std::uint32_t _windowHeight;
                sf::VideoMode _desktopMode = sf::VideoMode::getDesktopMode();
            };

            /**
             * @brief Outputs the window's info to a stream.
             * @param os The output stream.
             * @param item The window to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Window &item);
        }
    }
}
