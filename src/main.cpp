#include <sfml/Graphics.hpp>
#include <iostream>
#include "TileMap/tilemap.hpp"

int main()
{
    /* Window */
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Platformer", sf::Style::Default);
    window.setFramerateLimit(60);
    
    /* Tile map */
    const sf::Vector2f TILE_MAP_POS(0, 0);
    const sf::Vector2f TILE_MAP_SIZE((float)windowSize.x, (float)windowSize.y);
    const sf::Vector2i TILE_MAP_COUNT(12, 9);
    int tile_values[TILE_MAP_COUNT.x * TILE_MAP_COUNT.y] =
    {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4,
        0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    };
    TileMap tilemap(TILE_MAP_POS, TILE_MAP_SIZE, TILE_MAP_COUNT, tile_values);
    
    /* Game loop */
    while(window.isOpen())
    {
        /* Event polling */
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            
            default:
                break;
            }
        }
        
        /* Drawing */
        window.clear(sf::Color::Magenta);
        window.draw(tilemap);
        window.display();
    }
}