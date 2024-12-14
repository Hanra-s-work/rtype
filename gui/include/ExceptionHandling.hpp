/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.hpp
*/

#pragma once
#include <string>
#include <exception>

namespace MyException
{
    class InvalidArgumentNumber : public std::exception {
        public:
        const char *what() const noexcept;
    };

    class FileNotFound : public std::exception {
        public:
        FileNotFound(std::string error);
        ~FileNotFound();
        const char *what() const noexcept;

        private:
        std::string _error;
    };

    class IpIncorrect : public std::exception {
        public:
        IpIncorrect(std::string error);
        ~IpIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
    };

    class PortIncorrect : public std::exception {
        public:
        PortIncorrect(std::string error);
        ~PortIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
    };

    class InvalidWindowWidth : public std::exception {
        public:
        const char *what() const noexcept;
    };

    class InvalidWindowHeight : public std::exception {
        public:
        const char *what() const noexcept;
    };
    class HelpFound : public std::exception {
        public:
        const char *what() const noexcept;
    };

    class UnknownArgument : public std::exception {
        public:
        UnknownArgument(std::string argument);
        ~UnknownArgument();
        const char *what() const noexcept;
        private:
        std::string _argument;
    };
}
