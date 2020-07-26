#include <sfml/Graphics.hpp>
#include <iostream>
#include "TileMap/tilemap.hpp"
#include "Entity/entity.hpp"

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{
    //Based off of: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
    float windowRatio = static_cast<float>(windowWidth) / windowHeight;
    float viewRatio = static_cast<float>(view.getSize().x) / view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    
    /* Check if horizontal spacing */
    if(windowRatio >= viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    
    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int main()
{
    /* Window */
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Platformer", sf::Style::Default);
    window.setFramerateLimit(60);
    
    /* View */
    sf::View view;
    view.setSize(windowSize.x, windowSize.y);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = getLetterboxView(view, windowSize.x, windowSize.y);
    
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
    
    /* Entities */
    Entity entity({100, 150}, 10, {50, 50}, 2);
    
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
                
            case sf::Event::Resized:
                view = getLetterboxView(view, event.size.width, event.size.height);
                break;
            
            default:
                break;
            }
        }
        
        sf::Vector2f dir(0, 0);
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            dir.y += -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            dir.y += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            dir.x += -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dir.x += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            entity.setHitboxSize(entity.getHitboxSize() * 1.01f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            entity.setHitboxSize(entity.getHitboxSize() * 0.99f);
        
        entity.move(dir, 5);
        
        /* Drawing */
        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(tilemap);
        window.draw(entity);
        window.display();
    }
}