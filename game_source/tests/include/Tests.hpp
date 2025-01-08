#pragma once

#include <iostream>
#include <exception>
#include <functional>
#include <vector>

#include "Zipper.hpp"
#include "IndexedZipper.hpp"
#include "Game.hpp"
#include "GameMessage.hpp"
#include "Registry.hpp"
#include "Components.hpp"
#include "Systems.hpp"

/**
 * @brief Cleans up any resources or states after tests.
 * 
 * The `cleanup` function is used to reset or clean up any resources or global states after the tests 
 * have been run. This ensures that each test is isolated and doesn't interfere with others.
 */
void cleanup(void);

/**
 * @brief Test the functionality of the Zipper class.
 * 
 * This test verifies that the Zipper class correctly zips two vectors
 * containing optional values. The test iterates through the zipped pairs
 * and checks if the values match.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_zipper(void);

/**
 * @brief Test the functionality of the IndexedZipper class.
 * 
 * This test verifies that the IndexedZipper class correctly zips two vectors
 * containing optional values, along with their respective indices. The test 
 * iterates through the zipped tuples and checks if the values match.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_indexed_zipper(void);

/**
 * @brief Test function for creating a registry.
 * 
 * The `test_create_registry` function tests the creation of a registry object, verifying its initialization 
 * and ensuring that it functions as expected.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_create_registry(void);

/**
 * @brief Test function for running systems within the registry.
 * 
 * The `test_run_systems` function tests the execution of various systems within the registry, ensuring 
 * that the systems interact correctly with the components and entities.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_run_systems(void);

/**
 * @brief Test function for creating a game.
 * 
 * The `test_create_game` function tests the initialization of a game, ensuring that all game components 
 * are properly set up and ready for use.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_create_game(void);

/**
 * @brief Test function for running the game's update cycle.
 * 
 * The `test_run_update` function tests the game's update logic, simulating a game loop and verifying 
 * that game states and entities are correctly updated.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_run_update(void);

/**
 * @brief Test retrieving game events from the Game instance.
 * 
 * This test ensures that the Game object updates correctly and retrieves
 * game events. It deserializes each event and prints its type and ID to 
 * verify the functionality.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure).
 */
int test_get_game_event(void);

/**
 * @brief Test sending a message to the Game instance.
 * 
 * This test verifies that a message can be serialized, sent to the Game 
 * instance, and processed correctly. The Game object updates, retrieves 
 * game events, and deserializes them to validate the process.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure)..
 */
int test_send_msg(void);

/**
 * @brief Test for stress and performance.
 * 
 * This test verifies if the game loop doesn't break or is too slow.
 * 
 * @return An integer indicating the result of the test (e.g., 0 for success, non-zero for failure)...
 */
int test_stress(void);

/**
 * @brief A collection of test functions to be executed.
 * 
 * The `tests` vector holds a collection of test functions that will be run sequentially. Each function 
 * returns an integer indicating the test's result. This vector serves as the central point for managing 
 * and executing the tests.
 */
const std::vector<std::function<int(void)>> tests = {
    test_zipper,           ///< Test for creating a zipper
    test_indexed_zipper,   ///< Test for creating an indexed zipper
    test_create_registry,  ///< Test for creating a registry.
    test_run_systems,      ///< Test for running systems within the registry.
    test_create_game,      ///< Test for creating a game.
    test_run_update,       ///< Test for running the game's update cycle.
    test_get_game_event,   ///< Test for getting in-game events
    test_send_msg,         ///< Test for sending game changes
    test_stress            ///< Test for stress and performance 
};
