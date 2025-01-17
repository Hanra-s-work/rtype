/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client
*/

/**
 * @file NetworkManager.hpp
 *
 * @brief This file defines the NetworkManager class, which handles UDP socket communication
 *        for sending and receiving messages between the server and the client.
 */

#pragma once

#include <string>
#include <vector>
#include <asio.hpp>
#include <sstream>
#include <array>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <cstring>

#include "ProtocolHandler.hpp"
#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace Network
    {
        /**
         * @class NetworkManager
         * @brief A class that manages the network communication through UDP sockets.
         *
         * This class is responsible for initializing the UDP socket, sending and receiving messages,
         * and interpreting messages between the client and server.
         * It can send and receive messages in various formats and manage the connection state.
         */
        class NetworkManager : public GUI::ECS::EntityNode {
            public:
            /**
             * @brief Constructs a NetworkManager instance with an optional entity ID.
             * @param entityId The unique identifier for the entity (default is 0).
             */
            NetworkManager(const std::uint32_t entityId = 0);
            /**
             * @brief Initializes the UDP socket and binds it to a local endpoint.
             * This function opens the socket and binds it to the specified port.
             * If initialization fails, an error message will be printed.
             */
            void Initialize();
            /**
             * @brief Handles incoming messages on the UDP socket.
             *
             * This function listens for messages from the server, deserializes them, and processes the received data.
             */
            void HandleMessages();
            /**
             * @brief Sends a message to the server.
             * @param message The message to send.
             *
             * This function will check if the socket is connected, validate the message size,
             * and send the message to the server.
             */
            void SendMessage(const std::string &message);

            /**
             * @brief Sets the port for communication.
             * @param port The port number to set.
             */
            void setPort(const unsigned int port);
            /**
             * @brief Sets the IP address for communication.
             * @param ip The IP address to set.
             */
            void setIp(const std::string &ip);
            /**
             * @brief Sets the player's name for identification.
             * @param name The player's name.
             */
            void setPlayerName(const std::string &name);
            /**
             * @brief Sets both the IP address and port for communication.
             * @param ip The IP address to set.
             * @param port The port number to set.
             */
            void setAddress(const std::string &ip, const unsigned int port);

            /**
             * @brief Checks if the connection is active.
             * @return True if the socket is open and connected, false otherwise.
             */
            const bool isConnected() const;

            /**
             * @brief Converts a byte array to a floating-point value.
             * @param bytes Pointer to the byte array representing a float.
             * @return The corresponding floating-point value.
             */
            float bytesToFloat(const uint8_t *bytes);
            /**
             * @brief Converts a byte array to a hexadecimal string representation.
             * @param bytes The byte array to convert.
             * @return The hexadecimal string representing the byte array.
             */
            std::string bytesToHex(const std::vector<uint8_t> &bytes);
            /**
             * @brief Translates a message into a human-readable string format.
             * @param message The byte array representing the message.
             * @return A string representation of the message.
             *
             * This function decodes different message types such as connect, disconnect, move, shoot, etc.
             * and returns a description of the message contents.
             */
            std::string translateMessage(const std::vector<uint8_t> &message);
            /**
             * @brief Receives messages continuously from the server.
             *
             * This function waits for incoming messages and processes them by calling
             * `translateMessage()` to display them in a human-readable format.
             */
            void receiveMessage();

            private:
            /**
             * @brief Establishes a connection to the server using the specified IP and port.
             *
             * This function opens the UDP socket and sends a connection request to the server.
             */
            void _connect();
            /**
             * @brief Disconnects from the server by closing the UDP socket.
             *
             * This function closes the socket and marks the connection as inactive.
             */
            void _disconnect();

            bool _connectionActive = false;                                     //!< Flag indicating the connection status.
            unsigned int _port = -1;                                            //!< The port number for communication.
            std::string _ip = "127.0.0.1";                                      //!< The IP address for the server.
            std::string _playerName = "Player";                                 //!< The name of the player.
            asio::io_context _ioContext;                                        //!< The ASIO IO context for network operations.
            asio::ip::udp::socket _socket{ _ioContext };                        //!< The UDP socket for communication.
        };
    }
}
