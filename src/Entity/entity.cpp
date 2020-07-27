#include "entity.hpp"
#include <cmath>

Entity::Entity()
    : Entity({0, 0}, 0, {0, 0}, -1)
{}

Entity::Entity(const sf::Vector2f& pos, float maxVel, const sf::Vector2f& hitboxSize, int textureIndex)
{
    setTextureIndex(textureIndex);
    setHitboxSize(hitboxSize);
    setMaxVelocity(maxVel);
    setPosition(pos);
    
    debug = false;
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

sf::Vector2f Entity::getHitboxSize() const
{
    return sf::Vector2f(m_hitbox.width, m_hitbox.height);
}

int Entity::getTextureIndex() const
{
    return m_textureIndex;
}

void Entity::setPosition(const sf::Vector2f& newPos)
{
    m_pos = newPos;
    
    updateHitboxPos();
    updateSpritePos();
}

void Entity::setMaxVelocity(float a)
{
    m_maxVel = (a < 0 : 0 : a);
}

void Entity::setHitboxSize(const sf::Vector2f& a)
{
    if(a.x < 0 || a.y < 0)
        return;
    
    m_hitbox.width = a.x;
    m_hitbox.height = a.y;
    
    updateHitboxPos();
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
    
    m_sprite.setSize({40, 40});
}

void Entity::move(const sf::Vector2f& direction, float velocity)
{
    if(velocity < 0)
        return;
    
    /* Magnitude of vector */
    float mag = std::hypot(direction.x, direction.y);
    if(mag == 0)
        return;
    
    //Normalize vector and stretch by velocity before moving position by vector
    setPosition(m_pos + velocity * (direction / mag));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
    
    if(!debug)
        return;
    
    /* Debug position */
    sf::RectangleShape posShape({5, 5});
    posShape.setPosition(m_pos.x - 3 / 2.f, m_pos.y - 3 / 2.f);
    target.draw(posShape, states);
    
    /* Debug hitbox */
    float borderWidth = 2;
    sf::RectangleShape hbTop({m_hitbox.width, borderWidth});
    hbTop.setPosition(m_hitbox.left, m_hitbox.top);
    target.draw(hbTop, states);
    
    sf::RectangleShape hbBot({m_hitbox.width, borderWidth});
    hbBot.setPosition(m_hitbox.left, m_hitbox.top + m_hitbox.height - borderWidth);
    target.draw(hbBot, states);
    
    sf::RectangleShape hbLeft({borderWidth, m_hitbox.height});
    hbLeft.setPosition(m_hitbox.left, m_hitbox.top);
    target.draw(hbLeft, states);
    
    sf::RectangleShape hbRight({borderWidth, m_hitbox.height});
    hbRight.setPosition(m_hitbox.left + m_hitbox.width - borderWidth, m_hitbox.top);
    target.draw(hbRight, states);
}


void Entity::updateHitboxPos()
{
    m_hitbox.left = m_pos.x - m_hitbox.width / 2;
    m_hitbox.top = m_pos.y - m_hitbox.height;
}

void Entity::updateSpritePos()
{
    sf::Vector2f spriteSize = m_sprite.getSize();
    m_sprite.setPosition(m_pos.x - spriteSize.x / 2, m_pos.y - spriteSize.y);
}