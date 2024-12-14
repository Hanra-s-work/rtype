/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Debug.hpp
*/

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <mutex>

class Debug {
    public:
    static Debug &getInstance();

    void setDebugEnabled(bool enabled);

    void log(const std::string &message);
    void log(const char *message);

    template <typename T>
    Debug &operator<<(const T &message);
    Debug &operator<<(std::ostream &(*os)(std::ostream &));

    private:
    bool _debugEnabled;
    std::mutex _mtx;

    Debug() : _debugEnabled(false) {};
    Debug(const Debug &) = delete;
    Debug &operator=(const Debug &) = delete;
    std::string getCurrentDateTime();
};
