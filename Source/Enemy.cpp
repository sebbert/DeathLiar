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

Enemy::Enemy()
{
	m_Speed = 0.0;
	m_MaxLives = 0;
	m_Lives = 0;
	m_MaxHealth = 0;
	m_Health = 0;
}

Enemy::~Enemy()
{
	
}

void Enemy::Update(Real duration)
{
    Vec2D playerPosition = gWorld.GetPlayer().GetWorldPos();
    Vec2D vel = playerPosition - m_position;
	vel.Normalize();
	vel *= m_Speed;

    m_velocity = vel - m_velocity;
    m_position += gWorld.GetLevelPos();
    m_position += m_velocity * duration;
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