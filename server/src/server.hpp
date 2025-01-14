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
 * @brief The main UDP server that accepts client messages and updates the game logic.
 */
class Server : public std::enable_shared_from_this<Server> {
public:
    /**
     * @brief Constructs the Server, binding a UDP socket to the specified port.
     * @param io The Asio io_context for async operations.
     * @param port The UDP port for listening (e.g. 9000).
     */
    Server(asio::io_context& io, unsigned short port);

    /**
     * @brief Accessor for the GameManager that manages multiple games.
     * @return Reference to the GameManager instance.
     */
    GameManager& getGameManager() { return gameManager_; }

    /**
     * @brief Sends a Message to a specific client by ID (uses clientManager to find endpoint).
     * @param clientId The unique ID of the client.
     * @param msg The message to send.
     */
    void sendToClient(uint32_t clientId, const Message& msg);

private:
    /**
     * @brief Initiates an asynchronous receive operation.
     */
    void doReceive();

    /**
     * @brief Callback when a packet is received.
     * @param bytesReceived The size of the received packet in bytes.
     */
    void handleMessage(std::size_t bytesReceived);

    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remoteEndpoint_;

    std::array<char, 2048> recvBuffer_;

    ClientManager clientManager_;
    GameManager   gameManager_;
};
