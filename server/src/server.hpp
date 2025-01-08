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
 * @brief Asynchronous UDP server that accepts multiple clients and manages multiple Game instances.
 *
 * Binds to 0.0.0.0:<port> for LAN accessibility, uses async receive to handle client packets,
 * and forwards messages to the GameManager and ClientManager.
 */
class Server : public std::enable_shared_from_this<Server> {
public:
    /**
     * @brief Constructs the Server with a bound UDP socket on the given port.
     * @param io The Asio io_context for async I/O.
     * @param port The UDP port (e.g., 9000) for listening to client messages.
     */
    Server(asio::io_context& io, unsigned short port);

    /**
     * @brief Accessor to retrieve the GameManager (manages multiple Game instances).
     * @return Reference to the GameManager instance.
     */
    GameManager& getGameManager() { return gameManager_; }

private:
    /**
     * @brief Initiates an async receive operation for UDP packets.
     */
    void doReceive();

    /**
     * @brief Callback that processes a received packet (decodes and routes to game logic).
     * @param bytesReceived Number of bytes in the packet.
     */
    void handleMessage(std::size_t bytesReceived);

    /// UDP socket bound to 0.0.0.0:<port>.
    asio::ip::udp::socket socket_;

    /// Endpoint of the remote client who sent the current packet.
    asio::ip::udp::endpoint remoteEndpoint_;

    /// Buffer to store incoming packet data.
    std::array<char, 2048> recvBuffer_;

    /// Tracks endpoint <-> clientId mapping.
    ClientManager clientManager_;

    /// Manages multiple Game instances.
    GameManager gameManager_;
};
