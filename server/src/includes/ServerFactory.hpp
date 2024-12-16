/*
** EPITECH PROJECT, 2024
** ServerFactory.hpp
** File description:
** Use IServer interface to build the server
*/

#ifndef SERVER_FACTORY_H
    #define SERVER_FACTORY_H

    #include "./IServer.hpp"
    #include "./Server.hpp"

    class ServerFactory {
        public:
            static IServer* CreateServer() {
                return new Server();
            }
    };

#endif // SERVER_FACTORY_H
