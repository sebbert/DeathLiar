#include "Player.h"
#include "Entity.h"

Player::Player()
{
    m_sideSpeed = 200.0;
    m_forwardSpeed = 100.0;
    m_backwardSpeed = 100.0;
    m_accSpeed = 100.0;
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::A)
        {
            m_acceleration.x = -m_accSpeed;
        }
        else if(event.Key.Code == sf::Key::D)
        {
            m_acceleration.x = m_accSpeed;
        }
        else if(event.Key.Code == sf::Key::S)
        {
            m_acceleration.y = m_accSpeed;
        }
        else if(event.Key.Code == sf::Key::W)
        {
            m_acceleration.y = -m_accSpeed;
        }
    }
}

void Player::Update(Real duration)
{
    m_velocity += m_acceleration * duration;
    m_acceleration.Zero();
    m_velocity.Truncate(m_sideSpeed);

    m_position += m_velocity * duration;

    m_velocity *= 0.97;

    sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    m_sprite.SetPosition(*vec);
}