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

#include "RealMain.hpp"

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
    PRECISE_INFO << "Extracting arguments" << std::endl;
    std::string arg_str(arg);
    size_t pos = arg_str.find('=');
    std::string flag = "";
    std::string value = "";
    std::vector<std::string> resp;

    if (pos != std::string::npos) {
        flag = arg_str.substr(0, pos);
        value = arg_str.substr(pos + 1);
    } else {
        flag = arg_str;
        value = "";
    }

    if (flag.find("--") == 0) {
        flag = flag.substr(2);
    } else if (flag.find("-") == 0) {
        flag = flag.substr(1);
    } else if (flag.find("/") == 0) {
        flag = flag.substr(1);
    }

    resp.push_back(flag);
    resp.push_back(value);

    return resp;
}

/**
 *@brief Process the single argument that is provided.
 *
 * @param main The main class, initialised.
 * @param args The current argument
 * @param binName The name of the program binary.
 *
 * @throws MyException::HelpFound(); This is an information that allows the program to know that the help flag was passed.
 * @throws MyException::VersionFound(); This is an information that allows the program to know that the version flag was passed.
 * @throws MyException::InvalidPort(args[1]); This is an error informing the user that the port value they passed is invalid.
 * @throws MyException::NoFlagParameter(args[0]); This is an error informing the user that a parameter was expected for the flag but was not found.
 * @throws MyException::UnknownArgument(args[0]); This is an error informing the user that the flag they passed is unknown.
 * @throws MyException::InvalidFrameLimit(args[1]); This is an error informing the user that the frame limit that was passed is invalid.
 * @throws MyException::InvalidWindowWidth(args[1]); This is an error informing the user that the value for the window's width is invalid.
 * @throws MyException::InvalidWindowHeight(args[1]); This is an error informing the user the the value for the window's height is invalid.
 */
void process_given_argument(Main &main, const std::vector<std::string> &args, std::string const &binName)
{
    if (args[0] == "help" || args[0] == "h" || args[0] == "?") {
        DisplayHelp(binName);
        throw MyException::HelpFound();
    } else if (args[0] == "version" || args[0] == "v") {
        DisplayVersion(false);
        throw MyException::VersionFound();
    } else if (args[0] == "ip" || args[0] == "i") {
        PRECISE_SUCCESS << "Ip is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            PRECISE_CRITICAL << "Error: Ip value is required" << std::endl;
            std::cerr << "Error: Ip value is required" << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        main.setIp(args[1]);
    } else if (args[0] == "port" || args[0] == "p") {
        PRECISE_SUCCESS << "Port is provided: '" << args[1] << "'" << std::endl;
        unsigned int port = 0;
        if (args[1].empty()) {
            PRECISE_CRITICAL << "Error: Port number is required" << std::endl;
            std::cerr << "Error: Port number is required" << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        try {
            port = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            PRECISE_CRITICAL << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            std::cerr << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            throw MyException::InvalidPort(args[1]);
        }
        catch (const std::out_of_range &e) {
            PRECISE_CRITICAL << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            std::cerr << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            throw MyException::InvalidPort(args[1]);
        }
        main.setPort(port);
    } else if (args[0] == "debug" || args[0] == "d") {
        main.setDebug(true);
        PRECISE_INFO << "Debug is True" << std::endl;
    } else if (args[0] == "full-screen" || args[0] == "fs" || args[0] == "fullscreen") {
        PRECISE_INFO << "Full screen is activated" << std::endl;
        main.setWindowFullscreen(true);
    } else if (args[0] == "window-width" || args[0] == "ww" || args[0] == "windowwidth") {
        unsigned int windowWidth = 0;
        PRECISE_INFO << "Window width is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            std::cerr << "Error: Window width is required." << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        try {
            windowWidth = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            PRECISE_CRITICAL << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            std::cerr << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            throw MyException::InvalidWindowWidth(args[1]);
        }
        catch (const std::out_of_range &e) {
            PRECISE_CRITICAL << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            std::cerr << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            throw MyException::InvalidWindowWidth(args[1]);
        }
        main.setWindowWidth(windowWidth);
    } else if (args[0] == "window-height" || args[0] == "wh" || args[0] == "windowheight") {
        unsigned int windowHeight = 0;
        PRECISE_INFO << "Window Height is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            std::cerr << "Error: Window Height is required." << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        try {
            windowHeight = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            throw MyException::InvalidWindowHeight(args[1]);
        }
        catch (const std::out_of_range &e) {
            std::cerr << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            throw MyException::InvalidWindowHeight(args[1]);
        }
        main.setWindowHeight(windowHeight);
    } else if (args[0] == "frame-rate-limit" || args[0] == "frl" || args[0] == "frameratelimit") {
        unsigned int frameLimit = 0;
        PRECISE_INFO << "Frame limit is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            std::cerr << "Error: Frame Rate is required." << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        try {
            frameLimit = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            throw MyException::InvalidFrameLimit(args[1]);
        }
        catch (const std::out_of_range &e) {
            std::cerr << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            throw MyException::InvalidFrameLimit(args[1]);
        }
        main.setFrameLimit(frameLimit);
    } else if (args[0] == "config-file" || args[0] == "cf" || args[0] == "configfile") {
        PRECISE_INFO << "Config file is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            std::cerr << "Error: TOML config file is required." << std::endl;
            throw MyException::NoFlagParameter(args[0]);
        }
        main.setConfigFile(args[1]);
    } else {
        throw MyException::UnknownArgument(args[0]);
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
void process_arguments(Main &main, int argc, char **argv)
{
    unsigned int index = 1;
    PRECISE_INFO << "Dumping arguments" << std::endl;
    std::string binName(argv[0]);
    while (index < argc) {
        std::vector<std::string> arg = extract_argument(argv[index]);
        PRECISE_INFO << "Flag: '" << arg[0] << "', Value: '" << arg[1] << "'." << std::endl;
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
    bool version_found = false;

    Main MyMain("127.0.0.1", 5000, 800, 600, true, false, "R-Type", 0, 0, "NULL", false, false, false, 20, 20, 60, "client_config.toml", false);

    if (argc > 1) {
        try {
            process_arguments(MyMain, argc, argv);
        }
        catch (const MyException::HelpFound &e) {
            status = SUCCESS;
            help_found = true;
            PRECISE_SUCCESS << "Help was found: '" << e.what() << "'." << std::endl;
        }
        catch (const MyException::VersionFound &e) {
            status = SUCCESS;
            version_found = true;
            PRECISE_SUCCESS << "Version was found: '" << e.what() << "'." << std::endl;
        }
        catch (const std::exception &e) {
            status = ERROR;
            PRECISE_CRITICAL << "An error occurred: '" << e.what() << "'." << std::endl;
            std::cerr << "An error occurred: '" << e.what() << "'." << std::endl;
        }
    }

    if (help_found || version_found || status == ERROR) {
        PRECISE_INFO << "The program exited with status: " << status << std::endl;
        return status;
    }

    try {
        MyMain.setConfigFile(MyMain.getConfigFile());
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        PRECISE_CRITICAL << "Failed to load the config file, aboring program." << std::endl;
        return ERROR;
    }

    try {
        MyMain.run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        status = ERROR;
    }
    PRECISE_INFO << "Exit status : '" << status << "'." << std::endl;
    return status;
}
