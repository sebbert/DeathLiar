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

#include <iostream>

#include "Player.h"
#include "Entity.h"
#include "World.h"
#include "GameMaster.h"

Player::Player()
{
    m_currentWeapon = 0;
    m_type = ENTITY_PLAYER;
}

void Player::Init()
{
    m_speed = gWorld.GetParams().m_playerSpeed;
    m_position = gWorld.GetWindowCenter();
    m_currentWeapon = &m_pistol;
    m_halfWidth -= 10;
}

void Player::HandleEvents(sf::Event &event)
{
    if(event.Type == sf::Event::KeyPressed)
    {
        if(event.Key.Code == sf::Key::A)
        {
            m_velocity.x = -m_speed;
        }
        else if(event.Key.Code == sf::Key::D)
        {
            m_velocity.x = m_speed;
        }
        else if(event.Key.Code == sf::Key::S && !event.Key.Control)
        {
            m_velocity.y = m_speed;
        }
        else if(event.Key.Code == sf::Key::W)
        {
            m_velocity.y = -m_speed;
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

    if(event.Type == sf::Event::MouseButtonPressed)
    {
        //Fire weapon, or use weapon if mouse button is pressed.
        if(event.MouseButton.Button == sf::Mouse::Left)
        {
            m_currentWeapon->Fire();
        }
    }

    if(event.Type == sf::Event::MouseMoved)
    {
        Vec2D mousePos((Real)event.MouseMove.X, (Real)event.MouseMove.Y);

        Vec2D playerPos(m_position.x + gWorld.m_camera.m_position.x + m_halfWidth, m_position.y + gWorld.m_camera.m_position.y + m_halfHeight);
 
        float angle = (float)RadToDeg(AngleBetweenPoints(playerPos, mousePos)) + (Real)90.0;

        m_sprite.SetRotation(angle);
        m_pistol.GetSprite().SetRotation(angle);
        m_pistol.angle = angle;

        m_heading = playerPos - mousePos;
        m_heading.Normalize();

        m_pistol.m_heading = m_heading;
    }
}

void Player::Update(Real duration)
{
    //m_velocity.Truncate(m_speed);
    Vec2D frameVel = m_velocity * duration;
    m_position.x += frameVel.x;

    if(gWorld.GetLevel().CollisionWithWalls(this))
    {
        m_position.x -= frameVel.x;
    }
    m_position.y += frameVel.y;
    if(gWorld.GetLevel().CollisionWithWalls(this))
    {
        m_position.y -= frameVel.y;
    }

    gWorld.m_camera.FollowMe(this, true);

    if(m_position.x < m_halfWidth)
    {
        m_position.x = m_halfWidth;
    }
    else if(m_position.x > gWorld.GetLevel().m_levelWidth - m_halfWidth)
    {
        m_position.x = gWorld.GetLevel().m_levelWidth - m_halfWidth;
    }
    
    if(m_position.y < m_halfHeight)
    {
        m_position.y = m_halfHeight;
    }
    else if(m_position.y > gWorld.GetLevel().m_levelHeight - m_halfHeight)
    {
        m_position.y = gWorld.GetLevel().m_levelHeight - m_halfHeight;
    }

    m_pistol.GetPosition() = m_position;
    m_pistol.Draw(duration);

    gGameMaster.ResolveCollision(this);
    if(m_health <= 0)
    {
        std::cout << "Your are dead, sorry. I bet you have better luck next time!\n" << std::endl;
        gWorld.StopGame();
        gWorld.InitNewGame();
    }
}

Vec2D Player::GetWorldPos()
{
    return m_levelPos + m_position;
}
