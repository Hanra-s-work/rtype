/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Sprite.hpp
*/

#pragma once
#include "BaseComponents/Image.hpp"
#include "BaseComponents/Animation.hpp"

namespace GUI
{
    namespace BaseComponents
    {
        class Sprite : public Image, public Animation {
            public:
            Sprite();
            void playAnimation(const std::string &animation_name);
            void setFrame(unsigned int frame_index);
            private:
            std::map<std::string, std::vector<unsigned int>> _animations;
            std::string _current_animation;
        };
    }
}
