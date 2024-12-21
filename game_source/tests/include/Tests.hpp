#pragma once

#include <iostream>
#include <exception>
#include <functional>
#include <vector>

#include "Game.hpp"
#include "Registry.hpp"
#include "Components.hpp"
#include "Systems.hpp"

void cleanup(void);

int test_create_registry(void);
int test_run_systems(void);
int test_create_game(void);
int test_run_update(void);

const std::vector<std::function<int(void)>> tests = {
    test_create_registry,
    test_run_systems,
    test_create_game,
    test_run_update
};