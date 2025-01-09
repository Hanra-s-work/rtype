/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ImageComponent.cpp
*/

/**
 * @file ImageComponent.cpp
 *
 * @brief This is the file in charge of managing the text
 */

#include "GUI/ECS/Components/ImageComponent.hpp"

GUI::ECS::Components::ImageComponent::ImageComponent()
    : EntityNode(0), _collision(0), _base(0),
    _normalColor(0, GUI::ECS::Systems::Colour::White), _hoverColor(0, GUI::ECS::Systems::Colour::White), _clickedColor(0, GUI::ECS::Systems::Colour::White)
{
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId)
    : EntityNode(entityId), _collision(entityId), _base(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, const std::string &name, const std::string &application)
    : EntityNode(entityId), _collision(entityId), _base(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imageTexture, name);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const std::string &name, const std::string &application)
    : EntityNode(entityId), _collision(entityId), _base(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imageTexture, name);
    setDimension(dimensions);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::string &name, const std::string &application)
    : EntityNode(entityId), _collision(entityId), _base(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imageTexture, name);
    setDimension(dimensions);
    setClickedColor(clickedColor);
    setHoverColor(hoverColor);
    setNormalColor(normalColor);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::string &name, const std::string &application)
    : EntityNode(entityId), _collision(entityId), _base(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imageTexture, name);
    setDimension(dimensions);
    setPosition(position);
    setNormalColor(normalColor);
    setHoverColor(hoverColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const std::string &imagePath, const std::string &name, const std::string &application)
    : EntityNode(entityId), _base(entityId), _collision(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imagePath, name);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const std::string &name, const std::string &application)
    : EntityNode(entityId), _base(entityId), _collision(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imagePath, name);
    setDimension(dimensions);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::string &name, const std::string &application)
    : EntityNode(entityId), _base(entityId), _collision(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imagePath, name);
    setDimension(dimensions);
    setNormalColor(normalColor);
    setHoverColor(hoverColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent::ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColor, const GUI::ECS::Systems::Colour &hoverColor, const GUI::ECS::Systems::Colour &clickedColor, const std::string &name, const std::string &application)
    : EntityNode(entityId), _base(entityId), _collision(entityId),
    _normalColor(entityId, GUI::ECS::Systems::Colour::White), _hoverColor(entityId, GUI::ECS::Systems::Colour::White), _clickedColor(entityId, GUI::ECS::Systems::Colour::White)
{
    _inConstructor = true;
    setApplication(application);
    setImage(imagePath, name);
    setDimension(dimensions);
    setPosition(position);
    setNormalColor(normalColor);
    setHoverColor(hoverColor);
    setClickedColor(clickedColor);
    _inConstructor = false;
    _processImageComponent();
};


GUI::ECS::Components::ImageComponent::~ImageComponent() {};

void GUI::ECS::Components::ImageComponent::setName(const std::string &name)
{
    _name = name;
}

void GUI::ECS::Components::ImageComponent::setApplication(const std::string &application)
{
    _application = application;
}

void GUI::ECS::Components::ImageComponent::setNormalColor(const GUI::ECS::Systems::Colour &color)
{
    _normalColor = color;
}

void GUI::ECS::Components::ImageComponent::setHoverColor(const GUI::ECS::Systems::Colour &color)
{
    _hoverColor = color;
};

void GUI::ECS::Components::ImageComponent::setClickedColor(const GUI::ECS::Systems::Colour &color)
{
    _clickedColor = color;
};

void GUI::ECS::Components::ImageComponent::setImage(const GUI::ECS::Components::TextureComponent &image, const std::string &name)
{
    _base = image;
    if (!name.empty()) {
        _name = name;
    }
    _textureAltered = true;
    if (!_inConstructor) {
        _processImageComponent();
    }
};

void GUI::ECS::Components::ImageComponent::setImage(const std::string &path, const std::string &name)
{
    _base.setFilePath(path);
    if (!name.empty()) {
        _name = name;
    }
    if (!_inConstructor) {
        _processImageComponent();
    }
};

void GUI::ECS::Components::ImageComponent::setDimension(const std::pair<int, int> &dimension)
{
    _collision.setDimension(dimension);
    _base.setSize(dimension);
    _sizeAltered = true;
    if (!_inConstructor) {
        _processImageComponent();
    }
};

void GUI::ECS::Components::ImageComponent::setPosition(const std::pair<int, int> &position)
{
    _collision.setPosition(position);
    _base.setPosition(position);
    _positionAltered = true;
    if (!_inConstructor) {
        _processImageComponent();
    }
};

void GUI::ECS::Components::ImageComponent::setVisible(const bool visible)
{
    _visible = visible;
};

void GUI::ECS::Components::ImageComponent::setLevelBackgroundCompatible(const bool levelBackground)
{
    _levelBackground = levelBackground;
}

void GUI::ECS::Components::ImageComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
};

const bool GUI::ECS::Components::ImageComponent::isVisible() const
{
    return _visible;
}

const bool GUI::ECS::Components::ImageComponent::isLevelBackgroundCompatible() const
{
    return _levelBackground;
}

const std::string GUI::ECS::Components::ImageComponent::getName() const
{
    return _name;
}

const std::string GUI::ECS::Components::ImageComponent::getApplication() const
{
    return _application;
}

const GUI::ECS::Components::TextureComponent GUI::ECS::Components::ImageComponent::getImage() const
{
    return _base;
};

const GUI::ECS::Systems::Colour GUI::ECS::Components::ImageComponent::getNormalColor() const
{
    return _normalColor;
};

const GUI::ECS::Systems::Colour GUI::ECS::Components::ImageComponent::getHoverColor() const
{
    return _hoverColor;
};

const GUI::ECS::Systems::Colour GUI::ECS::Components::ImageComponent::getClickedColor() const
{
    return _clickedColor;
};

const std::pair<int, int> GUI::ECS::Components::ImageComponent::getDimension() const
{
    return _collision.getDimension();
};

const std::pair<int, int> GUI::ECS::Components::ImageComponent::getPosition() const
{
    return _collision.getPosition();
};

const bool GUI::ECS::Components::ImageComponent::getVisible() const
{
    return _visible;
};

const GUI::ECS::Systems::Collision GUI::ECS::Components::ImageComponent::getCollision() const
{
    return _collision;
}

const std::string GUI::ECS::Components::ImageComponent::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Image:\n";
    result += indentation + "- EntityId: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
    result += indentation + "- Size altered: " + Recoded::myToString(_sizeAltered) + "\n";
    result += indentation + "- In Constructor: " + Recoded::myToString(_inConstructor) + "\n";
    result += indentation + "- Texture altered: " + Recoded::myToString(_textureAltered) + "\n";
    result += indentation + "- Position altered: " + Recoded::myToString(_positionAltered) + "\n";
    result += indentation + "- Name: " + _name + "\n";
    result += indentation + "- Application: " + _application + "\n";
    result += indentation + "- Image Component present?: " + Recoded::myToString(_sfImage.has_value()) + "\n";
    result += indentation + "- Position: {\n" + _collision.getInfo(indent + 1) + "}\n";
    result += indentation + "- Texture Base: {\n" + _base.getInfo(indent + 1) + "}\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    return result;
};

const bool GUI::ECS::Components::ImageComponent::getLevelBackgroundCompatibility() const
{
    return isLevelBackgroundCompatible();
}

std::any GUI::ECS::Components::ImageComponent::render() const
{
    if (!_visible || !_sfImage.has_value()) {
        PRETTY_INFO << "Instance is hidden or no sfImage instance found, not rendering" << std::endl;
        return std::nullopt;
    }
    return std::make_any<sf::Sprite>(_sfImage.value());
};

void GUI::ECS::Components::ImageComponent::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _collision.update(mouse);
    _processImageComponent();
};

void GUI::ECS::Components::ImageComponent::update(const GUI::ECS::Components::ImageComponent &copy)
{
    _inConstructor = true;

    setName(copy.getName());
    setApplication(copy.getApplication());

    setImage(copy.getImage());
    setVisible(copy.getVisible());

    _collision = copy.getCollision();
    setPosition(copy.getPosition());
    setDimension(copy.getDimension());

    setHoverColor(copy.getHoverColor());
    setNormalColor(copy.getNormalColor());
    setClickedColor(copy.getClickedColor());

    setLevelBackgroundCompatible(copy.getLevelBackgroundCompatibility());

    _inConstructor = false;
    _processImageComponent();
};

GUI::ECS::Components::ImageComponent &GUI::ECS::Components::ImageComponent::operator=(const GUI::ECS::Components::ImageComponent &copy)
{
    update(copy);
    return *this;
}

void GUI::ECS::Components::ImageComponent::_initialiseImage()
{
    if (!_sfImage.has_value()) {
        const std::any textureCapsule = _base.getTexture();
        if (textureCapsule.has_value()) {
            if (textureCapsule.type() != typeid(std::shared_ptr<sf::Texture>)) {
                PRETTY_ERROR << "Texture is not a shared_ptr<sf::Texture>" << std::endl;
                throw CustomExceptions::NoTexture("<No texture was found when a texture of type sf::Texture was expected>");
            }
            const std::string errMsg = "<No texture was found when a texture of type sf::Texture was expected>, system error: ";
            const std::optional<std::shared_ptr<sf::Texture>> texture = Utilities::unCast<std::shared_ptr<sf::Texture>, CustomExceptions::NoTexture>(textureCapsule, true, errMsg);
            if (!texture.has_value()) {
                PRETTY_ERROR << errMsg << std::endl;
                throw CustomExceptions::NoTexture(errMsg);
            }
            _sfImage.emplace(*(texture.value()));
        }
    }
}

void GUI::ECS::Components::ImageComponent::_processColour()
{
    if (!_sfImage.has_value()) {
        PRETTY_WARNING << "ImageComponent has no image" << std::endl;
        return;
    }
    std::any systemColour;
    if (_collision.isClicked()) {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _clickedColor << "\n} and corresponds to the _clickedColour"
            << std::endl;
        systemColour = _clickedColor.getRenderColour();
    } else if (_collision.isHovered()) {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _hoverColor << "\n} and corresponds to the _hoverColour"
            << std::endl;
        systemColour = _hoverColor.getRenderColour();
    } else {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _normalColor << "\n} and corresponds to the _normalColour"
            << std::endl;
        systemColour = _normalColor.getRenderColour();
    }
    const std::string errMsg = "<The content returned by the getRenderColour function is not of type sf::Color>, system error: ";
    const std::optional<sf::Color> color = Utilities::unCast<sf::Color, CustomExceptions::NoColour>(systemColour, true, errMsg);
    if (!color.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "No Color found, " << errMsg << std::endl;
        throw CustomExceptions::NoColour(errMsg);
    }
    _sfImage->setColor(color.value());
    PRETTY_SUCCESS << "Image colour has been set" << std::endl;
}

void GUI::ECS::Components::ImageComponent::_processImageComponent()
{
    if (!_sfImage.has_value()) {
        _initialiseImage();
    }
    _processColour();
    if (_sfImage.has_value()) {
        if (_sizeAltered) {
            PRETTY_DEBUG << "The size has been altered, updating size." << std::endl;
            std::pair<float, float> dimension = _collision.getDimension();
            _sfImage->setScale({ dimension.first, dimension.second });
            _sizeAltered = false;
        }
        if (_positionAltered) {
            PRETTY_DEBUG << "The position has been altered, updating position." << std::endl;
            std::pair<float, float> position = _collision.getPosition();
            _sfImage->setPosition({ position.first, position.second });
            _positionAltered = false;
        }
        if (_textureAltered) {
            PRETTY_DEBUG << "The texture has been altered, updating image." << std::endl;
            const std::any textureCapsule = _base.getTexture();
            if (textureCapsule.type() == typeid(std::shared_ptr<sf::Texture>) && textureCapsule.has_value()) {
                const std::string errMsg = "<There is no texture instance in this cast, expected a cast of type sf::Texture>, system error: ";
                const std::optional<std::shared_ptr<sf::Texture>> texture = Utilities::unCast<std::shared_ptr<sf::Texture>, CustomExceptions::NoTexture>(textureCapsule, true, errMsg);
                if (texture.has_value()) {
                    _sfImage->setTexture(*(texture.value()));
                    _textureAltered = false;
                }
            }
        }
    }
}

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ImageComponent &item)
{
    os << item.getInfo();
    return os;
}
