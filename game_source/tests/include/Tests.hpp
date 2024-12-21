#pragma once

#include <iostream>
#include <exception>
#include <functional>
#include <vector>

#include "Game.hpp"
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
 * @brief A collection of test functions to be executed.
 * 
 * The `tests` vector holds a collection of test functions that will be run sequentially. Each function 
 * returns an integer indicating the test's result. This vector serves as the central point for managing 
 * and executing the tests.
 */
const std::vector<std::function<int(void)>> tests = {
    test_create_registry,  ///< Test for creating a registry.
    test_run_systems,      ///< Test for running systems within the registry.
    test_create_game,      ///< Test for creating a game.
    test_run_update        ///< Test for running the game's update cycle.
};
