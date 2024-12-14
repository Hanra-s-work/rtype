/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Debug.cpp
*/

#include "Debug.hpp"

Debug &Debug::getInstance()
{
    static Debug instance;
    return instance;
}

void Debug::setDebugEnabled(bool enabled)
{
    _debugEnabled = enabled;
}

template <typename T>
Debug &Debug::operator<<(const T &message)
{
    if (_debugEnabled) {
        std::lock_guard<std::mutex> lock(_mtx);
        std::cout << getCurrentDateTime() << " DEBUG: " << message;
    }
    return *this;
}

Debug &Debug::operator<<(std::ostream &(*os)(std::ostream &))
{
    if (_debugEnabled) {
        std::lock_guard<std::mutex> lock(_mtx);
        os(std::cout);  // Apply the manipulator (e.g., std::endl)
    }
    return *this;
}

void Debug::log(const std::string &message)
{
    if (_debugEnabled) {
        std::cout << getCurrentDateTime() << " DEBUG: " << message << std::endl;
    }
}

void Debug::log(const char *message)
{
    if (_debugEnabled) {
        std::cout << getCurrentDateTime() << " DEBUG: " << message << std::endl;
    }
}

std::string Debug::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *tm = std::localtime(&currentTime);

    std::stringstream ss;
    ss << "[" << (tm->tm_year + 1900) << "-"
        << (tm->tm_mon + 1) << "-"
        << tm->tm_mday << " "
        << tm->tm_hour << ":"
        << tm->tm_min << ":"
        << tm->tm_sec << "]";
    return ss.str();
}
