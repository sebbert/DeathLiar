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
#include "Weapon.h"

Enemy::Enemy()
{
	m_Speed = 0.0;
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

    m_position += m_velocity * duration;

    m_velocity *= std::pow((Real)0.99, duration);

    if(m_velocity.MagnitudeSquared() > 0.000000001)
    {
        m_heading = Normalize(m_velocity);
        Vec2D empty;
        float angle = RadToDeg(AngleBetweenPoints(m_heading, empty));

        m_sprite.SetRotation(angle - 90);
    }

    gBulletMgr.ResolveCollisions(this);
    if(gWorld.GetLevel().CollisionWithWalls(this))
    {
        //std::cout << "Collision occured.";
    }
}

Vec2D Enemy::Arrive()
{
    Vec2D toPlayer = gWorld.GetPlayer().GetPosition() - m_position;
    Real dist = toPlayer.Magnitude();
    if(dist > 0)
    {
        Real speed = dist / (Real)0.9;

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

void Enemy::Destroy()
{
}

void Enemy::Init(int maxHealth, Real speed, Real mass, const char *image)
{
    m_maxHealth = maxHealth;
    m_health = maxHealth;
    m_Speed = speed;
    m_mass = mass;
    SetSprite(image);
}

void Enemy::FindNeighbours(int numEnemies, Enemy *enemies)
{/*
    for(int i = 0;i < numEnemies;i++)
    {
        if(gWorld.GetLevel().GetZoneFromPoint(m_position) == gWorld.GetLevel().GetZoneFromPoint(enemies[i].GetPosition()))
        {
            Vec2D toNeighbour = 
        }
    }*/
}

void EnemySpawnPoint::Draw(Real duration)
{
    //Bruteforce casting :)
    m_circle.SetPosition(*(sf::Vector2f*)&m_position);
    gWorld.GetWindow()->Draw(m_circle);
}