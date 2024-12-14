/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RealMain.cpp
*/

#include "Constants.hpp"
#include "RealMain.hpp"

void process_arguments(const Main &main, int argc, char **argv)
{

}

int RealMain(int argc, char **argv)
{
    Main Main("127.0.0.1", 5000, 800, 800, true, false, "R-Type", 0, 0, "NULL", false, false, false, 20, 20);

    process_arguments(Main, argc, argv);
    return SUCCESS;
}
