#include "orion.h"

Orion::Orion() { }

Orion::~Orion() { }

void Orion::init(std::string textureName, sf::Vector2f position, float speed)
{
    m_speed = speed;
    m_position = position;

    m_texture.loadFromFile(textureName);

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Orion::update(float dt)
{
    m_sprite.move(m_speed * dt, 0);
}

sf::Sprite Orion::getSprite()
{
    return m_sprite;
}