#include "Player.h"
#include "Entity.h"

Player::Player()
{
    m_sideSpeed = 250.0;
    m_forwardSpeed = 250.0;
    m_backwardSpeed = 250.0;
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::A)
        {
            m_velocity.x = -m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::D)
        {
            m_velocity.x = m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::S)
        {
            m_velocity.y = m_backwardSpeed;
        }
        else if(event.Key.Code == sf::Key::W)
        {
            m_velocity.y = -m_forwardSpeed;
        }
    }

    if(event.Type == sf::Event::KeyReleased)
    {
        if(event.Key.Code == sf::Key::A || event.Key.Code == sf::Key::D)
        {
            m_velocity.x = 0;
        }
        else if(event.Key.Code == sf::Key::S || event.Key.Code == sf::Key::W)
        {
            m_velocity.y = 0;
        }
    }
}

void Player::Update(Real duration)
{
    Vec2D tmp = m_velocity;
    tmp.Truncate(m_sideSpeed);
    m_position += tmp * duration;

    sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    m_sprite.SetPosition(*vec);
}