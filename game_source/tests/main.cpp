#include "Tests.hpp"

int main(void) {
    int ok_test = tests.size();

    for (auto &test : tests) {
        ok_test += test();
    }

    cleanup();
    std::cout << "Successiful tests: " << ok_test << "\tFailed tests: " << tests.size() - ok_test << std::endl;
    return 0;
}