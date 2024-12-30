/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Log.cpp
*/

/**
 * @file Log.cpp
 * @brief This is the file in charge of managing the functions for the debug class
 */

#include "Log.hpp"

Log &Log::getInstance()
{
    static Log instance;
    return instance;
}

std::string Log::getLogLocation(const char *file, int line, const char *func)
{
    std::ostringstream oss;
    oss << file << ":" << line << " " << func << "()";
    return oss.str();
}

void Log::setLogEnabled(bool enabled)
{
    _debugEnabled = enabled;
}

void Log::log(const std::string &message)
{
    if (_debugEnabled) {
        std::lock_guard<std::mutex> lock(_mtx);
        std::cout << getCurrentDateTime() << message << std::endl;
    }
}

void Log::log(const char *message)
{
    log(std::string(message));
}

std::string Log::getCurrentDateTime()
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
