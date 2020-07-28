#include <sfml/Window.hpp>
#include <vector>

class Input
{
public:
    /* Constructors */
    Input(const sf::Window&);
   
    void poll(const std::vector<sf::Keyboard::Key>& keysToCheck,
              const std::vector<sf::Mouse::Button>& buttonsToCheck);
    bool keyIsPressed(sf::Keyboard::Key) const;
    bool mouseIsPressed(sf::Mouse::Button) const;
    sf::Vector2i mousePosition() const;
    
private:
    const sf::Window& m_window;
    std::vector<bool> m_keyboardKeys;
    std::vector<bool> m_mouseButtons;
    sf::Vector2i m_mousePos;
};