#include "Player.h"
#include "Entity.h"

Player::Player()
{
    m_sideSpeed = 50.0;
    m_forwardSpeed = 64.0;
    m_backwardSpeed = 64.0;
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
}

void Player::Update(Real duration)
{
    m_position += m_velocity * duration;

    m_velocity.Zero();

    sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    m_sprite.SetPosition(*vec);
}