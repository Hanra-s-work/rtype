/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MouseInfo.hpp
*/

/**
 * @file MouseInfo.hpp
 * @brief This is the header file containing the class for the mouse information.
 */

#pragma once

#include <any>
#include <utility>
#include <optional>
#include <SFML/Window/Event.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            /**
             *@brief An enum class to allow the user to know which direction the mouse has scrolled.
             *
             */
            enum class MouseWheel
            {
                Vertical,  //!< The vertical mouse wheel
                Horizontal //!< The horizontal mouse wheel
            };
            class MouseInfo : public EntityNode {
                public:
                MouseInfo(const std::uint32_t entityId = 0);
                ~MouseInfo();

                void update(const std::any &event);
                void update(const MouseInfo &entity);
                void update(const std::pair<int, int> &position);

                const std::pair<int, int> getMousePosition() const;

                const bool isMouseInFocus() const;
                const bool isMouseLeftButtonClicked() const;
                const bool isMouseMiddleButtonClicked() const;
                const bool isMouseRightButtonClicked() const;
                const bool isMouseExtra1ButtonClicked() const;
                const bool isMouseExtra2ButtonClicked() const;
                const bool isMouseWheelScrolled() const;
                const bool isMouseWheelScrolledUp() const;
                const bool isMouseWheelScrolledDown() const;
                const bool isMouseWheelScrolledLeft() const;
                const bool isMouseWheelScrolledRight() const;

                const float getScrollIndex() const;

                const MouseWheel getScrollDirection() const;

                const int getPositionX() const;
                const int getPositionY() const;
                /**
                  *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                void clear();

                MouseInfo &operator=(const GUI::ECS::Utilities::MouseInfo &copy);

                private:
                bool _mouseInFocus = false;                           //!< A boolean instance that informs the class if the mouse is in focus
                bool _leftButtonClicked = false;                      //!< A boolean instance that informs the class if the left button is clicked
                bool _rightButtonClicked = false;                     //!< A boolean instance that informs the class if the right button is clicked
                bool _middleButtonClicked = false;                    //!< A boolean instance that informs the class if the middle button is clicked
                bool _extra1ButtonClicked = false;                    //!< A boolean instance that informs the class if the extra button 1 is clicked
                bool _extra2ButtonClicked = false;                    //!< A boolean instance that informs the class if the extra button 2 is clicked
                std::pair<int, int> _mousePosition = { 0,0 };         //!< A std::pair<int, int> that allows the class to store the mouse position
                sf::Event::MouseWheelScrolled _mouseWheel;            //!< The sfml mousewheel instance that allows the mouse scrolled functions to return the data that is expected
            };

            /**
             * @brief Outputs the Mouse's info to a stream.
             *
             * @param os The output stream.
             * @param item The Mouse to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const MouseInfo &item);
        }
    }
}
