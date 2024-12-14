/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Debug.hpp
*/

#pragma once
#include <ctime>
#include <mutex>
#include <string>
#include <chrono>
#include <sstream>
#include <iostream>

class Debug {
    public:
    static Debug &getInstance();

    void setDebugEnabled(bool enabled);

    void log(const std::string &message);
    void log(const char *message);

    template <typename T>
    Debug &operator<<(const T &message)
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            std::cout << getCurrentDateTime() << " DEBUG: " << message;
        }
        return *this;
    }

    Debug &operator<<(std::ostream &(*os)(std::ostream &))
    {
        if (_debugEnabled) {
            std::lock_guard<std::mutex> lock(_mtx);
            os(std::cout);
        }
        return *this;
    }

    private:
    bool _debugEnabled;
    std::mutex _mtx;

    Debug() : _debugEnabled(false) {};
    Debug(const Debug &) = delete;
    Debug &operator=(const Debug &) = delete;
    std::string getCurrentDateTime();
};
