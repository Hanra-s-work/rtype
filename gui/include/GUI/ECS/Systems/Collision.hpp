/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.hpp
*/

/**
 * @file CollisionComponent.hpp
 * @brief This is the file that contains the class in charge of checking collisions.
 */

#pragma once

#include <cstdint>
#include <utility>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "Recoded/Rect.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/MouseInfo.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @class Collision
             * @brief Represents a rectangular component that can detect collisions and
             *        mouse interactions, such as hovering and clicking.
             */
            class Collision : public EntityNode {
                public:
                Collision(const std::uint32_t entityId = 0, const float width = 0, const float height = 0, const float positionX = 0, const float positionY = 0);
                ~Collision();

                void setWidth(const float &width);
                void setHeight(const float &height);

                void setPositionX(const float &posX);
                void setPositionY(const float &posY);

                void setPosition(const std::pair<float, float> &position);

                void setDimension(const std::pair<float, float> &dimension);

                void setGeometry(const Recoded::FloatRect &rect);

                void setMousePosition(const std::pair<int, int> &position);

                void update(const std::pair<int, int> &mousePosition);
                void update(const GUI::ECS::Systems::MouseInfo &mouse);
                void update(const GUI::ECS::Systems::Collision &copy);

                void updateMouseInfo(const GUI::ECS::Systems::MouseInfo &mouse);

                const bool isClicked() const;
                const bool isHovered() const;
                const bool isColliding(const Collision &itemTwo) const;

                const float getWidth() const;
                const float getHeight() const;

                const float getPositionX() const;
                const float getPositionY() const;

                const Recoded::FloatRect getGeometry() const;

                const std::pair<float, float> getPosition() const;

                const std::pair<float, float> getDimension() const;

                const GUI::ECS::Systems::MouseInfo getMouseInfo() const;
                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                Collision &operator =(const GUI::ECS::Systems::Collision &copy);

                protected:
                void _updateMouseCollisionData();
                bool _isHovered = false;
                bool _isClicked = false;
                Recoded::FloatRect _rect = { {0,0}, {0,0} };
                GUI::ECS::Systems::MouseInfo _mouse;
            };

            /**
             * @brief Outputs the collision component's info to a stream.
             * @param os The output stream.
             * @param item The collision component to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Collision &item);

            /**
             * @brief Compares two colors for equality.
             * @param left The first collision component.
             * @param right The second collision component.
             * @return `true` if the colors are equal; otherwise, `false`.
             */
            [[nodiscard]] const bool operator==(Collision left, Collision right);

            /**
             * @brief Compares two colors for inequality.
             * @param left The first collision component.
             * @param right The second collision component.
             * @return `true` if the colors are not equal; otherwise, `false`.
             */
            [[nodiscard]] const bool operator!=(Collision left, Collision right);

            /**
             * @brief Adds two colors component-wise.
             * @param left The first collision component.
             * @param right The second collision component.
             * @return The resulting collision component.
             */
            [[nodiscard]] const Collision operator+(Collision left, Collision right);

            /**
             * @brief Subtracts two colors component-wise.
             * @param left The first collision component.
             * @param right The second collision component.
             * @return The resulting collision component.
             */
            [[nodiscard]] const Collision operator-(Collision left, Collision right);

            /**
             * @brief Multiplies two colors component-wise.
             * @param left The first collision component.
             * @param right The second collision component.
             * @return The resulting collision component.
             */
            [[nodiscard]] const Collision operator*(Collision left, Collision right);

            /**
             * @brief Adds another collision component to the current collision component component-wise.
             * @param left The collision component to modify.
             * @param right The collision component to add.
             * @return Reference to the modified collision component.
             */
            const Collision &operator+=(Collision &left, Collision right);

            /**
             * @brief Subtracts another collision component from the current collision component component-wise.
             * @param left The collision component to modify.
             * @param right The collision component to subtract.
             * @return Reference to the modified collision component.
             */
            const Collision &operator-=(Collision &left, Collision right);

            /**
             * @brief Multiplies another collision component with the current collision component component-wise.
             * @param left The collision component to modify.
             * @param right The collision component to multiply.
             * @return Reference to the modified collision component.
             */
            const Collision &operator*=(Collision &left, Collision right);

        }
    }
}

