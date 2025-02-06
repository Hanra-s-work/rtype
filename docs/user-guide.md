# User Guide for the Game Engine

This guide explains how to integrate and extend the game engine.

## Integration in a New Project

1. Compile the engine as a static or dynamic library.
2. Include the engine headers in your project.
3. Initialize the `Client` class and start the main loop via `run()`.

## Extending the Engine

### Adding a New Entity

1. Create a new class derived from `Entity` or use `SpriteEntity`.
2. Register the entity with the `EntityManager` via `updateEntity()`.
3. Add the desired sprite and behavior.

### Customizing the Audio System

Audio is handled by `MusicHandler`:
- Adjust the volume using `setMusicVolume()` and `setEffectsVolume()`.
- To add a new effect, load the new resource and add a method similar to `playClick()`.

## Customizing Network Communication

The `NetworkClient` class can be modified to adjust network behavior.
- To add new message types, update `NetworkProtocol.hpp` (located in `common/`).
- Implement handling in the `processMessages()` method in `Client`.
