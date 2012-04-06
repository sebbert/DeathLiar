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

#ifndef AXE_H_
#define AXE_H_

#include "Weapon.h"

class Axe : public Weapon
{
public:
    Axe() : Weapon(1, 1, 0)
    {
        m_hitOffset = Vec2D(36, -35);
        SetSprite("weapon_axe.png");
    }
    void Fire();
    void StopFire();
    void Update(Real duration);

private:
    Real m_hitRotation;
    bool m_hitDir;
};

#endif