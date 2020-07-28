#include "input.hpp"

Input::Input(const sf::Window& window)
    : m_window(window)
{
    m_keyboardKeys.resize(static_cast<int>(sf::Keyboard::KeyCount));
    m_mouseButtons.resize(static_cast<int>(sf::Mouse::ButtonCount));
}

void Input::poll(const std::vector<sf::Keyboard::Key>& keysToCheck,
                 const std::vector<sf::Mouse::Button>& buttonsToCheck)
{
    for(sf::Keyboard::Key key : keysToCheck)
        m_keyboardKeys[static_cast<int>(key)] = sf::Keyboard::isKeyPressed(key);
    
    for(sf::Mouse::Button button : buttonsToCheck)
        m_mouseButtons[static_cast<int>(button)] = sf::Mouse::isButtonPressed(button);
    
    m_mousePos = sf::Mouse::getPosition(m_window);
}

bool Input::keyIsPressed(sf::Keyboard::Key a) const
{
    return m_keyboardKeys[a];
}

bool Input::mouseIsPressed(sf::Mouse::Button a) const
{
    return m_mouseButtons[a];
}

sf::Vector2i Input::mousePosition() const
{
    return m_mousePos;
}