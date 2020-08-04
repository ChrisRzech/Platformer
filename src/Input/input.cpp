#include "input.hpp"

Input::Input(const sf::Window& window, int holdThreshold, const std::vector<Key>& keysToPoll)
    : m_window(window), m_keysToPoll(keysToPoll)
{
    setHoldThreshold(holdThreshold);
    
    m_pressed.resize(static_cast<int>(TotalKeyCount));
    m_released.resize(static_cast<int>(TotalKeyCount));
    m_heldLoops.resize(static_cast<int>(TotalKeyCount));
}

bool Input::isPressed(Key a) const
{
    return m_pressed[static_cast<int>(a)];
}

bool Input::wasReleased(Key a) const
{
    return m_released[static_cast<int>(a)];
}

bool Input::isHeld(Key a) const
{
    return m_heldLoops[static_cast<int>(a)] == m_holdThreshold;
}

sf::Vector2i Input::mousePosition() const
{
    return m_mousePos;
}

void Input::setKeysToPoll(const std::vector<Key>& a)
{
    m_keysToPoll = a;
}

void Input::setHoldThreshold(int a)
{
    m_holdThreshold = (a < MIN_HOLD_THRESHOLD ? MIN_HOLD_THRESHOLD : a);
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
        bool wasReleased = wasPressed && !isPressed;
        m_released[index] = wasReleased;
        
        /* Handle key holding */
        if(wasReleased)
        {
            m_heldLoops[index] = 0;
        }
        else if(isPressed)
        {
            m_heldLoops[index]++;
            
            /* Cap out at the threshold */
            if(m_heldLoops[index] > m_holdThreshold)
                m_heldLoops[index] = m_holdThreshold;
            
            
        }
    }
    
    m_mousePos = sf::Mouse::getPosition(m_window);
}