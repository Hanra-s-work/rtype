/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.hpp
*/

/**
 * @file EventManager.hpp
 * @brief This is the file that contains the EvenManager class
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
            class Window;
            class EventManager : public EntityNode {
                public:
                EventManager(const std::uint32_t entityId = 0);
                ~EventManager();
                void clearEvents();
                void processEvents(GUI::ECS::Systems::Window &window);

                const bool isMouseInFocus() const;
                const bool isLeftButtonClicked() const;
                const bool isRightButtonClicked() const;

                const bool isKeyPressed(const GUI::ECS::Systems::Key &key) const;

                const float getPositionX() const;
                const float getPositionY() const;

                const std::pair<int, int> getMousePosition() const;
                const GUI::ECS::Systems::MouseInfo getMouseInfo() const;

                const std::vector<GUI::ECS::Systems::Key> getKeys() const;
                /**
                 * @brief This is a function meant for debugging purposes
                * It will dump the current state of the variables upon call.
                * It will dump them for itself and any of it's underlying classes
                *
                * @param indent The level to which the class should be indented in the dump.
                * @return const std::string The formatted output.
                */
                const std::string getInfo(const unsigned int indent = 0) const;

                void update(GUI::ECS::Systems::Window &window);
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                void update(const GUI::ECS::Systems::EventManager &copy);

                EventManager &operator=(const GUI::ECS::Systems::EventManager &copy);

                private:
                MouseInfo _mouse;
                KeyMapper _mapper;
                std::vector<GUI::ECS::Systems::Key> _keys;
                std::uint8_t _resetDelay = 10;
                std::uint8_t _resetIndex = 0;
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


