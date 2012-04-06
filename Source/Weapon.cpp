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

#include "Weapon.h"
#include "World.h"

Weapon::Weapon(int damage, int maxHealth, int weaponDamage)
{
    m_Damage = damage;
    m_MaxHealth = maxHealth;
    m_WeaponHealth = maxHealth;
    m_WeaponDamage = weaponDamage;
}

void Bullet::Update(Real duration)
{   
    m_position += m_velocity * duration;
    //Add some drag, but let it be litle.
    m_velocity *= std::pow((Real)0.9999, duration);
}

Bullet::Bullet()
{
    m_Damage = 0;
    m_MaxHealth = 0;
    m_WeaponDamage = 0;
    m_mass = 0;
    m_oneOverMass = 0;
}

void BulletManager::Init()
{
    //Reserve space for 50 bullets. No more than that.
    m_bullets.resize(50);
}

void BulletManager::FireBullet(const char *image, Real mass, int damage, int maxHealth, int weaponDamage, Vec2D &startPos, Vec2D &force)
{
    BulletIter iter = m_bullets.begin();
    for(;iter != m_bullets.end();++iter)
    {
        if(iter->m_MaxHealth == 0)
        {
            *iter = Bullet(mass, damage, maxHealth, weaponDamage, startPos, force);
            iter->SetSprite(image);
            break;
        }
    }

    if(iter == m_bullets.end())
    {
        iter = m_bullets.begin();
        *iter = Bullet(mass, damage, maxHealth, weaponDamage, startPos, force);
        iter->SetSprite(image);
    }
}

void BulletManager::Update(Real duration)
{
    for(BulletIter iter = m_bullets.begin();
            iter != m_bullets.end();++iter)
    {
        if(iter->m_MaxHealth == 0)
            continue;

        iter->Draw(duration);

        //Remove bullet if destroyed or went out of level.
        if(iter->m_WeaponDamage < 0 || !gWorld.IsInLevel(iter->GetPosition()))
        {
            iter->m_MaxHealth = 0;
        }
    }
}

void BulletManager::ResolveCollisions(CreatureEntity *entity)
{
    for(BulletIter iter = m_bullets.begin();
         iter != m_bullets.end();++iter)
    {
        if(iter->m_MaxHealth == 0)
            continue;

        Vec2D between = entity->GetPosition() - (iter->GetPosition() + (iter->m_velocity * gWorld.GetFrameTime()));
        if(between.MagnitudeSquared() <= iter->m_halfWidth * iter->m_halfWidth + entity->m_halfWidth * entity->m_halfWidth)
        {
            entity->m_health -= iter->m_Damage;
            iter->m_WeaponHealth -= iter->m_WeaponDamage;
            if(iter->m_WeaponHealth <= 0)
            {
                iter->m_MaxHealth = 0;
            }
        }
    }
}