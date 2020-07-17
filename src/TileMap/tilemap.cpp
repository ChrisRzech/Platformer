#include "tilemap.hpp"
#include <stdexcept>

TileMap::TileMap(const sf::Vector2f& position, const sf::Vector2f& mapSize, const sf::Vector2i& tileCount)
    : m_pos(position), m_mapSize(mapSize), m_tileCount(tileCount), m_tiles(nullptr)
{
    /* NOTE:
     * We don't make TILECOUNT unsigned because tiles can't have coordinate
     * values above the max for INT. However, making the tile count negative
     * doesn't make sense, so it is checked.
     */
    if(tileCount.x <= 0 || tileCount.y <= 0)
        throw std::invalid_argument("Tile count size can't be negative");
    
    updateTileSize();
}

sf::Vector2f TileMap::getPosition() const
{
    return m_pos;
}

sf::Vector2f TileMap::getMapSize() const
{
    return m_mapSize;
}

sf::Vector2i TileMap::getTileCount() const
{
    return m_tileCount;
}

sf::Vector2f TileMap::getTileSize() const
{
    return m_tileSize;
}

void TileMap::setPosition(const sf::Vector2f& a)
{
    m_pos = a;
}

void TileMap::setMapSize(const sf::Vector2f& a)
{
    m_mapSize = a;
    updateTileSize();
}

void TileMap::setTiles(int* a)
{
    m_tiles = a;
}

sf::Vector2f TileMap::tileToPixel(const Tile& a) const
{
    float x = a.x * m_tileSize.x;
    float y = a.y * m_tileSize.y;
    return sf::Vector2f(x, y);
}

Tile TileMap::pixelToTile(const sf::Vector2f& a) const
{
    int x = a.x / m_tileSize.x;
    int y = a.y / m_tileSize.y;
    return Tile(x, y);
}

bool TileMap::inBounds(const Tile& a) const
{
    return a.x >= 0 && a.x < m_tileCount.x &&
           a.y >= 0 && a.y < m_tileCount.y;
}

void TileMap::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape rect(m_tileSize);
    
    for(int y = 0; y < m_tileCount.y; y++)
    {
        for(int x = 0; x < m_tileCount.x; x++)
        {
            sf::Color color;
            switch(m_tiles[x + y * m_tileCount.x])
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
            rect.setFillColor(color);
            
            sf::Vector2f windowPosition = tileToPixel(Tile(x, y));
            rect.setPosition(windowPosition);
            window.draw(rect);
        }
    }
}

void TileMap::updateTileSize()
{
    m_tileSize.x = m_mapSize.x / m_tileCount.x;
    m_tileSize.y = m_mapSize.y / m_tileCount.y;
}