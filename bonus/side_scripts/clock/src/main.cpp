/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** main.cpp
*/

#include <iostream>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    sf::Clock clock;

    // Correct usage: Assign returned value to an object, not a reference
    sf::Time time1 = clock.getElapsedTime();
    sf::Time time2 = clock.restart();
    sf::Time time3 = clock.reset();

    // Optional: Print time values (requires proper sf::Time formatting if desired)
    std::cout << "Elapsed time: " << time1.asSeconds() << " seconds\n";
    std::cout << "Restart time: " << time2.asSeconds() << " seconds\n";
    std::cout << "Reset time: " << time3.asSeconds() << " seconds\n";

    return 0;
}
