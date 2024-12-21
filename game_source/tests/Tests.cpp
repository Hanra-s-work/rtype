#include "Tests.hpp"

EventDispatcher *ev = nullptr;
Registry *r = nullptr;
Game *g = nullptr;

void cleanup(void)
{
    if (ev)
        delete ev;
    if (r)
        delete r;
    if (g)
        delete g;
}

int test_create_registry(void)
{
    try {
        ev = new EventDispatcher();
        r = new Registry(ev);
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

int test_create_game(void) 
{
    try {
        g = new Game();
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_run_update(void)
{
    try {
        if (!g)
            throw std::runtime_error("Game not initialized");
        g->update(6);
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}
