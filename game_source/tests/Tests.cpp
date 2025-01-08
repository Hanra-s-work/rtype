#include "Tests.hpp"

EventDispatcher *ev = nullptr;
Registry *r = nullptr;
Game *g = nullptr;
Queue *q = nullptr;

void cleanup(void)
{
    if (ev)
        delete ev;
    if (r)
        delete r;
    if (g)
        delete g;
    if (q)
        delete q;
}

int test_zipper(void)
{
    std::vector<std::optional<int>> v1 = {97, 98, std::nullopt, 99, 100};
    std::vector<std::optional<char>> v2 = {'a', 'b', 'o', 'c', std::nullopt};
    try
    {
        Zipper z = Zipper(v1, v2);
        for (auto &&[num, letter] : z) {
            if (num != letter)
                throw std::runtime_error("Zipper is not zipping.");
        }
    }
    catch(std::exception& e)
    {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_indexed_zipper(void)
{
    std::vector<std::optional<int>> v1 = {97, 98, std::nullopt, 99, 100};
    std::vector<std::optional<char>> v2 = {'a', 'b', 'o', 'c', std::nullopt};
    try
    {
        IndexedZipper z = IndexedZipper(v1, v2);
        for (auto &&[idx, num, letter] : z) {
            if (num != letter)
                throw std::runtime_error("IndexedZipper is not zipping.");
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_create_registry(void)
{
    try {
        ev = new EventDispatcher();
        q = new Queue();
        r = new Registry(ev, q);
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

int test_get_game_event(void)
{
    try {
        if (!g)
            throw std::runtime_error("Game not initialized");
        g->update(6);
        auto list = g->getGameEvents();
        for (auto a : list) {
            std::istringstream iss = std::istringstream(a);
            GameMessage msg = deserialize(iss);
            std::cout << msg.type << " " << msg.id << std::endl;
        }
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_send_msg(void)
{
    GameMessage msg = {messageType::CONNECT, 0, {0, 0, "Player1", {0, 0}}};
    std::ostringstream oss;
    std::string s;
    try {
        if (!g)
            throw std::runtime_error("Game not initialized");
        serialize(msg, oss);
        s = oss.str();
        g->onServerEventReceived(s);
        g->update(1);
        auto list = g->getGameEvents();
        for (auto a : list) {
            std::istringstream iss = std::istringstream(a);
            GameMessage msg = deserialize(iss);
            std::cout << msg.type << " " << msg.id << std::endl;
        }
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}
