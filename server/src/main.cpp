//main.cpp
#include "Server.hpp"
#include <iostream>

int main() {
    try {
        Server server;
        server.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}