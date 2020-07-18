#pragma once
#include "tile.hpp"
#include <sfml/System.hpp>
#include <sfml/Graphics.hpp>

class TileMap
{
public:
    /* Constructors */
    TileMap(const sf::Vector2f& position, const sf::Vector2f& mapSize, const sf::Vector2i& tileCount, int* tiles);
    TileMap(const TileMap&) = delete;
    
    /* Destructor */
    ~TileMap();
    
    /* Getters */
    sf::Vector2f getPosition() const;
    sf::Vector2f getMapSize() const;
    sf::Vector2i getTileCount() const;
    sf::Vector2f getTileSize() const;
    
    /* Setters */
    void setPosition(const sf::Vector2f&);
    void setMapSize(const sf::Vector2f&);
    void setTile(int x, int y, int value);
    void setTiles(int*);
    
    /* Conversions */
    sf::Vector2f tileToPixel(const Tile&) const;
    Tile pixelToTile(const sf::Vector2f&) const;
    
    bool inBounds(const Tile&) const;
    
    void draw(sf::RenderWindow&) const;
    
private:
    /* Helpers */
    void updateTileSize();
    int calcTileIndex(int x, int y) const;
    
    /* Data */
    sf::Vector2f m_pos;
    sf::Vector2f m_mapSize;
    sf::Vector2i m_tileCount;
    sf::Vector2f m_tileSize;
    int* m_tiles;
};