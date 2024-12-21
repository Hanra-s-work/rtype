#pragma once

#include <iostream>
#include <exception>
#include <functional>
#include <vector>

#include "Components.hpp"
#include "Registry.hpp"
#include "Systems.hpp"

void cleanup(void);

int test_create_registry(void);
int test_run_systems(void);

const std::vector<std::function<int(void)>> tests = {
    test_create_registry,
    test_run_systems
};