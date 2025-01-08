#include "Tests.hpp"

EventDispatcher *ev = nullptr;
Registry *r = nullptr;
Game *g = nullptr;
Queue *q = nullptr;

inline void printMessage(GameMessage &msg)
{
    switch (msg.type)
    {
    case MOVE:
        std::cout << "MOVE " << msg.id << " " << msg.msg.coords.x << " " << msg.msg.coords.y;
        break;
    case SHOOT:
        std::cout << "SHOOT " << msg.id;
        break;
    case SPAWN:
        std::cout << "SPAWN " << msg.id << " " << msg.msg.asset_id << " " << msg.msg.coords.x << " " << msg.msg.coords.y;
        break;
    case KILL:
        std::cout << "KILL " << msg.id;
        break;
    case DAMAGE:
        std::cout << "MOVE " << msg.id;
        break;
    case STATUS:
        std::cout << "STATUS ";
        switch (msg.msg.status)
        {
        case 0x00:
            std::cout << "ON GOING";
            break;
        case 0x01:
            std::cout << "VICTORY";
            break;
        default:
            std::cout << "DEFEAT";
            break;
        }
        break;
    default:
        break;
    }
    std::cout << std::endl;
}

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
            //printMessage(msg);
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
            //printMessage(msg);
        }
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}

int test_stress(void)
{
    GameMessage msg1 = {messageType::CONNECT, 0, {0, 0, "Player1", {0, 0}}};
    GameMessage msg2 = {messageType::CONNECT, 0, {0, 0, "Player2", {0, 0}}};
    try {
        Game newGame;
        std::ostringstream oss;
        std::string s;
        serialize(msg1, oss);
        s = oss.str();
        newGame.onServerEventReceived(s);
        serialize(msg2, oss);
        s = oss.str();
        newGame.onServerEventReceived(s);
        for (int i = 0; i <= 60; i++) {
            newGame.update(1);
            auto events = newGame.getGameEvents();
            for (auto event : events) {
                std::cout << "frame " << i << ": ";
                std::istringstream iss(event);
                GameMessage msg = deserialize(iss);
                printMessage(msg);
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test Failed" << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Test OK" << std::endl;
    return 0;
}
