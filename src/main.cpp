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
    sf::Vector2i tileMapSize(8, 6);
    int tiles[8 * 6] =
    {
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
    };
    TileMap tilemap({0, 0}, {(float)windowSize.x, (float)windowSize.y}, tileMapSize);
    tilemap.setTiles(tiles);
    
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
        tilemap.draw(window);
        window.display();
    }
}