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


 /**
  *@brief The Debug class in charge of displaying information
  * only if the _debugEnabled is set to true.
  * It is designed to be used globally throughout the program.
  *
  */
class Debug {
    public:
    static Debug &getInstance();

    /**
     *@brief Set the Debug Enabled value to true or false.
     *
     * @param enabled
     */
    void setDebugEnabled(bool enabled);

    /**
     *@brief A logging function for if called in an non-overloading manner.
     *
     * @param message
     */
    void log(const std::string &message);

    /**
     *@brief A logging function for if called in an non-overloading manner.
     *
     * @param message
     */
    void log(const char *message);

    /**
     *@brief This function is used to log a message with a
     * timestamp is the debug mode is activated.
     *
     * @tparam T
     * @param message
     * @return Debug&
     */
    template <typename T>
    Debug &operator<<(const T &message)
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            _buffer << message; // Write to buffer instead of cout
        }
        return *this;
    }

    /**
     *@brief This is the overload to allow the debug function
     * to output a messsage if the debug mode is activated.
     *
     * @param os
     * @return Debug&
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
    }

    private:
    bool _debugEnabled;
    std::mutex _mtx;
    std::ostringstream _buffer;

    Debug() : _debugEnabled(false) {};
    Debug(const Debug &) = delete;
    Debug &operator=(const Debug &) = delete;
    std::string getCurrentDateTime();
};
