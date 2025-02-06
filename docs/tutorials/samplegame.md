# Tutorial: Creating a Sample Game with the Engine

This tutorial walks you through creating a simple game (e.g., Pong) using the engine.

## Step 1: Initialization

- Instantiate the `Client` class.
- Configure the window and load the necessary graphics.

## Step 2: Creating Entities

- Use `EntityManager` to create paddles and a ball.
- Implement specific behaviors (movement, collisions).

## Step 3: Input Handling

- Configure keyboard input to move the paddles.
- Optionally, use `NetworkClient` for multiplayer functionality.

## Step 4: Update and Render

- In the main loop, update entity states and render via `Client::render()`.

## Step 5: Build and Test

Compile your project and test the game.
