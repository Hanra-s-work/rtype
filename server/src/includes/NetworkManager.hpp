/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client 
*/

#ifndef NETWORK_MANAGER_H
    #define NETWORK_MANAGER_H

    #include <asio.hpp>
    #include <string>
    #include <vector>
    #include "ProtocolHandler.hpp"

    class NetworkManager {
        public:
            NetworkManager();
            void Initialize();
            void HandleMessages();
            void SendMessage(const std::string& message, const std::string& address, uint16_t port);

        private:
            asio::io_context ioContext;
            asio::ip::udp::socket socket{ioContext};
    };

#endif // NETWORK_MANAGER_H


