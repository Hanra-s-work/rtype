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

TOMLLoader::TOMLLoader()
{
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const std::string &tomlPath)
{
    setTOMLPath(tomlPath);
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const TOMLLoader &tomlInstance)
{
    update(tomlInstance);
};

TOMLLoader::TOMLLoader(const toml::table &tomlTable, const std::string &tomlPath)
{
    _toml = tomlTable;
    _tomlLoaded = true;
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const toml::array &tomlArray, const std::string &tomlPath)
{
    _tomlLoaded = true;
    update(tomlArray);
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
};

TOMLLoader::TOMLLoader(const toml::array &tomlArray, const std::string &key, const std::string &tomlPath)
{
    _tomlLoaded = true;
    update(tomlArray);
    _tomlPath = tomlPath;
    _loadNodeTypeEquivalence();
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

toml::node_type TOMLLoader::getValueType(const std::string &key) const
{
    _ensureLoaded();
    if (!hasKey(key)) {
        throw MyException::NoTOMLKey(_tomlPath, key);
    }
    return _toml[key].type();
}

std::string TOMLLoader::getValueTypeAsString(const std::string &key) const
{
    _ensureLoaded();
    toml::node_type nodeType = getValueType(key);
    auto it = _nodeTypeEquivalence.find(nodeType);
    if (it != _nodeTypeEquivalence.end()) {
        return it->second;
    }
    return "unknown";
}

std::string TOMLLoader::getTypeAsString(const toml::node_type &type) const
{
    auto it = _nodeTypeEquivalence.find(type);
    if (it != _nodeTypeEquivalence.end()) {
        return it->second;
    }
    return "unknown";
}

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

void TOMLLoader::update(const TOMLLoader &copy)
{
    _tomlLoaded = copy.isTOMLLoaded();
    if (!_tomlLoaded) {
        return;
    }
    _tomlPath = copy.getTOMLPath();
    _toml = copy.getRawTOML();
}

void TOMLLoader::update(const toml::table &copy)
{
    _toml = copy;
    _tomlLoaded = true;
}

void TOMLLoader::update(const toml::array &copy)
{
    _toml = toml::table{ {"array", copy} };
    _tomlLoaded = true;
}

void TOMLLoader::update(const toml::array &copy, const std::string &key)
{
    _toml = toml::table{ {key, copy} };
    _tomlLoaded = true;
}

void TOMLLoader::printTOML() const
{
    _ensureLoaded();
    Debug::getInstance() << "TOML Contents:\n" + _tomlString << std::endl;
};

// template <typename T>
// TOMLLoader &TOMLLoader::operator<<(const T &message)
// {
//     _ensureLoaded();
//     std::lock_guard<std::mutex> lock(_mtx);
//     _buffer << message;
//     return *this;
// };

// TOMLLoader &TOMLLoader::operator<<(const std::string &message)
// {
//     _ensureLoaded();
//     std::lock_guard<std::mutex> lock(_mtx);
//     _buffer << message;
//     return *this;
// };

// TOMLLoader &TOMLLoader::operator<<(std::ostream &(*os)(std::ostream &))
// {
//     _ensureLoaded();
//     std::cout << _tomlString << os;
//     return *this;
// };

TOMLLoader &TOMLLoader::operator=(const TOMLLoader &copy)
{
    update(copy);
    return *this;
}

TOMLLoader &TOMLLoader::operator=(const toml::table &copy)
{
    update(copy);
    return *this;
}

TOMLLoader &TOMLLoader::operator=(const toml::array &copy)
{
    update(copy);
    return *this;
}

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

void TOMLLoader::_loadNodeTypeEquivalence()
{
    _nodeTypeEquivalence[toml::node_type::none] = "none";
    _nodeTypeEquivalence[toml::node_type::date] = "date";
    _nodeTypeEquivalence[toml::node_type::time] = "time";
    _nodeTypeEquivalence[toml::node_type::table] = "table";
    _nodeTypeEquivalence[toml::node_type::array] = "array";
    _nodeTypeEquivalence[toml::node_type::string] = "string";
    _nodeTypeEquivalence[toml::node_type::integer] = "integer";
    _nodeTypeEquivalence[toml::node_type::boolean] = "boolean";
    _nodeTypeEquivalence[toml::node_type::date_time] = "date_time";
    _nodeTypeEquivalence[toml::node_type::floating_point] = "floating_point";
}
