/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Button.hpp
*/


#pragma once
#include <functional>
#include "BaseComponents/Shape.hpp"
#include "BaseComponents/Text.hpp"
#include "Utilities/Colour.hpp"

namespace GUI
{
    namespace UIComponents
    {
        class Button : public BaseComponents::Shape {
            public:
            Button();
            Button(const double width, const double height, std::string &text);
            ~Button();
            void setText(const std::string &label);
            void setFont(const std::string &font);
            void setFontColor(const std::string &color);
            void setOnClickCallback(const std::function<void()> &callback);
            void setHoverEffect(bool enable);
            void setBorderHoverColour(const Utilities::Colour &colour);
            void setHoverColour(const Utilities::Colour &colour);
            void setTextHoverColour(const Utilities::Colour &colour);
            void setBorderClickedColour(const Utilities::Colour &colour);
            void setClickedColour(const Utilities::Colour &colour);
            void setTextClickedColour(const Utilities::Colour &colour);
            bool isHovered();
            bool isClicked();
            private:
            std::string _label;
            std::function<void()> _onClick;
            bool _hoverEffect;
            Shape _shape;
            BaseComponents::Text _text;
            Utilities::Colour _borderHoverColour;
            Utilities::Colour _hoverColour;
            Utilities::Colour _textHoverColour;
            Utilities::Colour _borderClickedColour;
            Utilities::Colour _clickedColour;
            Utilities::Colour _textClickedColour;
        };
    }
}
