/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.cpp
*/

/**
 * @file RenderComponent.cpp
 * @brief This is the file in charge of managing the rendering
 */

#include "GUI/ECS/Components/TextureComponent.hpp"

GUI::ECS::Components::TextureComponent::TextureComponent() :EntityNode(0) {};

GUI::ECS::Components::TextureComponent::TextureComponent(const TextureComponent &other)
    : EntityNode(0)
{
    update(other);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(0)
{
    setFilePath(filePath);
    setCollisionInfo(collisionInfo);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(0)
{
    setTexture(texture);
    setCollisionInfo(collisionInfo);
}

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId)
    : EntityNode(entityId)
{
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const TextureComponent &other)
    : EntityNode(entityId)
{
    update(other);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(entityId)
{
    setFilePath(filePath);
    setCollisionInfo(collisionInfo);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(entityId)
{
    setTexture(texture);
    setCollisionInfo(collisionInfo);
}

GUI::ECS::Components::TextureComponent::~TextureComponent() {};

void GUI::ECS::Components::TextureComponent::setVisible(const bool visible)
{
    _visible = visible;
}

void GUI::ECS::Components::TextureComponent::setFilePath(const std::string &filePath)
{
    bool loadStatus = _texture.loadFromFile(filePath);
    if (!loadStatus) {
        throw MyException::FileNotFound(filePath);
    }
    sf::Vector2u node = _texture.getSize();
    _collisionInfo.setDimension({ node.x, node.y });
}

void GUI::ECS::Components::TextureComponent::setTexture(const std::any &texture)
{
    if (!texture.has_value()) {
        return;
    }
    sf::Texture text = std::any_cast<sf::Texture>(texture);
    _texture.update(text);
    sf::Vector2u node = _texture.getSize();
    _collisionInfo.setDimension({ node.x, node.y });
}

void GUI::ECS::Components::TextureComponent::setCollisionInfo(const GUI::ECS::Components::CollisionComponent &collisionInfo)
{
    _collisionInfo.update(collisionInfo);
}

void GUI::ECS::Components::TextureComponent::setPosition(const std::pair<int, int> &position)
{
    _collisionInfo.setPosition(position);
}

void GUI::ECS::Components::TextureComponent::setSize(const std::pair<int, int> &size)
{
    _collisionInfo.setDimension(size);
}

void GUI::ECS::Components::TextureComponent::update(const TextureComponent &copy)
{
    setVisible(copy.getVisible());
    setTexture(copy.getTexture());
    setCollisionInfo(copy.getCollisionInfo());
}

const std::any GUI::ECS::Components::TextureComponent::getTexture() const
{
    return std::make_any<sf::Texture>(_texture);
}

const bool GUI::ECS::Components::TextureComponent::getVisible() const
{
    return _visible;
}

const GUI::ECS::Components::CollisionComponent GUI::ECS::Components::TextureComponent::getCollisionInfo() const
{
    return _collisionInfo;
}

const std::string GUI::ECS::Components::TextureComponent::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Texture:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + MyRecodes::myToString(_visible) + "\n";
    result += indentation + "- Collision Info: \n" + _collisionInfo.getInfo(indent + 1) + "\n";
    return result;
}

GUI::ECS::Components::TextureComponent &GUI::ECS::Components::TextureComponent::operator =(const GUI::ECS::Components::TextureComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::TextureComponent &item)
{
    os << item.getInfo();
    return os;
}
