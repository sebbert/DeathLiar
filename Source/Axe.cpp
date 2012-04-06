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

#include "Axe.h"
#include "MathUtil.h"
#include "GameMaster.h"

void Axe::Fire()
{
    m_isHitting = true;
}

void Axe::StopFire()
{
    m_isHitting = false;
    m_sprite.SetRotation(0);
    m_hitRotation = 0;
}

void Axe::Update(Real duration)
{
    if(m_isHitting)
    {
        short numEnemies = gGameMaster.GetNumEnemies();
        Enemy* enemies = gGameMaster.GetEnemies();

        for(short i = 0; i < numEnemies; i++)
        {
            if(enemies[i].m_health > 0 && enemies[i].CollidesWith(m_hitOffset));
            {
                --enemies[i].m_health;
            }
        }

        m_sprite.SetRotation(m_hitRotation);
        m_hitRotation += 0.5 * (m_hitDir ? 1 : -1);

        if((m_hitRotation > 45) || (m_hitRotation < -45)) m_hitDir = !m_hitDir;
    }
}