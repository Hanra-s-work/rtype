#include "Tests.hpp"

Registry *r = nullptr;

void cleanup(void)
{
    if (r)
        delete r;
}

int test_create_registry(void)
{
    try {
        r = new Registry();
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_run_systems(void)
{
    try {
        if (!r)
            throw std::runtime_error("Registry not initialized");
        r->run_systems();
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}
