/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client 
*/

#ifndef NETWORK_MANAGER_H
    #define NETWORK_MANAGER_H

    #include <string>

    class NetworkManager {
        public:
            void Initialize();
            void HandleMessages();
            void SendMessage(const std::string& message, const std::string& address);
    };

#endif // NETWORK_MANAGER_H
