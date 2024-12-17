/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** HelpFunctions.cpp
*/

/**
 * @file HelpFunctions.cpp
 * @brief This is the file in charge of displaying the help message.
 */

#include <iostream>

 /**
  *@brief Display the Usage section of the help prompt.
  *
  * @param binName
  */
static void displayUsageSummary(const std::string binName)
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t" << binName << " [--ip] [--port] [--debug] [--help] ";
    std::cout << "[--full-screen] [--window-width] [--window-height] [--frame-rate-limit]";
    // std::cout << "[--position-x] [--position-y] [--window-title] [--cursor] ";
    // std::cout << "[--cursor-icon] [--image-is-sprite] [--sprite-start-top] ";
    // std::cout << "[--sprite-start-left] [--sprite-width] [--sprite-height]";
    std::cout << std::endl;
}

/**
 *@brief Display the Options section of the help prompt.
 *
 */
static void displayDetailedUsage()
{
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "\t--ip=\"127.0.0.1\"          \tSet the value of the ip on which the program will communicate. (Default value: 127.0.0.1)" << std::endl;
    std::cout << "\t--port=\"5000\"             \tSet the value of the port on which the program will communicate. (Default value: 5000)" << std::endl;
    std::cout << "\t--debug                     \tEnable debug logging." << std::endl;
    std::cout << "\t--help                      \tDisplay this help message and exit." << std::endl;
    std::cout << "\t--full-screen               \tEnable full screen mode." << std::endl;
    std::cout << "\t--window-width=\"800\"      \tSet the width of the window. (Default value: 800)" << std::endl;
    std::cout << "\t--window-height=\"600\"     \tSet the height of the window. (Default value: 600)" << std::endl;
    std::cout << "\t--frame-rate-limit=\"60\"   \tSet the frame rate limit of the window. (Default value: 60)" << std::endl;
    // std::cout << "\t--position-x=\"0\"          \tSet the x position of the window. (Default value: 0)" << std::endl;
    // std::cout << "\t--position-y=\"0\"          \tSet the y position of the window. (Default value: 0)" << std::endl;
    // std::cout << "\t--window-title=\"R-Type\"   \tSet the title of the window. (Default value: \"R-Type\")" << std::endl;
    // std::cout << "\t--cursor=\"true\"           \tShow/Hide the cursor. (Default value: true)" << std::endl;
    // std::cout << "\t--cursor-icon=\"cursor.png\"\tSet the path of the cursor icon. (Default value: \"null\")" << std::endl;
    // std::cout << "\t--image-is-sprite=\"false\" \tSet if the provided image is a spritesheet. (Default value: \"false\")" << std::endl;
    // std::cout << "\t--sprite-start-top=\"true\" \tAnimate by going from top to bottom (or bottom to top). (Default value: \"true\")" << std::endl;
    // std::cout << "\t--sprite-start-left=\"true\"\tAnimate by going from left to right (or right to left). (Default value: \"true\")" << std::endl;
    // std::cout << "\t--sprite-width=\"20\"       \tSet the width of the sprite in the animation. (Default value: 20)" << std::endl;
    // std::cout << "\t--sprite-height=\"20\"      \tSet the height of the sprite in the animation. (Default value: 20)" << std::endl;
}

/**
 *@brief Display the Author section of the help prompt.
 *
 */
static void displayAuthors()
{
    std::cout << "AUTHORS:" << std::endl;
    std::cout << "This program was created for Epitech ";
    std::cout << "project by students of the Epitech school." << std::endl;
}

/**
 *@brief The main function of the help display.
 *
 * @param binName
 */
void DisplayHelp(const std::string binName)
{
    displayUsageSummary(binName);
    std::cout << std::endl;
    displayDetailedUsage();
    std::cout << std::endl;
    displayAuthors();
}
