#pragma once

#include <functional>
#include "GameMessage.hpp"

/**
 * @brief A utility class for dispatching and handling game events.
 * 
 * The `EventDispatcher` facilitates the subscription and notification of game events using a callback mechanism. 
 * It allows a single listener to subscribe to events, which are then forwarded through the provided callback.
 */
class EventDispatcher {
public:
    /**
     * @brief Defines the type for event callbacks.
     * 
     * A callback is a function that takes a `GameMessage` as a parameter.
     */
    using Callback = std::function<void(const GameMessage&)>;

    /**
     * @brief Subscribes a listener to game events.
     * 
     * This method allows setting a callback function to handle incoming game events.
     * 
     * @param callback A function that processes `GameMessage` events.
     */
    void subscribe(Callback callback){
        listener = callback;
    }

    /**
     * @brief Notifies the subscribed listener of an event.
     * 
     * If a listener is subscribed, this method forwards the given `GameMessage` to the listener's callback.
     * 
     * @param event The event to be dispatched, represented as a `GameMessage`.
     */
    void notify(const GameMessage& event){
        if (listener)
            listener(event);
    }

private:
    /**
     * @brief The callback function to handle game events.
     */
    Callback listener;
};