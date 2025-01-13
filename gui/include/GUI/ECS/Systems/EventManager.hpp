/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.hpp
*/

/**
 * @file EventManager.hpp
 *
 * @brief Header file for the EventManager class, responsible for managing input events.
 */

#pragma once
#include <any>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "ActiveScreen.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/Key.hpp"
#include "GUI/ECS/Systems/Window.hpp"
#include "GUI/ECS/Systems/MouseInfo.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @brief Represents the window component.
             */
            class Window;
            /**
             * @class EventManager
             * @brief Manages input events such as mouse movements, key presses, and window interactions.
             */
            class EventManager : public EntityNode {
                public:
                /**
                 * @brief Constructs an EventManager with an optional entity ID.
                 *
                 * @param entityId The unique ID of the entity. Default is 0.
                 */
                EventManager(const std::uint32_t entityId = 0);
                /**
                 * @brief Destroys the EventManager instance.
                 */
                ~EventManager();
                /**
                 * @brief Clears all currently stored events.
                 */
                void clearEvents();
                /**
                 * @brief Processes events from the specified window.
                 *
                 * @param window The window from which events will be processed.
                 * @param currentScreen The screen that is currently in use.
                 */
                void processEvents(GUI::ECS::Systems::Window &window, const ActiveScreen &currentScreen = ActiveScreen::UNKNOWN);

                /**
                 * @brief Checks if the mouse is in focus within the window.
                 *
                 * @return true if the mouse is in focus, false otherwise.
                 */
                const bool isMouseInFocus() const;
                /**
                 * @brief Checks if the left mouse button is clicked.
                 *
                 * @return true if the left button is clicked, false otherwise.
                 */
                const bool isLeftButtonClicked() const;
                /**
                 * @brief Checks if the right mouse button is clicked.
                 *
                 * @return true if the right button is clicked, false otherwise.
                 */
                const bool isRightButtonClicked() const;

                /**
                 * @brief Checks if a specific key is currently pressed.
                 *
                 * @param key The key to check.
                 * @return true if the key is pressed, false otherwise.
                 */
                const bool isKeyPressed(const GUI::ECS::Systems::Key &key) const;

                /**
                 * @brief Retrieves the current X position of the mouse.
                 *
                 * @return The X coordinate of the mouse.
                 */
                const float getPositionX() const;
                /**
                 * @brief Retrieves the current Y position of the mouse.
                 *
                 * @return The Y coordinate of the mouse.
                 */
                const float getPositionY() const;

                /**
                 * @brief Retrieves the current position of the mouse as a pair (x, y).
                 *
                 * @return A pair containing the X and Y coordinates of the mouse.
                 */
                const std::pair<int, int> getMousePosition() const;
                /**
                 * @brief Retrieves the current state of the mouse.
                 *
                 * @return A MouseInfo object containing the mouse's state.
                 */
                const GUI::ECS::Systems::MouseInfo getMouseInfo() const;

                /**
                 * @brief Retrieves all currently pressed keys.
                 *
                 * @return A vector of Key objects representing pressed keys.
                 */
                const std::vector<GUI::ECS::Systems::Key> getKeys() const;
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
                 * @brief Updates the EventManager with events from a window.
                 *
                 * @param window The window to retrieve events from.
                 * @param screen The screen that is currently in use.
                 */
                void update(GUI::ECS::Systems::Window &window, const ActiveScreen &screen = ActiveScreen::UNKNOWN);
                /**
                 * @brief Updates the EventManager with new mouse information.
                 *
                 * @param mouse The updated mouse information.
                 */
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                /**
                 * @brief Updates the EventManager by copying data from another instance.
                 *
                 * @param copy The EventManager instance to copy from.
                 */
                void update(const GUI::ECS::Systems::EventManager &copy);

                /**
                 * @brief Assignment operator for the EventManager.
                 *
                 * @param copy The EventManager instance to assign from.
                 * @return A reference to the updated EventManager.
                 */
                EventManager &operator=(const GUI::ECS::Systems::EventManager &copy);

                private:
                MouseInfo _mouse;                                               //!< A MouseInfo component in charge of tracking the location of the mouse within the window
                KeyMapper _mapper;                                              //!< A KeyMapper component in charge of standardising the codes of the keys that were entered by the user
                std::vector<GUI::ECS::Systems::Key> _keys;                      //!< A Vector of keys to track the keys entered by the user
                std::uint8_t _resetDelay = 5;                                   //!< An unsigned integer in charge of adding a delay before clearing the previous set of events
                std::uint8_t _resetIndex = 0;                                   //!< An unsigned interger in charge of tracking the number of turns before resetting.
            };

            /**
             * @brief Outputs the event's info to a stream.
             * @param os The output stream.
             * @param item The event to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const EventManager &item);
        }
    }
}


