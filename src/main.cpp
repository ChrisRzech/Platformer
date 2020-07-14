#include <sfml/Graphics.hpp>

int main()
{
    /* Window */
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const sf::VideoMode WINDOW_VIDEO_MODE(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::RenderWindow window(WINDOW_VIDEO_MODE, "Platformer", sf::Style::Default);
    
    /* Game loop */
    while(window.isOpen())
    {
        /* Event polling */
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        /* Drawing */
        window.clear(sf::Color::Magenta);
        window.display();
    }
}