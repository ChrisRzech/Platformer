#include "tilemap.hpp"
#include <stdexcept>

TileMap::TileMap(const sf::Vector2f& position, const sf::Vector2f& mapSize, const sf::Vector2i& tileCount, int* tiles)
    : m_pos(position), m_mapSize(mapSize), m_tileCount(tileCount), m_tiles(nullptr)
{
    /* NOTE:
     * Since tiles have signed integer coordinates, TILECOUNT is a signed integer vector.
     * However, we must check if TILECOUNT's components are negative.
     */
    if(tileCount.x <= 0 || tileCount.y <= 0)
        throw std::invalid_argument("Tile count can't be negative");
    
    updateTileSize();
    
    setTiles(tiles);
}

TileMap::~TileMap()
{
    delete[] m_tiles;
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

void TileMap::setTile(int x, int y, int value)
{
    if(x < 0 || x >= m_tileCount.x ||
       y < 0 || y >= m_tileCount.y)
        return;
    
    m_tiles[calcTileIndex(x, y)] = value;
}

void TileMap::setTiles(int* tiles)
{
    delete[] m_tiles;
    
    /* Deep copy of tile values */
    m_tiles = new int[m_tileCount.x * m_tileCount.y]{0};
    for(int i = 0; i < m_tileCount.x * m_tileCount.y; i++)
        m_tiles[i] = tiles[i];
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

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_tiles == nullptr)
        return;
    
    sf::RectangleShape rect(m_tileSize);
    
    for(int y = 0; y < m_tileCount.y; y++)
    {
        for(int x = 0; x < m_tileCount.x; x++)
        {
            //TODO: replace colors with textures
            sf::Color color;
            switch(m_tiles[calcTileIndex(x, y)])
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
            
            sf::Vector2f rectPos = tileToPixel(Tile(x, y));
            rectPos.x += m_pos.x;
            rectPos.y += m_pos.y;
            rect.setPosition(rectPos);
            
            target.draw(rect, states);
        }
    }
}

void TileMap::updateTileSize()
{
    m_tileSize.x = m_mapSize.x / m_tileCount.x;
    m_tileSize.y = m_mapSize.y / m_tileCount.y;
}

int TileMap::calcTileIndex(int x, int y) const
{
    return x + y * m_tileCount.x;
}