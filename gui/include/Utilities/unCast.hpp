/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** unCast.hpp
*/

#pragma once

#include <any>
#include <string>
#include <optional>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "CustomExceptions.hpp"

namespace Utilities
{
    /**
     * @brief A function in charge of casting the content of std::any back to it's original state.
     *
     * @tparam T
     *
     * @param classNode The entity to process
     * @param raiseOnError If uncasting failed, raise an error? (Default: true)
     *
     * @return T The un-casted member.
     */
    template<typename T>
    std::optional<T> unCast(const std::any &classNode, const bool raiseOnError = true)
    {
        try {
            return std::optional(std::any_cast<T>(classNode));
        }
        catch (std::bad_any_cast &e) {
            if (raiseOnError) {
                throw CustomExceptions::InvalidType(std::string(e.what()));
            } else {
                PRECISE_WARNING << "Any cast failed, system error: " + std::string(e.what()) << std::endl;
                return std::nullopt;
            }
        }
    };
}
