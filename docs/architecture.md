# Engine Architecture

This document describes the overall architecture of the game engine.

## Modularity

The engine is divided into several modules:
- **Rendering**: Managed by `HandleBackground`, `SpriteEntity`, and SFML classes.
- **Audio**: Managed by `MusicHandler`.
- **Entities**: Managed by `EntityManager` with implementations via `Entity` and `SpriteEntity`.
- **Networking**: Asynchronous communication is handled by `NetworkClient` using Asio.

## Network Communication and Synchronization

The server is the authoritative source. Clients:
- Send commands (movement, firing, etc.)
- Receive regular updates (60 Hz) about entity states.
- Use a heartbeat mechanism to maintain connection.

Techniques like **client-side prediction** and **server reconciliation** are used to mask latency.

## Extensibility

The engine is designed to be independent from the final game:
- It can be compiled as a separate library.
- A second demonstration game (e.g., a Pong clone) can be built using this engine.
- Script integration (e.g., Lua) is planned to allow non-developers to extend game content.