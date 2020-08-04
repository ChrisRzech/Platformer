#include "input.hpp"

Input::Input(const sf::Window& window, const std::vector<Key>& keysToPoll)
    : m_window(window), m_keysToPoll(keysToPoll)
{
    m_pressed.resize(static_cast<int>(TotalKeyCount));
    m_released.resize(static_cast<int>(TotalKeyCount));
}

void Input::setKeysToPoll(const std::vector<Key>& keysToPoll)
{
    m_keysToPoll = keysToPoll;
}

void Input::poll()
{
    for(Key key : m_keysToPoll)
    {
        /* Skip over invalid values */
        if(key < 0 || key == KeyboardKeyCount || key >= TotalKeyCount)
            continue;
        
        int index = static_cast<int>(key);
        bool wasPressed = m_pressed[index];
        
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
        
        /* Check if the key was released after polling */
        bool isPressed = m_pressed[index];
        m_released[index] = wasPressed && !isPressed;
    }
    
    m_mousePos = sf::Mouse::getPosition(m_window);
}

bool Input::isPressed(Key a) const
{
    return m_pressed[a];
}

bool Input::wasReleased(Key a) const
{
    return m_released[a];
}

sf::Vector2i Input::mousePosition() const
{
    return m_mousePos;
}