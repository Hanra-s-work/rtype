#pragma once

/**
 * @class InputManager
 * @brief A singleton class for managing and mapping input actions to keys.
 *
 * The InputManager class provides a centralized system for registering and handling
 * keyboard input. It allows developers to assign custom string names to keys and
 * check if those keys are pressed. This class is implemented as a singleton to ensure
 * that only one instance exists across the application.
 */

#include <unordered_map>
#include <string>
#include <SFML/Window/Keyboard.hpp>

class InputManager {
private:
    static InputManager* instance;
    std::unordered_map<std::string, sf::Keyboard::Key> keyMap;
    InputManager() {}

public:
    static InputManager& getInstance();
    void registerKey(const std::string& name, sf::Keyboard::Key key);
    bool isKeyPressed(const std::string& name);

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
};
