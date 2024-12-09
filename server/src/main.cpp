/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** Build & start the server using the interface
*/

#include "./includes/IServer.hpp"
#include "./includes/ServerFactory.hpp"

int main() {
    IServer* server = ServerFactory::CreateServer();
    server->Build();
    server->Start();
    delete server;
    return 0;
}

