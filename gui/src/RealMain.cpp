/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RealMain.cpp
*/

/**
 * @file RealMain.cpp
 * @brief Entry point for processing command-line arguments and running the main application logic.
 */

#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include "RealMain.hpp"
#include "Constants.hpp"
#include "ExceptionHandling.hpp"

 /**
 * @brief Extracts the flag and value from a command-line argument.
 *
 * This function parses a command-line argument to split it into a flag and value.
 * For example, if the argument is `--key=value`, it will return a tuple `("key", "value")`.
 * If there is no `=` sign, it returns the flag with an empty value.
 *
 * @param arg The command-line argument as a C-style string.
 * @return A tuple containing the flag (as the first element) and the value (as the second element).
 */
std::vector<std::string> extract_argument(char *arg)
{
    std::cout << "Extracting arguments" << std::endl;
    std::string flag = "";
    std::string value = "";
    std::string arg_str(arg);
    size_t pos = arg_str.find('=');
    std::vector<std::string> resp;

    if (arg_str.find("--") == 0) {
        flag = arg_str.substr(2);
    } else if (arg_str.find("-") == 0) {
        flag = arg_str.find("-");
    } else if (arg_str.find("/") == 0) {
        flag = arg_str.substr(1);
    } else {
        flag = arg_str;
    }

    if (pos == std::string::npos) {
        resp.push_back(flag);
        resp.push_back("");
        return resp;
    }

    flag = arg_str.substr(0, pos);
    value = arg_str.substr(pos + 1);
    resp.push_back(flag);
    resp.push_back(value);

    return resp;
}

/**
 *@brief Process the single argument that is provided.
 *
 * @param main
 * @param args
 */
void process_given_argument(const Main &main, const std::vector<std::string> &args, std::string const &binName)
{
    if (args[0] == "help" || args[0] == "h" || args[0] == "?") {
        DisplayHelp(binName);
        throw MyException::HelpFound();
    }
}

/**
 * @brief Processes the command-line arguments and applies them to the main application object.
 *
 * This function iterates through the provided command-line arguments, parses them using
 * `extract_argument`, and applies relevant changes to the application state.
 *
 * @param main A reference to the main application object.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments as C-style strings.
 */
void process_arguments(const Main &main, int argc, char **argv)
{
    unsigned int index = 1;
    Debug::getInstance() << "Dumping arguments" << std::endl;
    std::string binName(argv[0]);
    while (index < argc) {
        std::vector<std::string> arg = extract_argument(argv[index]);
        std::cout << "Flag: " << arg[0] << ", Value: " << arg[1] << std::endl;
        process_given_argument(main, arg, binName);
        index++;
    }
}

/**
 * @brief The main function for initializing and running the application.
 *
 * This function serves as the entry point for the R-Type GUI application. It initializes the
 * main application object, processes command-line arguments, and starts the application's
 * execution loop. Exceptions are caught and logged, and an error code is returned if any
 * issues occur.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments as C-style strings.
 * @return An integer status code: SUCCESS (0) on successful execution, ERROR (non-zero) on failure.
 */
int RealMain(int argc, char **argv)
{
    int status = SUCCESS;
    bool help_found = false;

    Main MyMain("127.0.0.1", 5000, 800, 600, true, false, "R-Type", 0, 0, "NULL", false, false, false, 20, 20, true);

    if (argc > 1) {
        try {
            process_arguments(MyMain, argc, argv);
        }
        catch (const MyException::HelpFound &e) {
            status = SUCCESS;
            help_found = true;
            Debug::getInstance() << "Help was found: '" << e.what() << "'." << std::endl;
        }
        catch (const std::exception &e) {
            status = ERROR;
            Debug::getInstance() << "An error occurred: '" << e.what() << "'." << std::endl;
        }
    }

    if (help_found || status == ERROR) {
        return status;
    }

    try {
        status = MyMain.run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        status = ERROR;
    }
    std::cout << "Exit status : '" << status << "'." << std::endl;
    return status;
}
