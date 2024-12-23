/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** tomlLoader.hpp
*/

/**
 * @file TOMLLoader.hpp
 * @brief This is the file in charge of containing the class that will handle the loading and navigation of the TOML language.
 */

#pragma once

#include <string>
#include <vector>
#include <toml++/toml.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"

class TOMLLoader {
    public:
    TOMLLoader() = default;
    TOMLLoader(const std::string &tomlPath);

    ~TOMLLoader() = default;

    void setTOMLPath(const std::string &tomlPath);

    bool isTOMLLoaded() const;

    std::string getTOMLPath() const;

    toml::table getRawTOML() const;

    template <typename T>
    T getValue(const std::string &key) const;

    bool hasKey(const std::string &key) const;

    std::vector<std::string> getKeys() const;

    toml::table getTable(const std::string &key) const;

    toml::array getArray(const std::string &key) const;

    void printTOML() const;

    template <typename T>
    TOMLLoader &operator<<(const T &message);
    TOMLLoader &operator<<(const std::string &message);
    TOMLLoader &operator<<(std::ostream &(*os)(std::ostream &));

    private:
    void _loadTOML();
    void _ensureLoaded() const;

    std::string _tomlPath;
    bool _tomlLoaded = false;
    toml::table _toml;
    std::string _tomlString = "";
};
