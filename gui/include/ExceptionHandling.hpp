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
    class FileNotFound : public std::exception {
        public:
        FileNotFound(std::string error = "");
        ~FileNotFound();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };


    class NoFlagParameter : public std::exception {
        public:
        NoFlagParameter(std::string error = "");
        ~NoFlagParameter();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };



    class IpIncorrect : public std::exception {
        public:
        IpIncorrect(std::string error = "");
        ~IpIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    class PortIncorrect : public std::exception {
        public:
        PortIncorrect(std::string error = "");
        ~PortIncorrect();
        const char *what() const noexcept;

        private:
        std::string _error;
        std::string _msg;
    };

    class InvalidWindowWidth : public std::exception {
        public:
        InvalidWindowWidth();
        ~InvalidWindowWidth();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

    class InvalidWindowHeight : public std::exception {
        public:
        InvalidWindowHeight();
        ~InvalidWindowHeight();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

    class HelpFound : public std::exception {
        public:
        HelpFound();
        ~HelpFound();
        const char *what() const noexcept;
        private:
        std::string _msg;
    };

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
