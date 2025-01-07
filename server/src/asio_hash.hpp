#ifndef ASIO_HASH_HPP
#define ASIO_HASH_HPP

#include <asio.hpp>
#include <functional>
/**
 * asio_hash:
 *   - Define a std::hash specialisation for asio::ip::udp::endpoint
 *   - fix the g++ complaint
 */

namespace std {
    template<>
    struct hash<asio::ip::udp::endpoint> {
        std::size_t operator()(const asio::ip::udp::endpoint& endpoint) const noexcept {
            auto addressHash = std::hash<std::string>()(endpoint.address().to_string());
            auto portHash = std::hash<unsigned short>()(endpoint.port());
            return addressHash ^ (portHash << 1);
        }
    };
}

#endif // ASIO_HASH_HPP
