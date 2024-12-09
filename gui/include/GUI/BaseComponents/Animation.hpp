/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Animation.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities/Clock.hpp"


namespace GUI
{
    namespace BaseComponents
    {
        class Animation : public Utilities::Clock {
            public:
            Animation();
            Animation(std::map<unsigned int, sf::Texture> &frames, bool loop = false);
            ~Animation();
            void setFrameDuration(unsigned int microseconds);
            void createAnimation(std::string animation_name, std::vector<unsigned int> &frames);
            std::vector<unsigned int> getAnimation(std::string animation_name);
            void updateAnimation(std::string animation_name, std::vector<unsigned int> frames);
            void playAnimation(std::string animation_name);
            void stopAnimation();
            bool isPlaying();
            std::string getAnimationName();
            unsigned int getFrameDuration();
            unsigned int tick();
            private:
            bool _loop;
            unsigned int _frame_duration;
            unsigned int _current_frame;
            std::string _current_animation;
            std::map<unsigned int, sf::Texture> _sfml_textures;
            std::map<std::string, std::vector<unsigned int>> _sfml_animations;
        };
    }
}
