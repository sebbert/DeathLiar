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

#include "Enemy.h"
#include "World.h"
#include "Mathutil.h"

Enemy::Enemy()
{
	m_Speed = 0.0;
	m_MaxLives = 0;
	m_Lives = 0;
	m_MaxHealth = 0;
	m_Health = 0;
    m_heading.y = 1.0;
}

Enemy::~Enemy()
{
	
}

void Enemy::SetMass(Real mass)
{
    m_mass = mass;
}

void Enemy::Update(Real duration)
{
    Vec2D acceleration = Arrive() / m_mass;
    m_velocity += acceleration * duration;
    
    m_velocity.Truncate(m_Speed);

    m_localPos += m_velocity * duration;

    m_position = gWorld.GetLevelPos() + m_localPos;

    m_velocity *= 0.99;

    if(m_velocity.MagnitudeSquared() > 0.000000001)
    {
        m_heading = Normalize(m_velocity);
        float angle = RadToDeg(AngleBetweenPoints(m_heading, Vec2D(0, 0)));

        m_sprite.SetRotation(angle - 90);
    }

    PrintVec2D("Position", m_position);
    PrintVec2D("Enemy Velocity", m_velocity);
}

Vec2D Enemy::Pursuit()
{
    Vec2D playerPos = gWorld.GetPlayer().GetWorldPos();
    Vec2D toPlayer = playerPos - m_position;
    Vec2D force;

    Real length = toPlayer.Magnitude();  
    Real relativeHeading = m_heading * gWorld.GetPlayer().GetHeading();
    //Player is right in front, don't predict position.
    if(toPlayer * m_heading > 0 && relativeHeading < -0.95)
    {
        force = toPlayer / length;
        force *= m_Speed;
        PrintVec2D("Enemy In front of you", gWorld.GetPlayer().GetWorldPos());
    }
    else
    {
        Real lookAhead = length / (gWorld.GetPlayer().GetSpeed() + m_Speed);
        Vec2D futurePos = (playerPos + gWorld.GetPlayer().GetVelocity()) * lookAhead;
        PrintVec2D("Enemy Target", futurePos);
        force = Normalize(futurePos - m_position) * m_Speed;
    }

    force -= m_velocity;

    return force;
}

Vec2D Enemy::Arrive()
{
    PrintVec2D("Enemy Target", gWorld.GetPlayer().GetPosition());
    Vec2D toPlayer = gWorld.GetPlayer().GetPosition() - m_position;
    Real dist = toPlayer.Magnitude();
    if(dist > 0)
    {
        Real speed = dist / 0.9;

        speed = Min(speed, m_Speed);

        Vec2D velocity = toPlayer * speed / dist;
        return velocity - m_velocity;
    }

    return Vec2D(0, 0);
}

void Enemy::SetSpeed(Real speed)
{
	m_Speed = speed;
}

void Enemy::SetLives(int lives)
{
	m_Lives = lives;
}

void Enemy::SetMaxLives(int maxLives)
{
	m_MaxLives = maxLives;
}

void Enemy::SetHealth(int health)
{
	m_Health = health;
}

void Enemy::SetMaxHealth(int maxHealth)
{
	m_MaxHealth = maxHealth;
}

void Enemy::Damage()
{
	m_Health--;
}

void Enemy::Hurt()
{
	m_Health = m_MaxHealth;
	m_Lives--;
}

void Enemy::Kill()
{
	m_Health = m_Lives = 0;
}

void Enemy::Destroy()
{
}

void Enemy::Init()
{
}