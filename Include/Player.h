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
#include <SFML/Graphics.hpp>

/**
 * Player is the entity the user is controlling.
 */
class Player : public Entity
{
public:
    Player();

    void Init();

    /**
     * Handle user inputs.
     */
    void HandleEvents(sf::Event &event);

    /**
     * Update each frame.
     */
    void Update(Real duration);
    
    Vec2D GetWorldPos();

    Vec2D GetLevelPos()
    {
        return m_levelPos;
    }

    Vec2D GetVelocity()
    {
        return m_velocity;
    }

    Real GetSpeed()
    {
        return m_speed;
    }

    Vec2D GetHeading()
    {
        return m_heading;
    }
private:
    Vec2D m_velocity;///< Velocity of player.
    Vec2D m_heading;///< Heading of a player.
    Vec2D m_levelPos;///< Level pos.

    Real m_speed;///< Speed of player.

    int m_maxHealth;///< Maxium health of a player.
    int m_health;///< Current health of player.
};

float AngleBetweenPoints(const Vec2D& p1, const Vec2D& p2);

#endif