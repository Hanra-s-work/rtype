#include "Random.hpp"
#include <random>

std::random_device rd;

int randint(int min, int max)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}