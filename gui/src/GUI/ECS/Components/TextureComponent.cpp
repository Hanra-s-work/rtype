/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.cpp
*/

/**
 * @file RenderComponent.cpp
 *
 * @brief This is the file in charge of managing the rendering
 */

#include "GUI/ECS/Components/TextureComponent.hpp"

GUI::ECS::Components::TextureComponent::TextureComponent()
    :EntityNode(0), _collisionInfo(0)
{
};

GUI::ECS::Components::TextureComponent::TextureComponent(const TextureComponent &other)
    : EntityNode(0), _collisionInfo(0)
{
    update(other);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(0), _collisionInfo(0)
{
    setFilePath(filePath);
    setCollisionInfo(collisionInfo);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(0), _collisionInfo(0)
{
    setTexture(texture);
    setCollisionInfo(collisionInfo);
}

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId)
    : EntityNode(entityId), _collisionInfo(entityId)
{
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const TextureComponent &other)
    : EntityNode(entityId), _collisionInfo(entityId)
{
    update(other);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(entityId), _collisionInfo(entityId)
{
    setFilePath(filePath);
    setCollisionInfo(collisionInfo);
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::uint32_t entityId, const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo)
    : EntityNode(entityId), _collisionInfo(entityId)
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
    _textureSet = false;
    _texture = std::make_shared<sf::Texture>();
    const bool loadStatus = _texture->loadFromFile(filePath);
    if (loadStatus != true) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "Texture material not found in filepath: '" << filePath << "'." << std::endl;
        throw CustomExceptions::FileNotFound(filePath);
    }
    _textureSet = true;
    PRETTY_SUCCESS << "The texture is set" << std::endl;
    sf::Vector2u node = _texture->getSize();
    _collisionInfo.setDimension({ node.x, node.y });
}

void GUI::ECS::Components::TextureComponent::setTexture(const std::any &texture)
{
    _textureSet = false;
    PRETTY_INFO << "Setting the texture" << std::endl;
    if (!texture.has_value()) {
        PRETTY_WARNING << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "There is no texture to be processed" << std::endl;
        return;
    }
    if (texture.type() == typeid(std::shared_ptr<sf::Texture>)) {
        std::optional<std::shared_ptr<sf::Texture>> textureCapsule = Utilities::unCast<std::shared_ptr<sf::Texture>, CustomExceptions::NoTexture>(texture, true, "<There is no std::shared_ptr<sf::Texture> to be extracted from the std::any cast.>, system error: ");
        if (!textureCapsule.has_value()) {
            PRETTY_ERROR << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "There is no std::shared_ptr<sf::Texture> to be processed" << std::endl;
            throw CustomExceptions::NoTexture("<There is no std::shared_ptr<sf::Texture> to be extracted from the std::any cast.>");
        }
        PRETTY_INFO << "Updating texture with the new one as a copy." << std::endl;
        _texture = std::make_shared<sf::Texture>(*(textureCapsule.value()));
        _textureSet = true;
        PRECISE_SUCCESS << "Updated the texture with the new one as a copy." << std::endl;
    } else if (texture.type() == typeid(sf::Texture)) {
        std::optional<sf::Texture> textCapsule = Utilities::unCast<sf::Texture, CustomExceptions::NoTexture>(texture, true, "<There is no sf::Texture to be extracted from the std::any cast.>, system error: ");
        if (!textCapsule.has_value()) {
            PRETTY_ERROR << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "There is no sf::Texture to be processed" << std::endl;
            throw CustomExceptions::NoTexture("<There is no sf::Texture to be extracted from the std::any cast.>");
        }
        PRETTY_INFO << "Updating texture with the new one using the '=' operator and not the .update function" << std::endl;
        _texture = std::make_shared<sf::Texture>(textCapsule.value());
        _textureSet = true;
        PRETTY_SUCCESS << "Updated the texture with a copy of the passed structure." << std::endl;
    } else {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "No texture (sf::Texture or std::shared_ptr<sf::Texture>) found" << std::endl;
        throw CustomExceptions::NoTexture("<No texture (sf::Texture or std::shared_ptr<sf::Texture>) found>");
    }
    PRETTY_INFO << "Getting the texture size" << std::endl;
    sf::Vector2u node = _texture->getSize();
    PRETTY_INFO << "Setting the collision info with the new texture size" << std::endl;
    _collisionInfo.setDimension({ node.x, node.y });
    PRETTY_SUCCESS << "Dimensions for the collisionInfo is set." << std::endl;
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
    PRETTY_INFO << "Updating texture component" << std::endl;
    PRETTY_DEBUG << "Updating Visibility" << std::endl;
    setVisible(copy.getVisible());
    PRETTY_DEBUG << "Updated Visibility" << std::endl;
    PRETTY_DEBUG << "Updating Texture" << std::endl;
    setTexture(copy.getTexture());
    PRETTY_DEBUG << "Updated Texture" << std::endl;
    PRETTY_DEBUG << "Updating Collision Info" << std::endl;
    setCollisionInfo(copy.getCollisionInfo());
    PRETTY_DEBUG << "Updated Collision Info" << std::endl;
    PRETTY_SUCCESS << "Out of updating texture component " << std::endl;
}

const std::any GUI::ECS::Components::TextureComponent::getTexture() const
{
    PRETTY_INFO << "Creating an any pointer from the std::shared_ptr<sf::Texture>" << std::endl;
    if (!_textureSet) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' " << "The texture is not set, texture collisions '" << _collisionInfo << "'" << std::endl;
        throw CustomExceptions::NoTexture("<There is no std::shared_ptr<sf::Texture> int the class>");
    }
    return std::make_any<std::shared_ptr<sf::Texture>>(_texture);
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
