#pragma once

/**
 * @brief Namespace containing time-related utilities for the game.
 * 
 * The `Time` namespace provides access to time-related functionality, including tracking the time between 
 * frames or updates. It contains the `deltaTime` variable, which stores the time elapsed between two frames.
 */
namespace Time {
    /**
     * @brief The time difference between the current frame and the last frame.
     * 
     * `deltaTime` represents the time elapsed since the last frame was rendered or processed. This value 
     * is used to ensure smooth and consistent gameplay, independent of the frame rate.
     * 
     * @note This value is typically updated each frame and used for time-dependent actions, such as movement.
     */
    extern float deltaTime; ///< The time elapsed between the current and previous frame (in seconds).
}
