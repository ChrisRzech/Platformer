#include "input.hpp"

Input::Input(const sf::Window& window)
    : m_window(window)
{
    //Hold an extra one just incase TotalKeyCount's index is accessed
    m_pressed.resize(static_cast<int>(TotalKeyCount + 1));
}

void Input::poll(const std::vector<Key>& keysToCheck)
{
    for(Key key : keysToCheck)
    {
        /* Skip over invalid values */
        if(key < 0 || key == KeyboardKeyCount || key >= TotalKeyCount)
            continue;
        
        int index = static_cast<int>(key);
        
        /* Check if key is a keyboard or mouse key */
        if(key < KeyboardKeyCount)
        {
            m_pressed[index] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
        }
        else
        {
            /* Input::Key has the mouse buttons at the end of the enum.
             * Therefore, convert the Input::Key value to sf::Mouse::Button.
             */
            sf::Mouse::Button converted = static_cast<sf::Mouse::Button>(index - static_cast<int>(KeyboardKeyCount) - 1);
            m_pressed[index] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(converted));
        }
    }
    
    m_mousePos = sf::Mouse::getPosition(m_window);
}

bool Input::keyIsPressed(Key a) const
{
    return m_pressed[a];
}

sf::Vector2i Input::mousePosition() const
{
    return m_mousePos;
}