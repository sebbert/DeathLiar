#include "Player.h"
#include "Entity.h"

Player::Player()
{
    m_sideSpeed = 100.0;
    m_forwardSpeed = 100.0;
    m_backwardSpeed = 100.0;
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::Left)
        {
            m_velocity.x = -m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::Right)
        {
            m_velocity.x = m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::Down)
        {
            m_velocity.y = m_backwardSpeed;
        }
        else if(event.Key.Code == sf::Key::Up)
        {
            m_velocity.y = -m_forwardSpeed;
        }
    }

    if(event.Type == sf::Event::KeyReleased)
    {
        if(event.Key.Code == sf::Key::Left)
        {
            m_velocity.x = 0;
        }
        else if(event.Key.Code == sf::Key::Right)
        {
            m_velocity.x = 0;
        }
        else if(event.Key.Code == sf::Key::Down)
        {
            m_velocity.y = 0;
        }
        else if(event.Key.Code == sf::Key::Up)
        {
            m_velocity.y = 0;
        }
    }
}

void Player::Update(Real duration)
{
    m_position += m_velocity * duration;
    sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    m_sprite.SetPosition(*vec);
}