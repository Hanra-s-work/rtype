/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Debug.hpp
*/

/**
 * @file Debug.hpp
 * @brief This is the file in charge of containing the Debug class (the one in charge of outputing info only when asked to)
 */

#pragma once
#include <ctime>
#include <mutex>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "MyRecodes.hpp"


 /**
  * @class Debug
  * @brief A singleton class that provides thread-safe logging capabilities
  * with timestamps, active only when debugging is enabled.
  */
class Debug {
    public:
    /**
     * @brief Provides access to the singleton instance of the `Debug` class.
     * @return Reference to the `Debug` instance.
     */
    static Debug &getInstance();

    /**
     * @brief Enables or disables the debug logging.
     * @param enabled Set to `true` to enable debugging; `false` to disable.
     */
    void setDebugEnabled(bool enabled);

    /**
     * @brief Logs a message if debugging is enabled.
     * @param message The message to log.
     */
    void log(const std::string &message);

    /**
     * @brief Logs a message if debugging is enabled.
     * @param message A C-string containing the message to log.
     */
    void log(const char *message);

    /**
     * @brief Appends a message to the debug log if debugging is enabled.
     * @tparam T The type of the message.
     * @param message The message to log.
     * @return Reference to the `Debug` instance for chaining.
     * @warning Do not try and initialise it outside of the header file or compilation issues will occur.
     */
    template <typename T>
    Debug &operator<<(const T &message)
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            _buffer << message;
        }
        return *this;
    };

    /**
     * @brief Appends a string message to the debug log if debugging is enabled.
     * @param message The string message to log.
     * @return Reference to the `Debug` instance for chaining.
     */
    Debug &operator<<(const std::string &message)
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            _buffer << message;
        }
        return *this;
    };

    /**
     * @brief Handles special stream manipulators (e.g., `std::endl`)
     * for logging with timestamps if debugging is enabled.
     * @param os The stream manipulator to apply.
     * @return Reference to the `Debug` instance for chaining.
     */
    Debug &operator<<(std::ostream &(*os)(std::ostream &))
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            if (os == static_cast<std::ostream & (*)(std::ostream &)>(std::endl)) {
                std::cout << getCurrentDateTime() << " DEBUG: " << _buffer.str() << std::endl;
                _buffer.str("");
                _buffer.clear();
            } else {
                os(_buffer);
            }
        }
        return *this;
    };


    private:
    bool _debugEnabled;               ///< Indicates whether debugging is enabled.
    std::mutex _mtx;                  ///< Ensures thread-safe access to the logging buffer.
    std::ostringstream _buffer;       ///< Buffer for accumulating messages before output.

    /**
     * @brief Private constructor for singleton pattern. Debugging is disabled by default.
     */
    Debug() : _debugEnabled(false) {}

    Debug(const Debug &) = delete;            ///< Deleted copy constructor.
    Debug &operator=(const Debug &) = delete; ///< Deleted assignment operator.

    /**
     * @brief Retrieves the current date and time as a formatted string.
     * @return The current date and time in "YYYY-MM-DD HH:MM:SS" format.
     */
    std::string getCurrentDateTime();
};
