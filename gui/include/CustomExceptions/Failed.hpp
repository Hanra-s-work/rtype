/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Failed.hpp
*/

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{
    /**
     * @brief This is the class in charge of raising the ConnectionFailed error.
     *
     */
    class ConnectionFailed : public std::exception {
        public:
        /**
         * @brief Construct a new Connection Failed object
         *
         * @param address The address the program tried to connect to.
         */
        ConnectionFailed(const std::string &address = "");
        /**
         * @brief Destroy the Connection Failed object
         *
         */
        ~ConnectionFailed();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

}
