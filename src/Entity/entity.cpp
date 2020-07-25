#include "entity.hpp"

Entity::Entity()
    : Entity({0, 0}, 0, {0, 0}, -1)
{}

Entity::Entity(const sf::Vector2f& pos, float maxVel, const sf::Vector2f& hitboxSize, int textureIndex)
{
    setPosition(pos);
    setMaxVelocity(maxVel);
    setHitboxSize(hitboxSize);
    setTextureIndex(textureIndex);
}

sf::Vector2f Entity::getPosition() const
{
    return m_pos;
}

float Entity::getMaxVelocity() const
{
    return m_maxVel;
}

sf::FloatRect Entity::getHitbox() const
{
    return m_hitbox;
}

int Entity::getTextureIndex() const
{
    return m_textureIndex;
}

void Entity::setPosition(const sf::Vector2f& a)
{
    m_pos = a;
    
    sf::Vector2f spriteSize = m_sprite.getSize();
    m_sprite.setPosition(a.x - spriteSize.x / 2, a.y - spriteSize.y);
}

void Entity::setMaxVelocity(float a)
{
    m_maxVel = a;
}

void Entity::setHitboxSize(const sf::Vector2f& a)
{
    m_hitbox.left = m_pos.x - a.x / 2;
    m_hitbox.top = m_pos.y - a.y;
    m_hitbox.width = a.x;
    m_hitbox.height = a.y;
}

void Entity::setTextureIndex(int a)
{
    m_textureIndex = a;
    
    sf::Color color;
    switch(a)
    {
    case 1:
        color = sf::Color::White;
        break;
    case 2:
        color = sf::Color::Red;
        break;
    case 3:
        color = sf::Color::Green;
        break;
    case 4:
        color = sf::Color::Blue;
        break;
    default:
        color = sf::Color::Black;
        break;
    }
    m_sprite.setFillColor(color);
    
    m_sprite.setSize({50, 50});
}

void Entity::move(const sf::Vector2f& direction, float velocity)
{
    
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}