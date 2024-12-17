/*
** EPITECH PROJECT, 2024
** Server.cpp
** File description:
** Handle Server methods
*/

#include "./includes/Server.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Server::Server() : running(false) {}

Server::~Server() {
    Stop();
}

void Server::Build() {
    networkManager.Initialize();
    gameManager.Initialize();
    threadPool.Initialize();
    std::cout << "Server components build : ✅" << std::endl;
}

void Server::Start() {
    running = true;
    std::cout << "Server started : ✅" << std::endl;
    RunLoop();
}

void Server::Stop() {
    std::cout << "Server stopped : ✅" << std::endl;
    running = false;
    threadPool.Shutdown();
}

void Server::SendMessage(const std::string& message, const std::string& address) {
    networkManager.SendMessage(message, address, 4242);
}

void Server::HandleMessages() {
    networkManager.HandleMessages();
}

void Server::RunLoop() {
    while (running) {
        auto startTime = std::chrono::steady_clock::now();

        HandleMessages();
        gameManager.Update(0.016f);

        auto endTime = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(16) - (endTime - startTime));
    }
}
