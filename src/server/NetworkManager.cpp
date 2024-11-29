/*
** EPITECH PROJECT, 2024
** NetworkManager.cpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client 
*/

#include "./includes/NetworkManager.hpp"
#include <iostream>

void NetworkManager::Initialize() {
    std::cout << "Initializing network in progress" << std::endl;
}

void NetworkManager::HandleMessages() {
    // std::cout << "Handling messages in progress" << std::endl;
}

void NetworkManager::SendMessage(const std::string& message, const std::string& address) {
    std::cout << "Sending message: " << message << " to " << address << std::endl;
}


