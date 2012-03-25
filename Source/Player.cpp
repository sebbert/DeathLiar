/**
* This file is part of
* 
* 8888888b.                    888    888      888      d8b                  
* 888  "Y88b                   888    888      888      Y8P                  
* 888    888                   888    888      888                           
* 888    888  .d88b.   8888b.  888888 88888b.  888      888  8888b.  888d888 
* 888    888 d8P  Y8b     "88b 888    888 "88b 888      888     "88b 888P"   
* 888    888 88888888 .d888888 888    888  888 888      888 .d888888 888     
* 888  .d88P Y8b.     888  888 Y88b.  888  888 888      888 888  888 888     
* 8888888P"   "Y8888  "Y888888  "Y888 888  888 88888888 888 "Y888888 888   
* 
* Copyright © 2012 Emil Sandstø, Sebastian Reinhard
* 
*/

#include "Player.h"
#include "Entity.h"
#include "World.h"

Player::Player()
{
    m_sideSpeed = 250.0;
    m_forwardSpeed = 250.0;
    m_backwardSpeed = 250.0;
    m_sprite.SetPosition((Real)WINDOW_WIDTH * 0.5, (Real)WINDOW_HEIGHT * 0.5);
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::A)
        {
            m_velocity.x = m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::D)
        {
            m_velocity.x = -m_sideSpeed;
        }
        else if(event.Key.Code == sf::Key::S)
        {
            m_velocity.y = -m_backwardSpeed;
        }
        else if(event.Key.Code == sf::Key::W)
        {
            m_velocity.y = m_forwardSpeed;
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

    //sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    //m_sprite.SetPosition(*vec);

    gWorld.m_level.SetPosition(m_position);
}