/*
** EPITECH PROJECT, 2024
** Server.hpp
** File description:
** Handle Server methods
*/

#ifndef SERVER_H
    #define SERVER_H

    #include "./NetworkManager.hpp"
    #include "./GameManager.hpp"
    #include "./ThreadPool.hpp"
    #include "./IServer.hpp"

    class Server : public IServer {
        public:
            Server();
            ~Server();

            void Build() override;
            void Start() override;
            void Stop() override;
            void SendMessage(const std::string& message, const std::string& address) override;
            void HandleMessages() override;

        private:
            void RunLoop();

            bool running;
            NetworkManager networkManager;
            GameManager gameManager;
            ThreadPool threadPool;
    };

#endif // SERVER_H
