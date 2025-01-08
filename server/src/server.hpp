#pragma once

#include <asio.hpp>
#include <memory>
#include <array>
#include "game_manager.hpp"
#include "client_manager.hpp"
#include "message.hpp"
#include "message_codec.hpp"

/**
 * @class Server
 * @brief The main UDP server class that listens for client messages and routes them to the GameManager.
 *
 * The Server uses asynchronous I/O with Asio to receive incoming packets on a UDP socket.
 * Each packet is decoded and handed to the appropriate methods in the GameManager and ClientManager.
 */
class Server : public std::enable_shared_from_this<Server> {
public:
    /**
     * @brief Constructs the Server and binds the UDP socket to the given port.
     * @param io The Asio io_context to use for asynchronous operations.
     * @param port The UDP port on which to listen (e.g., 9000).
     */
    Server(asio::io_context& io, unsigned short port);

    /**
     * @brief Provides access to the GameManager that manages multiple games.
     * @return A reference to the GameManager instance.
     */
    GameManager& getGameManager() { return gameManager_; }

private:
    /**
     * @brief Initiates an asynchronous receive operation to listen for incoming packets.
     */
    void doReceive();

    /**
     * @brief Called when a packet is successfully received. Decodes and processes the message.
     * @param bytesReceived The number of bytes in the received packet.
     */
    void handleMessage(std::size_t bytesReceived);

    /// The UDP socket used to listen/send data.
    asio::ip::udp::socket socket_;

    /// The endpoint from which the latest packet was received.
    asio::ip::udp::endpoint remoteEndpoint_;

    /// Buffer to store incoming data.
    std::array<char, 2048> recvBuffer_;

    /// Tracks client endpoints and their assigned IDs.
    ClientManager clientManager_;

    /// Manages multiple GameLogic instances (multiple games).
    GameManager gameManager_;
};
