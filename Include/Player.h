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
* Copyright � 2012 Emil Sandst�, Sebastian Reinhard
* 
*/
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

/**
 * Player is the entity the user is controlling.
 */
class Player : public Entity
{
public:
    Player();

    /**
     * Handle user inputs.
     */
    void HandleEvents(sf::Event &event);

    /**
     * Update each frame.
     */
    void Update(Real duration);
private:
    Vec2D m_velocity;///< Velocity of player.
    Vec2D m_acceleration;///< Acceleration of player.

    Real m_accSpeed;///< How much to alter acceleration of a player.
    Real m_forwardSpeed;///< Forward speed of a player.
    Real m_backwardSpeed;///< Backward speed of a player.
    Real m_sideSpeed;///< Speed of going left and right.
    
    int m_maxHealth;///< Maxium health of a player.
    int m_health;///< Current health of player.
};

#endif