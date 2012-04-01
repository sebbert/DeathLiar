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
    m_position = gWorld.GetWindowCenter();
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
        else if(event.Key.Code == sf::Key::S)
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

    if(event.Type == sf::Event::MouseMoved)
    {
        Vec2D mousePos((Real)event.MouseMove.X, (Real)event.MouseMove.Y);
        Vec2D playerPos(m_position.x + m_halfWidth, m_position.y + m_halfHeight);
 
        float angle = (float)RadToDeg(AngleBetweenPoints(playerPos, mousePos)) + (Real)90.0;

        m_sprite.SetRotation(angle);

        m_heading = playerPos - mousePos;
        m_heading.Normalize();
    }
}

void Player::Update(Real duration)
{
    //m_velocity.Truncate(m_speed);
    m_position += m_velocity * duration;

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
}

void Player::UseFreeMovement(Real duration)
{/*
    Vec2D tmpVel = m_velocity.Opposite() * duration;
    Vec2D tmpLevelPos = m_levelPos;
    tmpLevelPos += tmpVel;

    Real lastZoneWidth = (Real)(gWorld.GetLevel().m_levelWidth - gWorld.GetParams().m_zoneWidth);
    Real lastZoneHeight = (Real)(gWorld.GetLevel().m_levelHeight - gWorld.GetParams().m_zoneHeight);

    if(tmpLevelPos.x < 0)
    {
        m_freeMovement |= LEFT;
    }

    if(m_freeMovement & LEFT)
    {
        m_position.x += tmpVel.x;
        m_freeMovement &= 0x1110;
    }

    if(!(m_freeMovement & LEFT))
    {
        m_levelPos.x += -tmpVel.x;
    }
    /*
    if(m_position.x < gWorld.GetWindowCenter().x && timedVel.x > 0
        && -m_levelPos.x < gWorld.GetParams().m_zoneWidth)
    {
        m_position.x += timedVel.x;
        m_levelPos.x = 0;
    }
    else if(m_position.x > gWorld.GetWindowCenter().x && timedVel.x < 0
        && -m_levelPos.x > lastZoneWidth)
    {
        m_position.x += timedVel.x;
        m_levelPos.x = -lastZoneWidth;
    }

    if(m_position.y < gWorld.GetWindowCenter().y && timedVel.y > 0)
    {
        m_position.y += timedVel.y;
        m_levelPos.y = 0;
    }
    else if(m_position.y > gWorld.GetWindowCenter().y && timedVel.y < 0)
    {
        m_position.y += timedVel.y;
        m_levelPos.y = -lastZoneHeight;
    }

    if(oppositeDir.x < 0)
    {
        m_position.x += timedVel.x;
        m_levelPos.x = 0;
    }
    else if(oppositeDir.x > (Real)gWorld.GetLevel().m_levelWidth)
    {
        m_position.x += timedVel.x;
        m_levelPos.x = -lastZoneWidth;
    }

    if(oppositeDir.y < 0)
    {
        m_position.y += timedVel.y;
        m_levelPos.y = 0;
    }
    else if(oppositeDir.y > lastZoneHeight)
    {
        m_position.y += timedVel.y;
        m_levelPos.y = -lastZoneHeight;
    }
    */
}

Vec2D Player::GetWorldPos()
{
    return m_levelPos + m_position;
}
