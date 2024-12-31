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
        throw CustomExceptions::FileNotFound(filePath);
    }
    sf::Vector2u node = _texture.getSize();
    _collisionInfo.setDimension({ node.x, node.y });
}

void GUI::ECS::Components::TextureComponent::setTexture(const std::any &texture)
{
    PRECISE_INFO << "Setting the texture" << std::endl;
    if (!texture.has_value()) {
        PRECISE_WARNING << "There is no texture to be processed" << std::endl;
        return;
    }
    try {
        PRECISE_INFO << "Casting texture back to it's initial form" << std::endl;
        sf::Texture text = std::any_cast<sf::Texture>(texture);
        PRECISE_INFO << "Updating texture with the new one using the '=' operator and not the .update function" << std::endl;
        _texture = text;
        PRECISE_INFO << "Getting the texture size" << std::endl;
        sf::Vector2u node = _texture.getSize();
        PRECISE_INFO << "Setting the collision info with the new texture size" << std::endl;
        _collisionInfo.setDimension({ node.x, node.y });
        PRECISE_SUCCESS << "Dimensions for the collisionInfo is set." << std::endl;
    }
    catch (std::bad_any_cast &e) {
        PRECISE_CRITICAL << "The cast failed to retrieve the sf::texture, system error: " << std::string(e.what()) << std::endl;
        throw CustomExceptions::NoTexture("<There is no sf::Texture to be extracted from the std::any cast.>, system error: " + std::string(e.what()));
    }
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
    PRECISE_INFO << "Updating texture component" << std::endl;
    PRECISE_DEBUG << "Updating Visibility" << std::endl;
    setVisible(copy.getVisible());
    PRECISE_DEBUG << "Updated Visibility" << std::endl;
    PRECISE_DEBUG << "Updating Texture" << std::endl;
    setTexture(copy.getTexture());
    PRECISE_DEBUG << "Updated Texture" << std::endl;
    PRECISE_DEBUG << "Updating Collision Info" << std::endl;
    setCollisionInfo(copy.getCollisionInfo());
    PRECISE_DEBUG << "Updated Collision Info" << std::endl;
    PRECISE_SUCCESS << "Out of updating texture component " << std::endl;
}

const std::any GUI::ECS::Components::TextureComponent::getTexture() const
{
    PRECISE_INFO << "Creating an any pointer from the sf::Texture" << std::endl;
    return std::any(sf::Texture(_texture));
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
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
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
