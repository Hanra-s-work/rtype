#include "server.hpp"

// We'll define a special message type for registering logic:
static const uint16_t REGISTER_LOGIC = 100;

Server::Server(asio::io_context& io,
               unsigned short clientPort,
               unsigned short logicPort)
    : io_context_(io)
    , client_socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), clientPort))
    , logic_socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), logicPort))
    , client_manager_(std::make_shared<ClientManager>())
    , logic_manager_(std::make_shared<LogicManager>())
{
    std::cout << "[Server] Listening for clients on port " << clientPort 
              << ", logic on port " << logicPort << "\n";

    // Start receiving
    doReceiveFromClients();
    doReceiveFromLogic();
}

void Server::doReceiveFromClients() {
    client_socket_.async_receive_from(
        asio::buffer(client_recv_buffer_), client_remote_endpoint_,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handleClientMessage(bytes_recvd);
            }
            doReceiveFromClients();
        }
    );
}

void Server::handleClientMessage(std::size_t bytes_recvd) {
    Message msg;
    if (!decodeMessage(client_recv_buffer_.data(), bytes_recvd, msg)) {
        std::cout << "[Server] Invalid client message (decode failed)\n";
        return;
    }

    // Identify the client
    uint32_t clientId = client_manager_->resolveClientID(client_remote_endpoint_);

    // Ensure assigned to a logic instance
    uint32_t logicId = logic_manager_->getLogicIdForClient(clientId);
    if (logicId == 0) {
        // Not assigned => try to assign
        logicId = logic_manager_->assignClientToLogic(clientId);
        if (logicId == 0) {
            std::cout << "[Server] No logic available for clientId=" << clientId << "\n";
            // Optionally send a "no logic" or "server full" message to the client
            return;
        }
    }

    // Forward the message to that logic
    auto logicEndpoint = logic_manager_->getLogicEndpointForClient(clientId);
    if (logicEndpoint == asio::ip::udp::endpoint()) {
        std::cout << "[Server] Error: clientId=" << clientId 
                  << " has no valid logic endpoint\n";
        return;
    }

    auto outBuf = encodeMessage(msg);
    logic_socket_.async_send_to(
        asio::buffer(outBuf), 
        logicEndpoint,
        [](std::error_code ec, std::size_t bytesSent) {
            if (ec) {
                std::cout << "[Server] Error sending to logic: " 
                          << ec.message() << "\n";
            }
        }
    );
}

void Server::doReceiveFromLogic() {
    logic_socket_.async_receive_from(
        asio::buffer(logic_recv_buffer_), logic_remote_endpoint_,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handleLogicMessage(bytes_recvd);
            }
            doReceiveFromLogic();
        }
    );
}

void Server::handleLogicMessage(std::size_t bytes_recvd) {
    Message msg;
    if (!decodeMessage(logic_recv_buffer_.data(), bytes_recvd, msg)) {
        std::cout << "[Server] Invalid logic message (decode failed)\n";
        return;
    }

    // If logic is registering, store it
    if (msg.type == REGISTER_LOGIC) {
        uint32_t logicId = logic_manager_->registerLogicInstance(logic_remote_endpoint_);
        std::cout << "[Server] Logic " << logic_remote_endpoint_ 
                  << " registered with logicId=" << logicId << "\n";
        return;
    }

    // Otherwise, it's a normal game update
    // Find all clients assigned to this logic endpoint
    auto clientIds = logic_manager_->getClientsForLogicEndpoint(logic_remote_endpoint_);
    for (auto cid : clientIds) {
        auto clientEp = client_manager_->getEndpoint(cid);
        if (clientEp != asio::ip::udp::endpoint()) {
            auto outBuf = encodeMessage(msg);
            client_socket_.async_send_to(
                asio::buffer(outBuf),
                clientEp,
                [](std::error_code ec, std::size_t bytesSent) {
                    if (ec) {
                        std::cout << "[Server] Error sending to client: " 
                                  << ec.message() << "\n";
                    }
                }
            );
        }
    }
}
