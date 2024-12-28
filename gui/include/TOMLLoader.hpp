/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** tomlLoader.hpp
*/

/**
 * @file TOMLLoader.hpp
 * @brief Contains the TOMLLoader class responsible for handling loading and navigation of the TOML format.
 */


#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <toml++/toml.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"

 /**
  * @class TOMLLoader
  * @brief A utility class for loading, navigating, and interacting with TOML files.
  */
class TOMLLoader {
    public:
    TOMLLoader();
    TOMLLoader(const std::string &tomlPath);
    TOMLLoader(const TOMLLoader &tomlInstance);
    TOMLLoader(const toml::table &tomlTable, const std::string &tomlPath);
    TOMLLoader(const toml::array &tomlArray, const std::string &tomlPath);
    TOMLLoader(const toml::array &tomlArray, const std::string &key, const std::string &tomlPath);

    ~TOMLLoader() = default;

    void setTOMLPath(const std::string &tomlPath);

    const bool isTOMLLoaded() const;

    const std::string getTOMLPath() const;

    const std::string getTOMLString() const;

    const toml::table getRawTOML() const;

    // Do not move this function code or compilation issues will arise.
    template <typename T>
    T getValue(const std::string &key) const
    {
        _ensureLoaded();
        if (auto value = _toml[key].value<T>()) {
            return *value;
        }
        throw MyException::NoTOMLKey(_tomlPath, key);
    };

    const toml::node_type getValueType(const std::string &key) const;

    const std::string getValueTypeAsString(const std::string &key) const;

    const std::string getTypeAsString(const std::string &key) const;
    const std::string getTypeAsString(const toml::node_type &type) const;

    const bool hasKey(const std::string &key) const;

    std::vector<std::string> getKeys() const;

    toml::table getTable(const std::string &key) const;

    toml::array getArray(const std::string &key) const;

    void update(const TOMLLoader &copy);
    void update(const toml::table &copy);
    void update(const toml::array &copy);
    void update(const toml::array &copy, const std::string &key);

    void printTOML() const;

    TOMLLoader &operator=(const TOMLLoader &copy);
    TOMLLoader &operator=(const toml::table &copy);
    TOMLLoader &operator=(const toml::array &copy);

    private:
    void _loadTOML();
    void _ensureLoaded() const;
    void _loadNodeTypeEquivalence();

    toml::table _toml;
    bool _tomlLoaded = false;
    std::string _tomlPath = "";
    std::string _tomlString = "";

    std::mutex _mtx;
    std::ostringstream _buffer;
    std::unordered_map<toml::node_type, std::string> _nodeTypeEquivalence;
};

std::ostream &operator<<(std::ostream &os, const TOMLLoader &node);
