/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TOMLLoader.cpp
*/

/**
 * @file TOMLLoader.cpp
 * @brief This is the file in charge of containing the functions for the class that will handle the loading and navigation of the TOML language.
 */

#include "TOMLLoader.hpp"

TOMLLoader::TOMLLoader(const std::string &tomlPath)
{
    setTOMLPath(tomlPath);
};

void TOMLLoader::setTOMLPath(const std::string &tomlPath)
{
    _tomlPath = tomlPath;
    _loadTOML();
};

bool TOMLLoader::isTOMLLoaded() const { return _tomlLoaded; };

std::string TOMLLoader::getTOMLPath() const
{
    return _tomlPath;
};

toml::table TOMLLoader::getRawTOML() const
{
    _ensureLoaded();
    return _toml;
};

template <typename T>
T TOMLLoader::getValue(const std::string &key) const
{
    _ensureLoaded();
    if (auto value = _toml[key].value<T>()) {
        return *value;
    }
    throw MyException::NoTOMLKey(_tomlPath, key);
};

bool TOMLLoader::hasKey(const std::string &key) const
{
    _ensureLoaded();
    return _toml.contains(key);
};

std::vector<std::string> TOMLLoader::getKeys() const
{
    _ensureLoaded();
    std::vector<std::string> keys;
    for (const auto &[key, _] : _toml) {
        keys.push_back(std::string(key));
    }
    return keys;
};

toml::table TOMLLoader::getTable(const std::string &key) const
{
    _ensureLoaded();
    if (auto table = _toml[key].as_table()) {
        return *table;
    }
    throw MyException::NoTOMLKey(_tomlPath, key);
};

toml::array TOMLLoader::getArray(const std::string &key) const
{
    _ensureLoaded();
    if (auto array = _toml[key].as_array()) {
        return *array;
    }
    throw MyException::NoTOMLKey(_tomlPath, key);
};

void TOMLLoader::printTOML() const
{
    _ensureLoaded();
    Debug::getInstance() << "TOML Contents:\n" + _tomlString << std::endl;
};

template <typename T>
TOMLLoader &TOMLLoader::operator<<(const T &message)
{
    _ensureLoaded();
    std::lock_guard<std::mutex> lock(_mtx);
    _buffer << message;
    return *this;
};

TOMLLoader &TOMLLoader::operator<<(const std::string &message)
{
    _ensureLoaded();
    std::lock_guard<std::mutex> lock(_mtx);
    _buffer << message;
    return *this;
};

TOMLLoader &TOMLLoader::operator<<(std::ostream &(*os)(std::ostream &))
{
    _ensureLoaded();
    std::cout << _tomlString << os;
    return *this;
};

void TOMLLoader::_loadTOML()
{
    _tomlLoaded = false;
    try {
        _toml = toml::parse_file(_tomlPath);
    }
    catch (const toml::parse_error &e) {
        throw MyException::InvalidTOML(_tomlPath, e.what());
    }
    std::ostringstream oss;
    oss << _toml;
    _tomlString = oss.str();
    _tomlLoaded = true;
};

void TOMLLoader::_ensureLoaded() const
{
    if (!_tomlLoaded) {
        throw MyException::NoTOML(_tomlPath);
    }
};



