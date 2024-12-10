/*
** EPITECH PROJECT, 2024
** NetworkManager.cpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client
*/

#include <iostream>
#include "GUI/Network/NetworkManager.hpp"

NetworkManager::NetworkManager() {}

void NetworkManager::Initialize()
{
    try {
        asio::ip::udp::endpoint localEndpoint(asio::ip::udp::v4(), 4242);
        socket.open(asio::ip::udp::v4());
        socket.bind(localEndpoint);
        std::cout << "UDP Socket initialized on port 4242" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error initializing UDP socket: " << e.what() << std::endl;
    }
}

void NetworkManager::HandleMessages()
{
    try {
        std::vector<uint8_t> buffer(1024);
        asio::ip::udp::endpoint senderEndpoint;

        size_t bytesReceived = socket.receive_from(asio::buffer(buffer), senderEndpoint);
        if (bytesReceived > 0) {
            std::vector<uint8_t> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
            Packet packet = Packet::deserialize(receivedData);
            /*// Debug part \\*/
            packet.print();
            /*// Debug part \\*/
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error handling messages: " << e.what() << std::endl;
    }
}

void NetworkManager::SendMessage(const std::string &message, const std::string &address, uint16_t port)
{
    try {
        asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(address), port);
        std::vector<uint8_t> data(message.begin(), message.end());

        socket.send_to(asio::buffer(data), remoteEndpoint);
        std::cout << "Message sent to " << address << ":" << port << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error sending message: " << e.what() << std::endl;
    }
}
