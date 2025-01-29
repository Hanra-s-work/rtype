#include "NetworkManager.hpp"
#include "GameWorld.hpp"
#include <iostream>

static const unsigned short SERVER_PORT = 9000;

NetworkManager::NetworkManager()
{

}

NetworkManager::~NetworkManager()
{
    stop();
}

void NetworkManager::start()
{
    if (_running) return;
    _running = true;

    _socket = std::make_unique<asio::ip::udp::socket>(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), SERVER_PORT));

    doReceive();

    const size_t THREAD_COUNT = 2;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        _ioThreads.emplace_back([this]() {
            try {
                _ioContext.run();
            } catch (std::exception& e) {
                std::cerr << "IOContext thread exception: " << e.what() << std::endl;
            }
        });
    }
    std::cout << "NetworkManager started on port " << SERVER_PORT << "\n";
}

void NetworkManager::stop()
{
    if (!_running) return;
    _running = false;

    if (_socket) {
        asio::error_code ec;
        _socket->close(ec);
    }
    _ioContext.stop();

    for (auto &t : _ioThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    _ioThreads.clear();

    std::cout << "NetworkManager stopped\n";
}

void NetworkManager::pollMessages(GameWorld& gameWorld)
{

}

void NetworkManager::broadcastState(const GameWorld& gameWorld)
{

}

void NetworkManager::doReceive()
{
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    _socket->async_receive_from(
        asio::buffer(*buffer), *senderEndpoint,
        [this, buffer, senderEndpoint](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::string data(buffer->data(), bytes_recvd);

                onDataReceived(data, *senderEndpoint);
            }
            if (_running) {
                doReceive();
            }
        }
    );
}

void NetworkManager::onDataReceived(const std::string& data, const asio::ip::udp::endpoint& senderEndpoint)
{
    bool knownClient = false;
    for (auto& c : _clients) {
        if (c == senderEndpoint) {
            knownClient = true;
            break;
        }
    }
    if (!knownClient) {
        _clients.push_back(senderEndpoint);
        std::cout << "New client connected: " << senderEndpoint << "\n";
    }
}