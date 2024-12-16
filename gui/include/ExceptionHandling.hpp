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
        FileNotFound(const std::string &error = "");
        ~FileNotFound();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user was supposed
     * to pass a parameter along with the flag.
     *
     */
    class NoFlagParameter : public std::exception {
        public:
        NoFlagParameter(const std::string &error = "");
        ~NoFlagParameter();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the entered ip is incorrect.
     *
     */
    class IpIncorrect : public std::exception {
        public:
        IpIncorrect(const std::string &error = "");
        ~IpIncorrect();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the port is incorrect.
     *
     */
    class PortIncorrect : public std::exception {
        public:
        PortIncorrect(const std::string &error = "");
        ~PortIncorrect();
        const char *what() const noexcept;

        private:
        std::string _msg;
        const char *_buffer;
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
        const char *_buffer;
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
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the window frame limit is invalid.
     *
     */
    class InvalidFrameLimit : public std::exception {
        public:
        InvalidFrameLimit(unsigned int frameLimit);
        ~InvalidFrameLimit();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
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
        const char *_buffer;
    };

    /**
     *@brief This is the class in charge of informing the user
     * that the argument that was provided is not known to the program.
     *
     */
    class UnknownArgument : public std::exception {
        public:
        UnknownArgument(const std::string &argument = "");
        ~UnknownArgument();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    class ConnectionFailed : public std::exception {
        public:
        ConnectionFailed(const std::string &address = "");
        ~ConnectionFailed();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    class InvalidWidth : public std::exception {
        public:
        InvalidWidth(const std::string &width = "", const std::string &min = "", const std::string &max = "");
        ~InvalidWidth();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };

    class InvalidHeight : public std::exception {
        public:
        InvalidHeight(const std::string &height = "", const std::string &min = "", const std::string &max = "");
        ~InvalidHeight();
        const char *what() const noexcept;
        private:
        std::string _msg;
        const char *_buffer;
    };
}
