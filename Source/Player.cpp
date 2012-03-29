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
#include <iostream>

Player::Player()
{
}

void Player::Init()
{
    m_speed = gWorld.GetParams().m_playerSpeed;
    m_position.Set((Real)gWorld.GetParams().m_windowWidth * 0.5, (Real)gWorld.GetParams().m_windowHeight * 0.5);
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::A)
        {
            m_velocity.x = m_speed;
        }
        else if(event.Key.Code == sf::Key::D)
        {
            m_velocity.x = -m_speed;
        }
        else if(event.Key.Code == sf::Key::S)
        {
            m_velocity.y = -m_speed;
        }
        else if(event.Key.Code == sf::Key::W)
        {
            m_velocity.y = m_speed;
        }
        if(event.Key.Code == sf::Key::H)
        {
            m_levelPos.x = m_speed;
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

    if(event.Type == sf::Event::MouseMoved)
    {
        Vec2D mousePos(event.MouseMove.X, event.MouseMove.Y);
        Vec2D playerPos((Real)gWorld.GetParams().m_windowWidth * 0.5 + 64 * 0.5, (Real)gWorld.GetParams().m_windowHeight * 0.5 + 64 * 0.5);
 
        float angle = RadToDeg(AngleBetweenPoints(playerPos, mousePos)) + 90.0;

        m_sprite.SetRotation(angle);

        m_heading = playerPos - mousePos;
        m_heading.Normalize();
    }
}

void Player::Update(Real duration)
{
    m_velocity.Truncate(m_speed);

    m_levelPos += m_velocity * duration;

    //Vec2D pos = *(Vec2D*)&m_transformMat.Transform(*(sf::Vector2f *)&m_position);
    //sf::Vector2f *vec = (sf::Vector2f *)&m_position;
    //m_sprite.SetPosition(*vec);

    gWorld.GetLevel().SetPosition(m_levelPos);
}

Vec2D Player::GetWorldPos()
{
    return m_levelPos + m_position;
}
