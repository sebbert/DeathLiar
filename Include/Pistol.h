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
#ifndef PISTOL_H_
#define PISTOL_H_

#include "Weapon.h"
#include <SFML/System.hpp>

/**
 * Pistol is a lightweight weapon, which don't damage very much. 
 * This weapon single shots, and the shoot frequenzy is low. 
 */
class Pistol : public Weapon
{
public:
    Pistol();

    void Fire();
    
    sf::Clock m_clock;
    float m_secBetweenShots;
};

#endif