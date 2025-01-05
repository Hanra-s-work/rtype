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

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @class Clock
             * @brief A class for managing time tracking within the ECS system.
             *
             * This class extends EntityNode and provides functionality for managing time, including
             * starting, stopping, resetting, and getting the elapsed time. It also supports debug information
             * output through the `getInfo` method.
             */
            class Clock : public EntityNode {
                public:
                /**
                 * @brief Construct a new Clock object.
                 *
                 * @param entityId The ID of the entity associated with this Clock. Defaults to 0.
                 */
                Clock(const std::uint32_t entityId = 0);
                /**
                 * @brief Destroy the Clock object.
                 */
                ~Clock();
                /**
                 * @brief Resets the clock and returns the elapsed time since the last reset.
                 *
                 * @return The elapsed time in microseconds as a signed 64-bit integer.
                 */
                const std::int64_t reset();
                /**
                 * @brief Gets the elapsed time since the clock was last reset.
                 *
                 * @return The elapsed time in microseconds as a signed 64-bit integer.
                 */
                const std::int64_t getElapsedTime() const;
                /**
                 * @brief Stops the clock.
                 */
                void stop();
                /**
                 * @brief Starts the clock.
                 */
                void start();
                /**
                 * @brief Checks if the clock is currently running.
                 *
                 * @return `true` if the clock is running, `false` otherwise.
                 */
                const bool isRunning() const;
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

                private:
                bool _isRunning;   //!< Tracks whether the clock is currently running.
                sf::Clock _clock;  //!< The underlying SFML Clock used for time management.
            };

            /**
             * @brief Outputs the clock's info to a stream.
             *
             * @param os The output stream.
             * @param item The clock to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Clock &item);
        }
    }
}


