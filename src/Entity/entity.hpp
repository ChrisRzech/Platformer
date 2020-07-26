#include <sfml/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
    /* Constructors */
    Entity();
    Entity(const sf::Vector2f& position, float maxVelocity, const sf::Vector2f& hitboxSize, int textureIndex);
    
    /* Getters */
    sf::Vector2f getPosition() const;
    float getMaxVelocity() const;
    sf::FloatRect getHitbox() const;
    sf::Vector2f getHitboxSize() const;
    int getTextureIndex() const;
    
    /* Setters */
    void setPosition(const sf::Vector2f&);
    void setMaxVelocity(float);
    void setHitboxSize(const sf::Vector2f&);
    void setTextureIndex(int);
    
    void move(const sf::Vector2f& direction, float velocity);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    /* Helpers */
    void updateHitboxPos();
    void updateSpritePos();
    
    /* Data */
    sf::Vector2f m_pos;
    float m_maxVel;
    sf::FloatRect m_hitbox;
    int m_textureIndex;
    //sf::Sprite m_sprite;
    sf::RectangleShape m_sprite;
};