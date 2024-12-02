#include "InputManager.hpp"

InputManager *InputManager::instance = nullptr;

InputManager &InputManager::getInstance() {
    if (!instance) {
        instance = new InputManager();
    }
    return *instance;
}

void InputManager::registerKey(const std::string &name, sf::Keyboard::Key key) {
    keyMap[name] = key;
}

bool InputManager::isKeyPressed(const std::string &name) {
    auto it = keyMap.find(name);
    if (it != keyMap.end()) {
        return sf::Keyboard::isKeyPressed(it->second);
    }
    return false;
}
