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

void Debug::log(const std::string &message)
{
    if (_debugEnabled) {
        std::lock_guard<std::mutex> lock(_mtx);
        std::cout << getCurrentDateTime() << " DEBUG: " << message << std::endl;
    }
}

void Debug::log(const char *message)
{
    log(std::string(message));
}

std::string Debug::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count() % 1000;


    std::tm *tm = std::localtime(&currentTime);

    std::stringstream ss;
    ss << "[" << (tm->tm_year + 1900) << "-"
        << (tm->tm_mon + 1) << "-"
        << tm->tm_mday << " "
        << tm->tm_hour << ":"
        << tm->tm_min << ":"
        << tm->tm_sec << "."
        << std::setfill('0') << std::setw(3) << millis << "]";
    return ss.str();
}
