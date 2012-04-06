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

#ifndef ENEMY_H
#define ENEMY_H

#include "MathUtil.h"
#include "Vec2D.h"
#include "Entity.h"
#include <vector>

/**
 * An enemy class. This should be used for zombies, etc.
 */
class Enemy : public CreatureEntity
{
public:
	/**
	 * The constructor. Calls the Init method.
	 */
	Enemy();

	/**
	 * The destructor. Calls the Destroy method.
	 */
	~Enemy();

	/**
	 * Initalizes the enemy.
	 */
	virtual void Init(int maxHealth, Real speed, Real mass, const char *image);

	/**
	 * Destroys the enemy.
	 */
	virtual void Destroy();

	/**
	 * Updates the AI.
	 */
	void Update(Real duration);

    /**
     * Sets the mass of the enemy.
     * @param mass The mass.
     */
    void SetMass(Real mass);

	/**
	 * Sets the speed of the enemy.
	 * @param speed The speed.
	 */
	void SetSpeed(Real speed);
    
    /**
     * Gets the speed of the enemy.
     * @return the speed of the enemy.
     */
    Real GetSpeed()
    {
        return m_Speed;
    }

    Vec2D m_velocity;       ///< Velocity of enemy.

    /**
     * Find neighbours enemies, by iterating through a array of enemies.
     */
    void FindNeighbours(int numEnemies, Enemy *enemies);

    std::vector<Enemy*> m_neighbours;///< Neighbour enemies in neighbour radius of enemy. 
    int m_neighbourRadius;///< Radius of the neightbours
private:
    Vec2D Arrive();

    bool m_calculateForce;
    Vec2D m_heading;        ///< Heding of enemy.

	Real m_Speed;			///< The speed of the enemy.
    Real m_mass;            ///< Mass of a enemy;
};

/**
 * Spawn point for enemy.
 */
class EnemySpawnPoint : public Entity
{
public:
    EnemySpawnPoint()
    {
        m_type = ENTITY_SPAWN_POINT;
        m_circle = sf::Shape::Circle(0, 0, 30, sf::Color(0, 255, 20)); 
    }

    void Draw(Real duration);

    sf::Shape m_circle;
};

#endif /* ENEMY_H */
