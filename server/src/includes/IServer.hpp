/*
** EPITECH PROJECT, 2024
** IServer.hpp
** File description:
** Interface that build server
*/

#ifndef ISERVER_H
    #define ISERVER_H

    #include <string>

    class IServer {
        public:
            virtual ~IServer() = default;
            virtual void Build() = 0;
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void SendMessage(const std::string& message, const std::string& address) = 0;
            virtual void HandleMessages() = 0;
    };

#endif // ISERVER_H
