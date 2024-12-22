#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include "GameMessage.hpp"

/**
 * @brief A thread-safe queue for storing and managing GameMessage objects.
 *
 * This class provides thread-safe methods for adding, retrieving, and waiting
 * for GameMessage objects. It uses a mutex and condition variable to ensure
 * synchronization between threads.
 */
class Queue {
public:
    /**
     * @brief Push a GameMessage item into the queue.
     * @param item The GameMessage to push into the queue.
     */
    void push(const GameMessage& item);

    /**
     * @brief Try to pop a GameMessage item from the queue.
     * @return An optional containing the GameMessage if the queue is not empty, or std::nullopt otherwise.
     */
    std::optional<GameMessage> pop();

    /**
     * @brief Wait and pop a GameMessage item from the queue.
     *        This blocks until an item is available.
     * @return The GameMessage item from the queue.
     */
    GameMessage waitAndPop();

    /**
     * @brief Check if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    bool isEmpty();

private:
    std::queue<GameMessage> _queue; ///< The underlying queue to store GameMessage objects.
    std::mutex _mutex; ///< Mutex to ensure thread safety.
    std::condition_variable _condition; ///< Condition variable to handle blocking.
};