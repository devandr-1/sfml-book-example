#include "hero.h"

Hero::Hero() { }

Hero::~Hero() { }

void Hero::init(std::string textureName, sf::Vector2f position, float mass)
{
    m_position = position;
    m_mass = mass;

    m_grounded = false;

    m_texture.loadFromFile(textureName.c_str());

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Hero::update(float dt)
{
    m_velocity -= m_mass * m_gravity * dt;
    m_position.y -= m_velocity * dt;

    m_sprite.setPosition(m_position);

    if (m_position.y >= 768.f * 0.75f) {
        m_position.y = 768 * 0.75f;
        m_velocity = 0;
        m_grounded = true;
        jump_count = 0;
    }
}

void Hero::jump(float velocity)
{
    if (jump_count < 2) {
        jump_count++;

        m_velocity = velocity;
        m_grounded = false;
    }
}

sf::Sprite Hero::getSprite()
{
    return m_sprite;
}