/*
** EPITECH PROJECT, 2024
** GameManager.cpp
** File description:
** Handle game logic
*/

#include "./includes/GameManager.hpp"
#include "Registry.hpp"
#include <iostream>

void GameManager::Initialize() {
    std::cout << "Initializing game manager in progress" << std::endl;
    game = new Registry();
}

void GameManager::Update(float deltaTime) {
    std::cout << "Updating game logic with deltaTime: " << deltaTime << "s." << std::endl;
    game->run_systems();
}
