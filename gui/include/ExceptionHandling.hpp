/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.hpp
*/

/**
 * @file ExceptionHandling.hpp
 * @brief File in charge of containing the custom errors that are going to be used for custom description errors.
 */

#pragma once
#include <string>
#include <exception>

namespace MyException
{
    /**
     *@brief This is the class in charge of informing the user
     * that the provided file path could not be found.
     *
     */
    class FileNotFound : public std::exception {
        public:
        FileNotFound(std::string error = "");
        ~FileNotFound();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user was supposed
     * to pass a parameter along with the flag.
     *
     */
    class NoFlagParameter : public std::exception {
        public:
        NoFlagParameter(std::string error = "");
        ~NoFlagParameter();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the entered ip is incorrect.
     *
     */
    class IpIncorrect : public std::exception {
        public:
        IpIncorrect(std::string error = "");
        ~IpIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the port is incorrect.
     *
     */
    class PortIncorrect : public std::exception {
        public:
        PortIncorrect(std::string error = "");
        ~PortIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window width is invalid.
     *
     */
    class InvalidWindowWidth : public std::exception {
        public:
        InvalidWindowWidth();
        ~InvalidWindowWidth();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window height is invalid.
     *
     */
    class InvalidWindowHeight : public std::exception {
        public:
        InvalidWindowHeight();
        ~InvalidWindowHeight();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the help flag was found.
     * This is not an error.
     *
     */
    class HelpFound : public std::exception {
        public:
        HelpFound();
        ~HelpFound();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the argument that was provided is not known to the program.
     *
     */
    class UnknownArgument : public std::exception {
        public:
        UnknownArgument(std::string argument = "");
        ~UnknownArgument();
        const char *what() const noexcept;
        private:
        std::string _argument;
        std::string _msg;
    };
}
