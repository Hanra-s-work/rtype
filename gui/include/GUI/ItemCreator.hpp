/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ItemCreator.hpp
*/

#pragma once
#include <map>
#include <vector>
#include "Enums/ItemType.hpp"
#include "Interfaces/IComponent.hpp"

namespace GUI
{
    class ItemCreator {
        public:
        ItemCreator();
        ~ItemCreator();
        void createItem(const std::string &name, const Enums::ItemType &item, const Interfaces::IComponent &node);
        Interfaces::IComponent getItem(const std::string &name);
        private:
        std::vector<std::map<std::string, Enums::ItemType, Interfaces::IComponent>> _items;
    };
}
