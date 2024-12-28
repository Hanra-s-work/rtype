/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.hpp
*/

/**
 * @file Clock.hpp
 * @brief This is the file that contains the Clock class
 */

#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Clock : public EntityNode {
                public:
                Clock(const std::uint32_t entityId = 0);
                ~Clock();
                const std::int64_t reset();
                const std::int64_t getElapsedTime() const;
                void stop();
                void start();
                const bool isRunning() const;
                /**
                * @brief This is a function meant for debugging purposes
                * It will dump the current state of the variables upon call.
                * It will dump them for itself and any of it's underlying classes
                *
                * @param indent The level to which the class should be indented in the dump.
                * @return const std::string The formatted output.
                */
                const std::string getInfo(const unsigned int indent = 0) const;

                private:
                bool _isRunning;
                sf::Clock _clock;
            };

            /**
             * @brief Outputs the clock's info to a stream.
             * @param os The output stream.
             * @param item The clock to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Clock &item);
        }
    }
}


